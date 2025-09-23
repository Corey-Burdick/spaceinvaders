#include <game.h>

Game::Game() {


}

Game::~Game() {
  printf("Unloaded Game.\n");
}

void Game::Update() {

  for (auto& laser: spaceship.lasers) {
    laser.Update();
  }

  DeleteInactiveLasers();

}

void Game::Draw() {

  spaceship.Draw();

  for (auto& laser: spaceship.lasers) {
    laser.Draw();
  }
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
}


void Game::DeleteInactiveLasers() {
  
  for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) {
    if (!it -> active) {
      it = spaceship.lasers.erase(it);
    } else {
      ++it;
    }
  }

}
