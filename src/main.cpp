#include <raylib.h>
#include <game.h>

int main() {

  Color grey = {29, 29, 27, 255};

  int windowWidth = 750;
  int windowHeight = 700;

  InitWindow(windowWidth, windowHeight, "C++ Space Invader");
  InitAudioDevice();
  SetTargetFPS(60);

  Game game = Game();
  Music mainTheme = LoadMusicStream("Music/PlaceholderTrack1.ogg");
  mainTheme.looping = true;
  PlayMusicStream(mainTheme);

  while (!WindowShouldClose()) {
    UpdateMusicStream(mainTheme);
    game.HandleInput();
    game.Update();

    BeginDrawing();
    ClearBackground(grey);

    game.Draw();

    EndDrawing();
  }

  UnloadMusicStream(mainTheme);

  printf("Window Closed.\n");
}
