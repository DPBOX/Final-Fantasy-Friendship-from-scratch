#include "Main.h"
#include "Game_State.h"

Game::Game()
{
  m_state_manager = new State_Manager;
  ++mem;
  m_world = new World;
  ++mem;
}

Game::~Game()
{
  delete m_state_manager;
  m_state_manager = nullptr;
  delete m_world;
  m_world = nullptr;
  --mem;
  --mem;
}

void Game::update()
{
  m_state_manager->change_state();
  m_state_manager->update_input(m_world, m_state_manager);
  m_world->update();
}

void Game::render() const
{
  m_state_manager->render(m_world);
  m_world->render_cursor();
}

State_Manager::State_Manager()
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

void State_Manager::update_input(World* world, State_Manager* state_manager)
{
  if(m_states.empty() == false)
  {
    m_states[m_states.size() - 1]->update_input(world, state_manager);
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

void Title_State::update_input(World* world, State_Manager* state_manager)
{
  if(IsKeyPressed(KEY_Z) == true)
  {
    Game_State* e{new Explore_State(MAPS[0])};
    ++mem;
    state_manager->pop_state();
    state_manager->set_next_state(e);
  }
}

void Title_State::render(World* world) const
{
  world->render_text_center(1, "Dungeon", SCREEN_HEIGHT / 4 - FONT_HEADING_HEIGHT / 2);
  world->render_text_center(0, "Press Z!", SCREEN_HEIGHT * 3 / 4);
  world->render_text_center(0, "(X is back.)", SCREEN_HEIGHT * 3 / 4 + FONT_TEXT_HEIGHT);
  world->render_text_center(0, "(S is open and close the menu.)", SCREEN_HEIGHT * 3 / 4 + FONT_TEXT_HEIGHT * 2);
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

void Explore_State::update_input(World* world, State_Manager* state_manager)
{
  world->unpause_time();
  m_map_handler->update_input(m_map_handler, world);

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

void Explore_State::render(World* world) const
{
  m_map_handler->render(m_map_handler, world);
}

Game_Over_State::Game_Over_State()
{
  m_name = "Game Over";
}

void Game_Over_State::update_input(World* world, State_Manager* state_manager){}

void Game_Over_State::render(World* world) const
{
  world->render_text_center(1, "End of Demo", SCREEN_HEIGHT / 2 - FONT_HEADING_HEIGHT / 2);
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

void Front_Menu_State::update_input(World* world, State_Manager* state_manager)
{
  world->pause_time();
  m_machine->update_input(m_machine, world);
  if(IsKeyPressed(KEY_S) == true || (IsKeyPressed(KEY_X) == true && m_machine->check_exit() == true))
  {
    state_manager->pop_state();
    world->play_global_sound("Back");
  }
  m_machine->change_state(world);
}

void Front_Menu_State::render(World* world) const
{
  m_machine->render(world);
}
