#include "Main.h"
#include "UI.h"

long count_words(const string & text)
{
  long count{0};
  for(long i{0}; i < static_cast<long>(text.size()); ++i)
  {
    if(text[i] == ' ')
    {
      ++count;
    }
  }
  return count + 1;
}

long get_text_font_word_width(string word)
{
  long current_pos{0};

  while(word != "")
  {
    current_pos += FONT_TEXT_CHAR_WIDTHS[word[0]];
    word.erase(word.begin());
  }
  return current_pos;
}

void crash(const string & message)
{
  Fnt* font{new Fnt};
  ++mem;
  while(WindowShouldClose() == false)   // Detect window close button or ESC key
  {
    BeginDrawing();
    ClearBackground(Color{0x00, 0x00, 0x00, 0xFF});
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color{0, 0, 0, 255});
    font->render_text_center(message, SCREEN_HEIGHT / 2 - font->get_height() / 2, 255);
    EndDrawing();
  }
  exit(1);
}
