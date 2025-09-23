#include <laser.h>

Laser::Laser(Vector2 position, int speed) {

  active = true;
  this -> position = position;
  this -> speed = speed;

}

void Laser::Draw() {
  if (active) {
    DrawRectangle(position.x, position.y, 4, 15, {243, 216, 63, 255});
  }

}

void Laser::Update() {
  position.y += speed;
  if (position.y > GetScreenHeight() || position.y < 0) {
    active = false;
    printf("Laser Inactive.\n");
  }
}

Rectangle Laser::GetRect() {
  return {position.x, position.y, 4, 15};
}
