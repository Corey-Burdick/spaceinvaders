#pragma once

#include <stdio.h>
#include <raylib.h>
#include <spaceship.h>
#include <obstacle.h>
#include <alien.h>

class Game{
public:

  Game();
  ~Game();
  void Draw();
  void Update();
  void HandleInput();


private:
  Spaceship spaceship;
  std::vector<Obstacle> obstacles;
  std::vector<Alien> aliens;
  std::vector<Laser> alienLasers;
  int aliensDirection;
  constexpr static float alienLaserShootInterval = 0.35;
  float timeLastAlienFired;

  void DeleteInactiveLasers();
  std::vector<Obstacle> CreateObstacles();
  std::vector<Alien> CreateAliens();
  void MoveAliens();
  void MoveDownAliens(int distance);
  void AlienShootLaser();

};
