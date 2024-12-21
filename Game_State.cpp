#include "Main.h"
#include "Game_State.h"

Music_Player::Music_Player()
{
  Music music{LoadMusicStreamFromMemory(".mp3", CITY_MUSIC.m_data, CITY_MUSIC.m_size)};
  m_global_music.push_back(music);

  m_global_music_names.push_back(CITY_MUSIC.m_name);
}

Music_Player::~Music_Player()
{
  for(long i{0}; i < static_cast<long>(m_global_music.size()); ++i)
  {
    UnloadMusicStream(m_global_music[i]);
  }
}

Sound_Player::Sound_Player()
{
  Wave wave{LoadWaveFromMemory(".wav", CURSOR_SOUND.m_data, CURSOR_SOUND.m_size)};
  m_global_sounds.push_back(LoadSoundFromWave(wave));
  UnloadWave(wave);
  Wave wave2{LoadWaveFromMemory(".wav", CONFIRM_SOUND.m_data, CONFIRM_SOUND.m_size)};
  m_global_sounds.push_back(LoadSoundFromWave(wave2));
  UnloadWave(wave2);
  Wave wave3{LoadWaveFromMemory(".wav", BACK_SOUND.m_data, BACK_SOUND.m_size)};
  m_global_sounds.push_back(LoadSoundFromWave(wave3));
  UnloadWave(wave3);
  Wave wave4{LoadWaveFromMemory(".wav", BUZZER_SOUND.m_data, BUZZER_SOUND.m_size)};
  m_global_sounds.push_back(LoadSoundFromWave(wave4));
  UnloadWave(wave4);

  m_global_sound_names.push_back(CURSOR_SOUND.m_name);
  m_global_sound_names.push_back(CONFIRM_SOUND.m_name);
  m_global_sound_names.push_back(BACK_SOUND.m_name);
  m_global_sound_names.push_back(BUZZER_SOUND.m_name);
}

Sound_Player::~Sound_Player()
{
  for(long i{0}; i < static_cast<long>(m_global_sounds.size()); ++i)
  {
    UnloadSound(m_global_sounds[i]);
  }
}

void Sound_Player::play_global_sound(const string & name) const
{
  for(long i{0}; i < static_cast<long>(m_global_sounds.size()); ++i)
  {
    if(m_global_sound_names[i] == name)
    {
      PlaySound(m_global_sounds[i]);
      return;
    }
  }
  crash("Error: Global sound effect \"" + name + "\" doesn't exist.");
}

void Music_Player::play_global_music(const string & name)
{
  for(long i{0}; i < static_cast<long>(m_global_music.size()); ++i)
  {
    if(m_global_music_names[i] == m_music_playing)
    {
      StopMusicStream(m_global_music[i]);
      m_music_playing = "NULL";
    }
  }
  for(long i{0}; i < static_cast<long>(m_global_music.size()); ++i)
  {
    if(m_global_music_names[i] == name)
    {
      PlayMusicStream(m_global_music[i]);
      m_music_playing = name;
      return;
    }
  }
  crash("Error: Global music \"" + name + "\" doesn't exist.");
}

void Music_Player::pause_play_global_music() const
{
  for(long i{0}; i < static_cast<long>(m_global_music.size()); ++i)
  {
    if(m_global_music_names[i] == m_music_playing)
    {
      if(IsMusicStreamPlaying(m_global_music[i]) == true)
      {
        PauseMusicStream(m_global_music[i]);
      }
      else
      {
        PlayMusicStream(m_global_music[i]);
      }
      return;
    }
  }
  crash("Error: Global music \"" + m_music_playing + "\" doesn't exist.");
}

void Music_Player::stop_global_music()
{
  for(long i{0}; i < static_cast<long>(m_global_music.size()); ++i)
  {
    if(m_global_music_names[i] == m_music_playing)
    {
      StopMusicStream(m_global_music[i]);
      m_music_playing = "NULL";
      return;
    }
  }
  crash("Error: Global music \"" + m_music_playing + "\" doesn't exist.");
}

void Music_Player::update_music()
{
  while(m_terminate_music == false)
  {
    for(long i{0}; i < static_cast<long>(m_global_music.size()); ++i)
    {
      if(m_global_music_names[i] == m_music_playing)
      {
        if(IsMusicStreamPlaying(m_global_music[i]) == true)
        {
          UpdateMusicStream(m_global_music[i]);
        }
      }
    }
    WaitTime(FRAME_LENGTH_IN_SECONDS);
  }
}

void Music_Player::terminate_music()
{
  m_terminate_music = true;
}

Game::Game()
{
  m_music_player = new Music_Player;
  ++mem;
  m_world = new World;
  ++mem;
  m_state_manager = new State_Manager(m_world, m_music_player);
  ++mem;
}

Game::~Game()
{
  delete m_state_manager;
  m_state_manager = nullptr;
  delete m_world;
  m_world = nullptr;
  delete m_music_player;
  m_music_player = nullptr;
  --mem;
  --mem;
  --mem;
}

void Game::update_music()
{
  m_music_player->update_music();
}

void Game::update()
{
  m_state_manager->change_state();
  m_state_manager->update_input(m_state_manager);
  m_world->update();
}

void Game::render() const
{
  m_state_manager->render();
  m_world->render_cursor();
}

void Game::terminate_music()
{
  m_music_player->terminate_music();
}

State_Manager::State_Manager(World* world, Music_Player* music_player) : m_world(world), m_music_player(music_player)
{
  Game_State* e{new Title_State};
  ++mem;
  m_states.push_back(e);
}

State_Manager::~State_Manager()
{
  if(m_next_state != nullptr)
  {
    delete m_next_state;
    --mem;
    m_next_state = nullptr;
  }
  for(long i{0}; i < static_cast<long>(m_states.size()); ++i)
  {
    delete m_states[i];
    m_states[i] = nullptr;
    --mem;
  }
}

void State_Manager::set_next_state(Game_State* new_state)
{
  m_next_state = new_state;
}

void State_Manager::pop_state()
{
  m_pop = true;
}

void State_Manager::change_state()
{
  if(m_next_state == nullptr && m_pop == true)
  {
    delete m_states[m_states.size() - 1];
    --mem;
    m_states.pop_back();
  }

  if(m_next_state != nullptr && m_pop == true)
  {
    delete m_states[m_states.size() - 1];
    --mem;
    m_states.pop_back();
    m_states.push_back(m_next_state);
  }

  if(m_next_state != nullptr && m_pop == false)
  {
    m_states.push_back(m_next_state);
  }
  m_next_state = nullptr;
  m_pop = false;
}

void State_Manager::update_input(State_Manager* state_manager)
{
  if(m_states.empty() == false)
  {
    m_states[m_states.size() - 1]->update_input(state_manager, m_world);
    for(long i{static_cast<long>(m_states.size()) - 2}; i >= 0; --i)
    {
      m_states[i]->update();
    }
  }
}

void State_Manager::render() const
{
  if(m_states.empty() == false)
  {
    for(long i{0}; i < static_cast<long>(m_states.size()); ++i)
    {
      m_states[i]->render(m_world);
    }
  }
}

Music_Player* State_Manager::get_music_player() const
{
  return m_music_player;
}

string Game_State::get_name() const
{
  return m_name;
}

void State_Manager::create_new_explore_state()
{
  Game_State* e{new Explore_State(m_music_player, MAPS[0], DUMMY_SCRIPT)};
  ++mem;
  pop_state();
  set_next_state(e);
}

void State_Manager::create_new_front_menu_state()
{
  Game_State* e{new Front_Menu_State(m_world)};
  ++mem;
  set_next_state(e);
}

void State_Manager::create_new_game_over_state()
{
  Game_State* e{new Game_Over_State};
  ++mem;
  set_next_state(e);
}

void State_Manager::create_new_battle_state()
{
  Game_State* e{new Game_Over_State};
  ++mem;
  set_next_state(e);
}

Title_State::Title_State()
{
  m_name = "Title";
}

void Title_State::update_input(State_Manager* state_manager, World* world)
{
  if(IsKeyPressed(KEY_Z) == true)
  {
    state_manager->create_new_explore_state();
  }
}

void Title_State::render(const World* const world) const
{
  m_renderer.render(world);
}

void Title_State_Renderer::render(const World* const world) const
{
  world->render_text_center("Heading", "Dungeon", SCREEN_HEIGHT / 4 - FONT_HEADING_HEIGHT / 2);
  world->render_text_center("Text", "Press Z!", SCREEN_HEIGHT * 3 / 4);
  world->render_text_center("Text", "(X is back.)", SCREEN_HEIGHT * 3 / 4 + FONT_TEXT_HEIGHT);
  world->render_text_center("Text", "(S is open and close the menu.)", SCREEN_HEIGHT * 3 / 4 + FONT_TEXT_HEIGHT * 2);
}

Explore_State::Explore_State(Music_Player* music_player, const Map_Data & map_data, const Scr & start_script)
{
  m_map_handler = new Map_Handler;
  ++mem;
  m_name = "Explore State";
  m_map_handler->add_map(music_player, map_data, m_map_handler);
  m_map_handler->add_script(start_script);
}

Explore_State::~Explore_State()
{
  delete m_map_handler;
  m_map_handler = nullptr;
  --mem;
}

void Explore_State::update_input(State_Manager* state_manager, World* world)
{
  m_map_handler->update_input(m_map_handler, state_manager->get_music_player(), world);

  if(IsKeyPressed(KEY_S) == true)
  {
    state_manager->create_new_front_menu_state();
  }

  if(m_map_handler->get_pop() == true)
  {
    state_manager->pop_state();
  }

  string next_state{m_map_handler->get_next_game_state()};
  if(next_state == "Game Over")
  {
    state_manager->create_new_game_over_state();
  }
  if(next_state == "Battle")
  {
    state_manager->create_new_battle_state();
  }
}

void Explore_State::render(const World* const world) const
{
  m_map_handler->render(m_map_handler, world);
}

Game_Over_State::Game_Over_State()
{
  m_name = "Game Over";
}

void Game_Over_State::update_input(State_Manager* state_manager, World* world){}

void Game_Over_State::render(const World* const world) const
{
  m_renderer.render(world);
}

void Game_Over_State_Renderer::render(const World* const world) const
{
  world->render_text_center("Heading", "End of Demo", SCREEN_HEIGHT / 2 - FONT_HEADING_HEIGHT / 2);
}

Front_Menu_State::Front_Menu_State(World* world)
{
  m_machine = new State_Machine;
  ++mem;
  m_machine->set_start_state_front_menu(world);
  m_name = "Front Menu State";
  m_world = world;
  world->pause_play_time();
}

Front_Menu_State::~Front_Menu_State()
{
  delete m_machine;
  m_machine = nullptr;
  --mem;
  m_world->unpause_play_time();
}

void Front_Menu_State::update()
{
  m_machine->update();
}

void Front_Menu_State::update_input(State_Manager* state_manager, World* world)
{
  m_machine->update_input(m_machine, world);
  if(IsKeyPressed(KEY_S) == true || (IsKeyPressed(KEY_X) == true && m_machine->check_exit() == true))
  {
    state_manager->pop_state();
    g_sound_player->play_global_sound("Back");
  }
  m_machine->change_state(world);
}

void Front_Menu_State::render(const World* const world) const
{
  m_machine->render(world);
}
