#include <game.h>

Game::Game() {
  InitAudioDevice();
  mainTheme = LoadMusicStream("Music/PlaceholderTrack1.ogg");
  mainTheme.looping = true;
  SetMusicVolume(mainTheme, 0.6f);
  PlayMusicStream(mainTheme);
  lives = 3;
  wavesCleared = 0;
  wavesSinceReset = 0;
  obstacles = CreateObstacles();
  aliens = CreateAliens();
  aliensDirection = 1;
  timeLastAlienFired = 0;
  timeLastSpawn = 0;
  mysteryShipSpawnInterval = GetRandomValue(10, 20);
}

Game::~Game() {
  printf("Unloaded Game.\n");
  UnloadMusicStream(mainTheme);
  Alien::UnloadImages();
}

void Game::Update() {

  UpdateMusicStream(mainTheme);

  if (aliens.empty()) {
    aliens = CreateAliens();
    wavesCleared += 1;
    wavesSinceReset += 1;
    if (wavesSinceReset >= 5) {
      obstacles = CreateObstacles();
      wavesSinceReset = 0;
      lives += 1;
    }
  }

  if (lives <= 0) {
    aliens = CreateAliens();
    obstacles = CreateObstacles();
    lives = 3;
    wavesCleared = 0;
    wavesSinceReset = 0;
  }
  if (lives > 15) {
    lives = 15;
  }

  double currentTime = GetTime();
  if (currentTime - timeLastSpawn > mysteryShipSpawnInterval) {
    mysteryship.Spawn();
    timeLastSpawn = GetTime();
    mysteryShipSpawnInterval = GetRandomValue(10, 20);
  }

  if (mysteryship.alive) {
    spaceship.fireRate = 0;
  } else {
    spaceship.fireRate = 0.35;
  }

  for (auto& laser: spaceship.lasers) {
    laser.Update();
  }

  MoveAliens();

  AlienShootLaser();

  for (auto& laser: alienLasers) {
    laser.Update();
  }

  DeleteInactiveLasers();
  mysteryship.Update();

  CheckForCollisions();

}

void Game::Draw() {

  spaceship.Draw();

  for (auto& laser: spaceship.lasers) {
    laser.Draw();
  }

  for (auto& obstacle: obstacles) {
    obstacle.Draw();
  }

  for (auto& alien: aliens) {
    alien.Draw();
  }

  for (auto& laser: alienLasers) {
    laser.Draw();
  }

  mysteryship.Draw();

  //DrawText(TextFormat("LIVES: %i", lives), 5, 5, 40, WHITE);
  
  for (int i = 0; i < lives; i++) {
    DrawTexture(spaceship.image, 5 + spaceship.image.width * i + 5 * i, 5, WHITE);
  }

  DrawText(TextFormat("Waves Cleared: %i", wavesCleared), 5, spaceship.image.height + 10, 25, WHITE);

}

void Game::HandleInput() {

  if (IsKeyDown(KEY_LEFT)) {
    spaceship.MoveLeft();
  } 
  if (IsKeyDown(KEY_RIGHT)) {
    spaceship.MoveRight();
  } 
  if (IsKeyDown(KEY_SPACE)) {
    spaceship.FireLaser();
  }
  if (IsKeyDown(KEY_R)) {
    lives += 1;
  }

}


void Game::DeleteInactiveLasers() {
  
  for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) {
    if (!it -> active) {
      it = spaceship.lasers.erase(it);
    } else {
      ++it;
    }
  }

  for (auto it = alienLasers.begin(); it != alienLasers.end();) {
    if (!it -> active) {
      it = alienLasers.erase(it);
    } else {
      ++it;
    }
  }

}

std::vector<Obstacle> Game::CreateObstacles() {
  
  int obstacleWidth = Obstacle::grid[0].size() * 3;
  float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;

  for (int i = 0; i < 4; i++) {
    float offsetX = (i + 1) * gap + i * obstacleWidth;
    obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 100)}));
  }
 
  return obstacles;

}

std::vector<Alien> Game::CreateAliens() {

  std::vector<Alien> aliens;
  for (int row = 0; row < 5; row++) {
    for (int column = 0; column < 11; column++) {
      
      int alienType;
      if (row == 0) {
        alienType = 3;
      } else if (row == 1 || row == 2) {
        alienType = 2;
      } else {
        alienType = 1;
      }

      float x = 75 + column * 55;
      float y = 110 + row * 55;
      
      aliens.push_back(Alien(alienType, {x, y}));
    }
  }

  return aliens;

}

void Game::MoveAliens() {

  for (auto& alien: aliens) {
    if (alien.position.x + alien.alienImage[alien.type - 1].width > GetScreenWidth()) {
      aliensDirection = -1;
      MoveDownAliens(4);
    }

    if (alien.position.x < 0) {
      aliensDirection = 1;
      MoveDownAliens(4);
    }
    alien.Update(aliensDirection);
  }

}

void Game::MoveDownAliens(int distance) {

  for (auto& alien: aliens) {
    alien.position.y += distance;
  }

}

void Game::AlienShootLaser() {

  double currentTime = GetTime();

  if (currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty()) {

    int randomIndex = GetRandomValue(0, aliens.size() - 1);
    Alien& alien = aliens[randomIndex];
    alienLasers.push_back(Laser({alien.position.x + alien.alienImage[alien.type - 1].width/2, alien.position.y + alien.alienImage[alien.type - 1].height}, 6));

    timeLastAlienFired = GetTime();

  }
}

void Game::CheckForCollisions() {

  //Spaceship Lasers
  
  for (auto& laser: spaceship.lasers) {
    auto it = aliens.begin();
    while (it != aliens.end()) {
      if (CheckCollisionRecs(it -> GetRect(), laser.GetRect())) {
        it = aliens.erase(it);
        laser.active = false;
      } else {
        it++;
      }
    }

    for (auto& obstacle: obstacles) {
      auto it = obstacle.blocks.begin();
      while (it != obstacle.blocks.end()) {
        if (CheckCollisionRecs(it -> GetRect(), laser.GetRect())) {
          it = obstacle.blocks.erase(it);
          laser.active = false;
        } else {
          it++;
        }
      }
    }

    if (CheckCollisionRecs(mysteryship.GetRect(), laser.GetRect())) {
      mysteryship.alive = false;
      laser.active = false;
    }
  }

  //Alien Lasers

  for (auto& laser: alienLasers) {
    if (CheckCollisionRecs(laser.GetRect(), spaceship.GetRect())) {
      laser.active = false;
      lives -= 1;
      printf("Spaceship Hit!\n");
    }

    for (auto& obstacle: obstacles) {
      auto it = obstacle.blocks.begin();
      while (it != obstacle.blocks.end()) {
        if (CheckCollisionRecs(it -> GetRect(), laser.GetRect())) {
          it = obstacle.blocks.erase(it);
          laser.active = false;
        } else {
          it++;
        }
      }
    }

  }

  //Alien Collision with Obstacle
  
  for (auto& alien: aliens) {
    for (auto& obstacle: obstacles) {
      auto it = obstacle.blocks.begin();
      while (it != obstacle.blocks.end()) {
        if (CheckCollisionRecs(it -> GetRect(), alien.GetRect())) {
          it = obstacle.blocks.erase(it);
        } else {
          it++;
        }
      }
    }

    if (CheckCollisionRecs(alien.GetRect(), spaceship.GetRect())) {
      printf("Spaceship Hit by Alien!\n");
    }
  }
}
