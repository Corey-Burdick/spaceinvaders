#include <mysteryship.h>

MysteryShip::MysteryShip() {
  image = LoadTexture("Graphics/Moon.png");
  memeText = LoadTexture("Graphics/descriptiveText.png");
  alive = false;
}

MysteryShip::~MysteryShip() {
  UnloadTexture(image);
  UnloadTexture(memeText);
}

void MysteryShip::Spawn() {
  position.y = 50;
  int side = GetRandomValue(0, 1);

  if (side == 0) {
    position.x = 0;
    speed = 3;
  } else {
    position.x = GetScreenWidth() - image.width;
    speed = -3;
  }

  alive = true;
}

void MysteryShip::Update() {
  if (alive) {
    position.x += speed;
    if (position.x > GetScreenWidth() - image.width || position.x < 0) {
      alive = false;
    }
  }
}

void MysteryShip::Draw() {
  if (alive) {
    DrawTextureV(image, position, WHITE);
    DrawTextureV(memeText,{position.x - memeText.width + GetRandomValue(-2, 2), position.y + GetRandomValue(-2, 2)}, WHITE);
  }

}

Rectangle MysteryShip::GetRect() {
  if (alive) {
    return {position.x, position.y,
    float(image.width),
    float(image.height)
    };
  } else {
    return {position.x, position.y, 0, 0};
  }
}
