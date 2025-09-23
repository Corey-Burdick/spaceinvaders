#pragma once

#include <raylib.h>
#include <stdio.h>

class Alien{
public:
  static Texture2D alienImage[3];
  int type;
  Vector2 position;


  Alien(int type, Vector2 position);
  static void UnloadImages();
  void Update(int direction);
  void Draw();
  int GetType();
  Rectangle GetRect();

private:

};
