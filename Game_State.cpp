#include "Main.h"
#include "Game_State.h"
#include "Consts/Storyboard_Consts.h"
#include "Consts/Map_Consts.h"

Game::Game()
{
  m_state_manager = new State_Manager;
  ++mem;
  m_world = new World;
  ++mem;
  m_cursor = new Cursor;
  ++mem;
}

Game::~Game()
{
  delete m_state_manager;
  m_state_manager = nullptr;
  delete m_world;
  m_world = nullptr;
  delete m_cursor;
  m_cursor = nullptr;
  --mem;
  --mem;
  --mem;
}

void Game::update()
{
  m_state_manager->change_state();
  m_state_manager->update_input(m_world, m_cursor, m_state_manager);
  m_cursor->update();
  m_world->update();
}

void Game::render() const
{
  m_state_manager->render(m_world);
  m_cursor->render();
}

State_Manager::State_Manager()
{
  Game_State* e{new Title_State};
  ++mem;
  m_states.push_back(e);
  
  m_fonts.push_back(new Fnt);
  ++mem;
  m_fonts.push_back(new Fnt{HEADING_FONT});
  ++mem;
  m_fonts.push_back(new Fnt{CHARACTER_TITLE_FONT});
  ++mem;
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
  for(long i{0}; i < static_cast<long>(m_fonts.size()); ++i)
  {
    delete m_fonts[i];
    m_fonts[i] = nullptr;
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

void State_Manager::update_input(World* world, Cursor* cursor, State_Manager* state_manager)
{
  if(m_states.empty() == false)
  {
    m_states[m_states.size() - 1]->update_input(world, cursor, state_manager, m_fonts);
    for(long i{static_cast<long>(m_states.size()) - 2}; i >= 0; --i)
    {
      m_states[i]->update();
    }
  }
}

void State_Manager::render(World* world) const
{
  if(m_states.empty() == false)
  {
    for(long i{0}; i < static_cast<long>(m_states.size()); ++i)
    {
      m_states[i]->render(world, m_fonts);
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

void Title_State::update_input(World* world, Cursor* cursor, State_Manager* state_manager, const vector<Fnt*> & fonts)
{
  if(IsKeyPressed(KEY_Z) == true)
  {
    Game_State* e{new Explore_State(MAPS[0])};
    ++mem;
    state_manager->pop_state();
    state_manager->set_next_state(e);
  }
}

void Title_State::render(World* world, const vector<Fnt*> & fonts) const
{
  fonts[1]->render_text_center("Dungeon", SCREEN_HEIGHT / 4 - FONT_HEADING_HEIGHT / 2);
  fonts[0]->render_text_center("Press Z!", SCREEN_HEIGHT * 3 / 4);
  fonts[0]->render_text_center("(X is back.)", SCREEN_HEIGHT * 3 / 4 + FONT_TEXT_HEIGHT);
  fonts[0]->render_text_center("(S is open and close the menu. Only Items works.)", SCREEN_HEIGHT * 3 / 4 + FONT_TEXT_HEIGHT * 2);
}

Explore_State::Explore_State(const Map_Data & map_data, const Scr & start_script)
{
  m_map_handler = new Map_Handler;
  ++mem;
  m_name = "Explore State";
  m_map_handler->add_map(map_data, m_map_handler);
  m_map_handler->add_script(start_script);
}

Explore_State::~Explore_State()
{
  delete m_map_handler;
  m_map_handler = nullptr;
  --mem;
}

void Explore_State::update()
{
  m_map_handler->update();
}

void Explore_State::update_input(World* world, Cursor* cursor, State_Manager* state_manager, const vector<Fnt*> & fonts)
{
  world->unpause_time();
  m_map_handler->update_input(m_map_handler, cursor, world, fonts);

  if(IsKeyPressed(KEY_S) == true)
  {
    Game_State* m{new Front_Menu_State(world)};
    ++mem;
    state_manager->set_next_state(m);
  }
  
  if(m_map_handler->get_pop() == true)
  {
    state_manager->pop_state();
  }
  
  string next_state{m_map_handler->get_next_game_state()};
  if(next_state == "Game Over")
  {
    state_manager->set_next_state(new Game_Over_State());
    ++mem;
  }
}

void Explore_State::render(World* world, const vector<Fnt*> & fonts) const
{
  m_map_handler->render(fonts);
}

Game_Over_State::Game_Over_State()
{
  m_name = "Game Over";
}

void Game_Over_State::update_input(World* world, Cursor* cursor, State_Manager* state_manager, const vector<Fnt*> & fonts){}

void Game_Over_State::render(World* world, const vector<Fnt*> & fonts) const
{
  fonts[1]->render_text_center("End of Demo", SCREEN_HEIGHT / 2 - FONT_HEADING_HEIGHT / 2);
}

Front_Menu_State::Front_Menu_State(World* world)
{
  m_machine = new State_Machine;
  ++mem;
  m_machine->set_start_state_front_menu(world);
  m_name = "Front Menu State";
}

Front_Menu_State::~Front_Menu_State()
{
  delete m_machine;
  m_machine = nullptr;
  --mem;
}

void Front_Menu_State::update()
{
  m_machine->update();
}

void Front_Menu_State::update_input(World* world, Cursor* cursor, State_Manager* state_manager, const vector<Fnt*> & fonts)
{
  world->pause_time();
  m_machine->update_input(m_machine, cursor, world);
  if(IsKeyPressed(KEY_S) == true || (IsKeyPressed(KEY_X) == true && m_machine->check_exit() == true))
  {
    state_manager->pop_state();
  }
  m_machine->change_state(world);
}

void Front_Menu_State::render(World* world, const vector<Fnt*> & fonts) const
{
  m_machine->render(world, fonts);
}