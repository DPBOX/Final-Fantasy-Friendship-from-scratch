#include "Main.h"
#include "Game_State.h"

long mem;
const Sound_Player* g_sound_player;

int main(int argc, char* args[])
{
  mem = 0;

  // seed the random number generator
  srand(time(nullptr));
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TEXT.c_str());
  InitAudioDevice();      // Initialize audio device

  //The frames per second cap timer
  LTimer cap_timer;

  g_sound_player = new Sound_Player;
  ++mem;

  Game* game{new Game};
  ++mem;
  {
    thread t{&Game::update_music, game};

    // Main game loop
    while(WindowShouldClose() == false)   // Detect window close button or ESC key
    {
      cap_timer.start();

      // Update
      game->update();

      // Draw
      BeginDrawing();
      ClearBackground(Color{0x00, 0x00, 0x00, 0xFF});
      game->render();
      EndDrawing();

      long i{1};
      while(FRAME_LENGTH_IN_SECONDS * i - cap_timer.get_ticks() < 0)
      {
        ++i;
      }
      WaitTime(FRAME_LENGTH_IN_SECONDS * i - cap_timer.get_ticks());
    }
    game->terminate_music();
    t.join();
  }

  // Shut Down
  delete game;
  game = nullptr;
  --mem;
  delete g_sound_player;
  g_sound_player = nullptr;
  --mem;
  CloseAudioDevice();     // Close audio device
  CloseWindow();        // Close window and OpenGL context
  return mem;
}
