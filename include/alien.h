#pragma once

#include <raylib.h>

class Alien{
public:
  Texture2D image;
  int type;
  Vector2 position;

  Alien(int type, Vector2 position);
  void Update();
  void Draw();
  int GetType();

private:

};
