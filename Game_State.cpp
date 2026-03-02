#include "Main.h"
#include "Game_State.h"
#include "Input_Wrapper.h"
#include "Tilemap.h"
#include "UI.h"
#include "State_Machine.h"

Music_Player::Music_Player()
{
  Music music{LoadMusicStreamFromMemory(".mp3", PONYVILLE_MUSIC.m_data, PONYVILLE_MUSIC.m_size)};
  SetMusicVolume(music, PONYVILLE_MUSIC.m_volume);
  m_global_music.push_back(music);
  Music music2{LoadMusicStreamFromMemory(".mp3", BATTLE_MUSIC.m_data, BATTLE_MUSIC.m_size)};
  SetMusicVolume(music2, BATTLE_MUSIC.m_volume);
  m_global_music.push_back(music2);
  Music music3{LoadMusicStreamFromMemory(".mp3", INTRO_1_MUSIC.m_data, INTRO_1_MUSIC.m_size)};
  SetMusicVolume(music3, INTRO_1_MUSIC.m_volume);
  m_global_music.push_back(music3);
  Music music4{LoadMusicStreamFromMemory(".mp3", INTRO_2_MUSIC.m_data, INTRO_2_MUSIC.m_size)};
  SetMusicVolume(music4, INTRO_2_MUSIC.m_volume);
  m_global_music.push_back(music4);
  Music music5{LoadMusicStreamFromMemory(".mp3", TITLE_SCREEN_MUSIC.m_data, TITLE_SCREEN_MUSIC.m_size)};
  SetMusicVolume(music5, TITLE_SCREEN_MUSIC.m_volume);
  m_global_music.push_back(music5);

  m_global_music_names.push_back(PONYVILLE_MUSIC.m_name);
  m_global_music_names.push_back(BATTLE_MUSIC.m_name);
  m_global_music_names.push_back(INTRO_1_MUSIC.m_name);
  m_global_music_names.push_back(INTRO_2_MUSIC.m_name);
  m_global_music_names.push_back(TITLE_SCREEN_MUSIC.m_name);
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
  Wave wave5{LoadWaveFromMemory(".wav", BATTLE_TRANSITION_SOUND.m_data, BATTLE_TRANSITION_SOUND.m_size)};
  m_global_sounds.push_back(LoadSoundFromWave(wave5));
  UnloadWave(wave5);
  Wave wave6{LoadWaveFromMemory(".wav", EQUIP_SOUND.m_data, EQUIP_SOUND.m_size)};
  m_global_sounds.push_back(LoadSoundFromWave(wave6));
  UnloadWave(wave6);
  Wave wave7{LoadWaveFromMemory(".wav", ATB_SOUND.m_data, ATB_SOUND.m_size)};
  m_global_sounds.push_back(LoadSoundFromWave(wave7));
  UnloadWave(wave7);
  Wave wave8{LoadWaveFromMemory(".wav", EXIT_AREA_SOUND.m_data, EXIT_AREA_SOUND.m_size)};
  m_global_sounds.push_back(LoadSoundFromWave(wave8));
  UnloadWave(wave8);
  Wave wave9{LoadWaveFromMemory(".wav", DOOR_OPEN_SOUND.m_data, DOOR_OPEN_SOUND.m_size)};
  m_global_sounds.push_back(LoadSoundFromWave(wave9));
  UnloadWave(wave9);

  m_global_sound_names.push_back(CURSOR_SOUND.m_name);
  m_global_sound_names.push_back(CONFIRM_SOUND.m_name);
  m_global_sound_names.push_back(BACK_SOUND.m_name);
  m_global_sound_names.push_back(BUZZER_SOUND.m_name);
  m_global_sound_names.push_back(BATTLE_TRANSITION_SOUND.m_name);
  m_global_sound_names.push_back(EQUIP_SOUND.m_name);
  m_global_sound_names.push_back(ATB_SOUND.m_name);
  m_global_sound_names.push_back(EXIT_AREA_SOUND.m_name);
  m_global_sound_names.push_back(DOOR_OPEN_SOUND.m_name);
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
  m_state_manager = new State_Manager();
  ++mem;
  m_input = new Input_Wrapper();
  ++mem;
  m_next_state = make_tuple(false, nullptr, nullptr);
}

Game::~Game()
{
  delete m_state_manager;
  m_state_manager = nullptr;
  delete m_world;
  m_world = nullptr;
  delete m_music_player;
  m_music_player = nullptr;
  delete m_input;
  m_input = nullptr;
  --mem;
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
  m_input->poll();
  m_state_manager->change_state(m_next_state);
  m_next_state = m_state_manager->update_input(m_world, m_music_player, m_input);
  m_world->update();
  m_input->finish();
}

void Game::render() const
{
  m_state_manager->render(m_world);
  m_world->render_cursor();
}

void Game::terminate_music()
{
  m_music_player->terminate_music();
}

State_Manager::State_Manager()
{
  Game_State* e{new Title_State};
  ++mem;
  m_states.push_back(e);
}

State_Manager::~State_Manager()
{
  for(long i{0}; i < static_cast<long>(m_states.size()); ++i)
  {
    delete m_states[i];
    m_states[i] = nullptr;
    --mem;
  }
}

void State_Manager::change_state(const tuple<bool, Game_State*, Game_State*> & state)
{
  if(get<1>(state) == nullptr && get<0>(state) == true)
  {
    delete m_states[m_states.size() - 1];
    --mem;
    m_states.pop_back();
  }

  if(get<1>(state) != nullptr && get<0>(state))
  {
    delete m_states[m_states.size() - 1];
    --mem;
    m_states.pop_back();
    m_states.push_back(get<1>(state));
  }

  if(get<1>(state) != nullptr && get<0>(state) == false)
  {
    m_states.push_back(get<1>(state));
    if(get<2>(state) != nullptr && get<0>(state) == false)
    {
      m_states.push_back(get<2>(state));
    }
  }
}

tuple<bool, Game_State*, Game_State*> State_Manager::update_input(World* world, Music_Player* music_player, Input_Wrapper* input)
{
  tuple<bool, Game_State*, Game_State*> state{make_tuple(false, nullptr, nullptr)};

  if(m_states.empty() == false)
  {
    state = m_states[m_states.size() - 1]->update_input(world, music_player, input);
    for(long i{static_cast<long>(m_states.size()) - 2}; i >= 0; --i)
    {
      m_states[i]->update(world);
    }
  }
  return state;
}

void State_Manager::render(World* world) const
{
  if(m_states.empty() == false)
  {
    for(long i{0}; i < static_cast<long>(m_states.size()); ++i)
    {
      m_states[i]->render(world);
    }
  }
}

string Game_State::get_name() const
{
  return m_name;
}

Title_State::Title_State()
{
  m_name = "Title";
}

void Title_State::update(World* world){}

tuple<bool, Game_State*, Game_State*> Title_State::update_input(World* world, Music_Player* music_player, Input_Wrapper* input)
{
  if(input->A_button_pressed() == true)
  {
    Game_State* e{new Explore_State(music_player, MAPS[0], 1)};
    ++mem;
    return make_tuple(true, e, nullptr);
  }
  return make_tuple(false, nullptr, nullptr);
}

void Title_State::render(const World* const world) const
{
  m_renderer.render(world);
}

void Title_State_Renderer::render(const World* const world) const
{
  world->render_text_center("Heading", "Dungeon", SCREEN_HEIGHT / 4 - FONT_HEADING_HEIGHT / 2);
  world->render_text_center("Text", "Press Z!", SCREEN_HEIGHT * 3 / 4);
  world->render_text_center("Text", "(X is back.)", SCREEN_HEIGHT * 3 / 4 + TEXT_FONT_HEIGHT);
  world->render_text_center("Text", "(S is open and close the menu.)", SCREEN_HEIGHT * 3 / 4 + TEXT_FONT_HEIGHT * 2);
}

Explore_State::Explore_State(Music_Player* music_player, const Map_Data & map_data, const long & start_script_index)
{
  m_map = new Tilemap(music_player, map_data);
  ++mem;
  m_name = "Explore State";
  m_script_handler = new Script_Handler{map_data.m_scripts};
  ++mem;
  m_map->add_entities(m_map, map_data, Direction::Left, 10, 6, 0);
  m_map->run_script(start_script_index);
}

Explore_State::~Explore_State()
{
  if(m_map != nullptr)
  {
    delete m_map;
    m_map = nullptr;
    --mem;
  }
  if(m_script_handler != nullptr)
  {
    delete m_script_handler;
    m_script_handler = nullptr;
    --mem;
  }
}

void Explore_State::update(World* world){}

tuple<bool, Game_State*, Game_State*> Explore_State::update_input(World* world, Music_Player* music_player, Input_Wrapper* input)
{
  long map_script{m_map->update_input(m_map, input)};
  bool pop{false};

  tuple<bool, string, string, bool, const Map_Data*, tuple<Direction, long, long, long>> s{make_tuple(false, "NULL", "NULL", false, nullptr, make_tuple(Direction::Down, 0, 0, 0))};
  if(m_script_handler != nullptr)
  {
    if(map_script != -1)
    {
      m_script_handler->run_script(map_script);
    }
    s = m_script_handler->update_input(m_map, music_player, world, input);
    if(get<3>(s) == true)
    {
      m_map->unlock_controls();
    }
    if(get<4>(s) != nullptr)
    {
      tuple<Direction, long, long, long> inner{get<5>(s)};
      delete m_map;
      m_map = nullptr;
      --mem;
      m_map = new Tilemap(music_player, *get<4>(s));
      ++mem;
      m_map->add_entities(m_map, *get<4>(s), get<0>(inner), get<1>(inner), get<2>(inner), get<3>(inner));
    }
  }

  if(input->X_button_pressed() == true)
  {
    Game_State* e{new Front_Menu_State(world)};
    ++mem;
    return make_tuple(false, e, nullptr);
  }

  if(get<0>(s) == true)
  {
    pop = true;
  }

  if(get<1>(s) == "Battle")
  {
    Game_State* e{new Battle_State(world)};
    ++mem;

    if(get<2>(s) == "Battle Transition")
    {
      Game_State* e2{new Battle_Transition_State()};
      ++mem;
      return make_tuple(pop, e, e2);
    }
    else
    {
      return make_tuple(pop, e, nullptr);
    }
  }
  return make_tuple(pop, nullptr, nullptr);
}

void Explore_State::render(const World* const world) const
{
  m_map->render(m_map);
  if(m_script_handler != nullptr)
  {
    m_script_handler->render(world);
  }
}

Game_Over_State::Game_Over_State()
{
  m_name = "Game Over";
}

void Game_Over_State::update(World* world){}

tuple<bool, Game_State*, Game_State*> Game_Over_State::update_input(World* world, Music_Player* music_player, Input_Wrapper* input)
{
  return make_tuple(false, nullptr, nullptr);
}

void Game_Over_State::render(const World* const world) const
{
  m_renderer.render(world);
}

void Game_Over_State_Renderer::render(const World* const world) const
{
  world->render_text_center("Heading", "End of Demo", SCREEN_HEIGHT / 2 - FONT_HEADING_HEIGHT / 2);
}

Battle_Transition_State::Battle_Transition_State()
{
  m_name = "Battle Transition";
}

void Battle_Transition_State::update(World* world){}

tuple<bool, Game_State*, Game_State*> Battle_Transition_State::update_input(World* world, Music_Player* music_player, Input_Wrapper* input)
{
  m_alpha -= BATTLE_TRANSITION_SPEED;
  if(m_alpha <= 0)
  {
    m_alpha = 0;
    return make_tuple(true, nullptr, nullptr);
  }
  return make_tuple(false, nullptr, nullptr);
}

void Battle_Transition_State::render(const World* const world) const
{
  m_renderer.render(world, m_alpha);
}

void Battle_Transition_State_Renderer::render(const World* const world, const long & alpha) const
{
  DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color{255, 255, 255, static_cast<unsigned char>(alpha)});
}

Battle_State::Battle_State(const World* const world)
{
  m_name = "Battle";
  for(long i{0}; i < world->get_party_size(); ++i)
  {
    m_party.push_back(new Battle_Ally{world->get_party_member_name(i), i, HERO_ANIMATION_SPEED, vector<vector<long>>{HERO_ANIM_BATTLE_IDLE, HERO_ANIM_BATTLE_GUARD}});
    ++mem;
  }
  m_enemies.push_back(new Battle_Enemy(CHANGELING_INFO, 0, CHANGELING_ANIMATION_SPEED));
  m_enemies.push_back(new Battle_Enemy(CHANGELING_INFO, 1, CHANGELING_ANIMATION_SPEED));
  m_enemies.push_back(new Battle_Enemy(CHANGELING_INFO, 2, CHANGELING_ANIMATION_SPEED));
  m_enemies.push_back(new Battle_Enemy(CHANGELING_INFO, 3, CHANGELING_ANIMATION_SPEED));
  m_enemies.push_back(new Battle_Enemy(CHANGELING_INFO, 4, CHANGELING_ANIMATION_SPEED));
  m_enemies.push_back(new Battle_Enemy(CHANGELING_INFO, 5, CHANGELING_ANIMATION_SPEED));
  ++mem;
  ++mem;
  ++mem;
  ++mem;
  ++mem;
  ++mem;
  add_turns(m_party, world);
  add_turns(m_enemies, world);
}

Battle_State::~Battle_State()
{
  for(long i{0}; i < static_cast<long>(m_party.size()); ++i)
  {
    delete m_party[i];
    m_party[i] = nullptr;
    --mem;
  }
  for(long i{0}; i < static_cast<long>(m_enemies.size()); ++i)
  {
    delete m_enemies[i];
    m_enemies[i] = nullptr;
    --mem;
  }
}

void Battle_State::update(World* world)
{
  for(long i{0}; i < static_cast<long>(m_party.size()); ++i)
  {
    m_party[i]->update(world, &m_battle_event_queue);
  }
  for(long i{0}; i < static_cast<long>(m_enemies.size()); ++i)
  {
    m_enemies[i]->update(world, &m_battle_event_queue);
  }
}

tuple<bool, Game_State*, Game_State*> Battle_State::update_input(World* world, Music_Player* music_player, Input_Wrapper* input)
{
  if(m_battle_event_stack.empty() == false)
  {
    m_battle_event_stack.change_state();
  }
  if(m_battle_event_queue.empty() == true)
  {
    return make_tuple(true, nullptr, nullptr);
  }
  for(long i{0}; i < static_cast<long>(m_party.size()); ++i)
  {
    m_party[i]->update(world, &m_battle_event_queue);
  }
  for(long i{0}; i < static_cast<long>(m_enemies.size()); ++i)
  {
    m_enemies[i]->update(world, &m_battle_event_queue);
  }

  if(m_battle_event_stack.empty() == false)
  {
    m_battle_event_stack.update(&m_battle_event_stack, world, input);
  }
  else
  {
    m_battle_event_queue.update(&m_battle_event_stack);
    if(m_battle_event_queue.empty() == true)
    {
      add_turns(m_party, world);
      add_turns(m_enemies, world);
    }
    if(party_defeated(world) == true)
    {
      m_battle_event_queue.clear();
/*      deal with loss*/
    }
    else if(enemies_defeated(world) == true)
    {
      m_battle_event_queue.clear();
/*      deal with win*/
    }
  }
  return make_tuple(false, nullptr, nullptr);
}

void Battle_State::add_turns(vector<Battle_Character*> characters, const World* const world)
{
  for(long i{0}; i < static_cast<long>(characters.size()); ++i)
  {
    if(m_battle_event_queue.actor_has_event(characters[i]) == false && characters[i]->get_hp(world) > 0)
    {
      Battle_Event* e{new CETurn{characters[i], world, m_party, m_enemies}};
      m_battle_event_queue.push(e);
      ++mem;
    }
  }
}

bool Battle_State::party_defeated(const World* const world) const
{
  for(long i{0}; i < static_cast<long>(m_party.size()); ++i)
  {
    if(m_party[i]->get_hp(world) > 0)
    {
      return false;
    }
  }
  return true;
}

bool Battle_State::enemies_defeated(const World* const world) const
{
  for(long i{0}; i < static_cast<long>(m_enemies.size()); ++i)
  {
    if(m_enemies[i]->get_hp(world) > 0)
    {
      return false;
    }
  }
  return true;
}

void Battle_State::render(const World* const world) const
{
  m_renderer.render(world);
  for(long i{0}; i < static_cast<long>(m_party.size()); ++i)
  {
    m_party[i]->render(world);
  }
  for(long i{0}; i < static_cast<long>(m_enemies.size()); ++i)
  {
    m_enemies[i]->render(world);
  }
  m_battle_event_stack.render(world);
}

Battle_State_Renderer::Battle_State_Renderer()
{
  Image image{LoadImageFromMemory(".png", CELESTIAL_PLANE_BATTLE_BACKGROUND_IMAGE.m_data, CELESTIAL_PLANE_BATTLE_BACKGROUND_IMAGE.m_size)};
  m_battle_background = LoadTextureFromImage(image);
  UnloadImage(image);

/*  m_owner_panel = new Panel(TEXTBOX_PADDING_SCREEN, SCREEN_HEIGHT - (TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 4 + TEXTBOX_PADDING_SHORT * 2), SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2, TEXT_FONT_HEIGHT * 4 + TEXTBOX_PADDING_SHORT * 2);
*/  ++mem;
}

void Battle_State_Renderer::render(const World* const world) const
{
  DrawTexturePro(m_battle_background, Rectangle{0, 0, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT)}, Rectangle{static_cast<float>(0), static_cast<float>(0), static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
  m_owner_panel->render(world);
}

Battle_State_Renderer::~Battle_State_Renderer()
{
  UnloadTexture(m_battle_background);
  delete m_owner_panel;
  m_owner_panel = nullptr;
  --mem;
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

void Front_Menu_State::update(World* world)
{
  m_machine->update();
}

tuple<bool, Game_State*, Game_State*> Front_Menu_State::update_input(World* world, Music_Player* music_player, Input_Wrapper* input)
{
  if(input->X_button_pressed() == true || (m_machine->update_input(world, input) == true && input->B_button_pressed() == true))
  {
    g_sound_player->play_global_sound("Back");
    return make_tuple(true, nullptr, nullptr);
  }
  m_machine->change_state(world);
  return make_tuple(false, nullptr, nullptr);
}

void Front_Menu_State::render(const World* const world) const
{
  m_machine->render(world);
}
