#pragma once

#include <raylib.h>
#include <stdio.h>

class Laser{
public:
  bool active; 

  Laser(Vector2 position, int speed);
  void Update();
  void Draw();
  Rectangle GetRect();

private:
  Vector2 position;
  int speed;

};
