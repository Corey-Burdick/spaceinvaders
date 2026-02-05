#pragma once

#include <stdio.h>
#include <vector>
#include <raylib.h>
#include <laser.h>

class Spaceship {
public:
  std::vector<Laser> lasers;
  double fireRate;
  Texture2D image;
  
  Spaceship();
  ~Spaceship();
  void Update();
  void Draw();
  void MoveLeft();
  void MoveRight();
  void FireLaser();
  Rectangle GetRect();
  
private:
  Vector2 position;
  double lastFireTime;

};
