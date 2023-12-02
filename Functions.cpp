#include "Main.h"
#include "UI.h"

void music_op(const Music_Command_Params & command)
{
  static vector<Music> mus_list;
  static vector<string> name_list;
  if(command.m_operation == Music_Command::Add)
  {
    Music music{LoadMusicStreamFromMemory(".mp3", get<Add_Music_Params>(command.m_params).m_data, get<Add_Music_Params>(command.m_params).m_size)};
    music.looping = true;
    mus_list.push_back(music);
    name_list.push_back(get<Add_Music_Params>(command.m_params).m_name);
  }

  else if(command.m_operation == Music_Command::Remove)
  {
    UnloadMusicStream(mus_list[mus_list.size() - 1]);   // Unload music stream buffers from RAM
    mus_list.pop_back();
    name_list.pop_back();
  }
  
  else if(command.m_operation == Music_Command::Remove_All)
  {
    while(mus_list.empty() == false)
    {
      UnloadMusicStream(mus_list[mus_list.size() - 1]);   // Unload music stream buffers from RAM
      mus_list.pop_back();
      name_list.pop_back();
    }
  }

  else if(command.m_operation == Music_Command::Update)
  {
    for(long i{0}; i < static_cast<long>(mus_list.size()); ++i)
    {
      UpdateMusicStream(mus_list[i]);   // Update music buffer with new stream data
    }
  }

  else if(command.m_operation == Music_Command::Play)
  {
    for(long i {0}; i < static_cast<long>(mus_list.size()); ++i)
    {
      if(get<Play_Pause_Music_Params>(command.m_params).m_name == name_list[i])
      {
        PlayMusicStream(mus_list[i]);
        return;
      }
    }
    crash("Error: Tried to play invalid music " + get<Play_Pause_Music_Params>(command.m_params).m_name + ".");
  }
  
  else if(command.m_operation == Music_Command::Pause)
  {
    for(long i {0}; i < static_cast<long>(mus_list.size()); ++i)
    {
      if(get<Play_Pause_Music_Params>(command.m_params).m_name == name_list[i])
      {
        PauseMusicStream(mus_list[i]);
        return;
      }
    }
    crash("Error: Tried to pause invalid music " + get<Play_Pause_Music_Params>(command.m_params).m_name + ".");
  }

  else if(command.m_operation == Music_Command::Volume)
  {
    for(long i {0}; i < static_cast<long>(mus_list.size()); ++i)
    {
      if(get<Volume_Music_Params>(command.m_params).m_name == name_list[i])
      {
        SetMusicVolume(mus_list[i], get<Volume_Music_Params>(command.m_params).m_volume);
        return;
      }
    }
    crash("Error: Tried to set the volume of invalid music " + get<Volume_Music_Params>(command.m_params).m_name + ".");
  }
  
  else
  {
    crash("Error: Invalid music command.");
  }
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