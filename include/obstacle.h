#pragma once

#include <raylib.h>
#include <vector>
#include <block.h>


class Obstacle{
public:
  Vector2 position; 
  std::vector<Block> blocks;
  static std::vector<std::vector<int>> grid;
  
  Obstacle(Vector2 position);
  void Draw();

private:


};
