#include "Main.h"
#include "Game_State.h"

long mem;

int main(int argc, char* args[])
{
  mem = 0;

  // seed the random number generator
  srand(time(nullptr));
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TEXT.c_str());
  InitAudioDevice();      // Initialize audio device
  SetTargetFPS(SCREEN_FPS);               // Set our game to run at 60 frames-per-second

  Game* game{new Game};
  ++mem;

  // Main game loop
  while(WindowShouldClose() == false)   // Detect window close button or ESC key
  {
    // Update
    game->update();

    // Draw
    BeginDrawing();
    ClearBackground(Color{0x00, 0x00, 0x00, 0xFF});
    game->render();
    EndDrawing();
  }

  // Shut Down
  delete game;
  game = nullptr;
  --mem;
  CloseAudioDevice();     // Close audio device
  CloseWindow();        // Close window and OpenGL context
  return mem;
}