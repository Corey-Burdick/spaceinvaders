#pragma once

#include <stdio.h>
#include <raylib.h>
#include <spaceship.h>
#include <obstacle.h>

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

  void DeleteInactiveLasers();
  std::vector<Obstacle> CreateObstacles();

};
