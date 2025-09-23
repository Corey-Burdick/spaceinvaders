#pragma once

#include <stdio.h>
#include <vector>
#include <raylib.h>
#include <laser.h>

class Spaceship {
public:
  std::vector<Laser> lasers;
  
  Spaceship();
  ~Spaceship();
  void Update();
  void Draw();
  void MoveLeft();
  void MoveRight();
  void FireLaser();
  Rectangle GetRect();

private:
  Texture2D image;
  Vector2 position;
  double lastFireTime;

};
