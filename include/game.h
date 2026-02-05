#pragma once

#include <stdio.h>
#include <raylib.h>
#include <spaceship.h>
#include <obstacle.h>
#include <alien.h>
#include <mysteryship.h>

class Game{
public:
  int lives;
  int wavesCleared;
  int wavesSinceReset;

  Game();
  ~Game();
  void Draw();
  void Update();
  void HandleInput();


private:
  Spaceship spaceship;
  MysteryShip mysteryship;
  std::vector<Obstacle> obstacles;
  std::vector<Alien> aliens;
  std::vector<Laser> alienLasers;
  int aliensDirection;
  constexpr static float alienLaserShootInterval = 0.35;
  float timeLastAlienFired;
  float mysteryShipSpawnInterval;
  float timeLastSpawn;

  void DeleteInactiveLasers();
  std::vector<Obstacle> CreateObstacles();
  std::vector<Alien> CreateAliens();
  void MoveAliens();
  void MoveDownAliens(int distance);
  void AlienShootLaser();
  void CheckForCollisions();

};
