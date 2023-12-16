#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Script_Structs.h"
#include "Consts/Storyboard_Consts.h"
#include "World.h"
#include "Tilemap.h"
#include "State_Machine.h"

class State_Manager;
class Map_Handler;

class Game_State
{
  public:
    explicit Game_State(){}
    Game_State(const Game_State & obj) = delete;
    Game_State & operator =(const Game_State & obj) = delete;
    virtual ~Game_State(){}

    virtual string get_name() const;

    virtual void update() = 0;
    virtual void update_input(World* world, State_Manager* state_manager) = 0;
    virtual void render(World* world) const = 0;
  protected:
    string m_name{"Game State"};
};

class Title_State : public Game_State
{
  public:
    explicit Title_State();
    Title_State(const Title_State & obj) = delete;
    Title_State & operator =(const Title_State & obj) = delete;
    virtual ~Title_State(){}

    virtual void update(){}
    virtual void update_input(World* world, State_Manager* state_manager);
    virtual void render(World* world) const;
};

class Explore_State : public Game_State
{
  public:
    explicit Explore_State(const Map_Data & map_data, const Scr & start_script = DUMMY_SCRIPT);
    Explore_State(const Explore_State & obj) = delete;
    Explore_State & operator =(const Explore_State & obj) = delete;
    virtual ~Explore_State();

    virtual void update(){}
    virtual void update_input(World* world, State_Manager* state_manager);
    virtual void render(World* world) const;
  private:
    Map_Handler* m_map_handler{nullptr};
};

class Front_Menu_State : public Game_State
{
  public:
    explicit Front_Menu_State(World* world);
    Front_Menu_State(const Front_Menu_State & obj) = delete;
    Front_Menu_State & operator =(const Front_Menu_State & obj) = delete;
    virtual ~Front_Menu_State();

    virtual void update();
    virtual void update_input(World* world, State_Manager* state_manager);
    virtual void render(World* world) const;
  private:
    State_Machine* m_machine{nullptr};
};

class Game_Over_State : public Game_State
{
  public:
    explicit Game_Over_State();
    Game_Over_State(const Game_Over_State & obj) = delete;
    Game_Over_State & operator =(const Game_Over_State & obj) = delete;
    virtual ~Game_Over_State(){}

    virtual void update(){}
    virtual void update_input(World* world, State_Manager* state_manager);
    virtual void render(World* world) const;
};

class State_Manager
{
  public:
    explicit State_Manager();
    State_Manager(const State_Manager & obj) = delete;
    State_Manager & operator =(const State_Manager & obj) = delete;
    ~State_Manager();

    void set_next_state(Game_State* new_state);
    void pop_state();

    void change_state();

    void update_input(World* world, State_Manager* state_manager);
    void render(World* world) const;
  private:
    vector<Game_State*> m_states{};
    Game_State* m_next_state{nullptr};
    bool m_pop{false};
};

class Game
{
  public:
    explicit Game();
    Game(const Game & obj) = delete;
    Game & operator =(const Game & obj) = delete;
    ~Game();

    void update();
    void render() const;

  private:
    State_Manager* m_state_manager{nullptr};
    World* m_world{nullptr};
};

#endif