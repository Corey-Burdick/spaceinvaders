#include <raylib.h>
#include <game.h>

int main() {

  Color grey = {29, 29, 27, 255};

  int windowWidth = 750;
  int windowHeight = 700;

  InitWindow(windowWidth, windowHeight, "C++ Space Invader");
  SetTargetFPS(60);

  Game game = Game();

  while (!WindowShouldClose()) {
    
    game.HandleInput();
    game.Update();

    BeginDrawing();
    ClearBackground(grey);

    game.Draw();

    EndDrawing();
  }

  printf("Window Closed.\n");
}
