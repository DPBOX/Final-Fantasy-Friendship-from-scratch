#ifndef GAME_STATE_H
#define GAME_STATE_H
#include "Battle.h"

class State_Manager;
class State_Machine;
class Panel;

class Game_State
{
  public:
    explicit Game_State(){}
    Game_State(const Game_State & obj) = delete;
    Game_State & operator =(const Game_State & obj) = delete;
    virtual ~Game_State(){}

    virtual string get_name() const;

    virtual void update(World* world) = 0;
    virtual tuple<bool, Game_State*, Game_State*> update_input(World* world, Music_Player* music_player, Input_Wrapper* input) = 0;
    virtual void render(const World* const world) const = 0;
  protected:
    string m_name{"Game State"};
};

class Title_State_Renderer
{
  public:
    explicit Title_State_Renderer(){}
    Title_State_Renderer(const Title_State_Renderer & obj) = delete;
    Title_State_Renderer & operator =(const Title_State_Renderer & obj) = delete;
    ~Title_State_Renderer(){}
    void render(const World* const world) const;
};

class Title_State : public Game_State
{
  public:
    explicit Title_State();
    Title_State(const Title_State & obj) = delete;
    Title_State & operator =(const Title_State & obj) = delete;
    virtual ~Title_State(){}

    virtual void update(World* world);
    virtual tuple<bool, Game_State*, Game_State*> update_input(World* world, Music_Player* music_player, Input_Wrapper* input);
    virtual void render(const World* const world) const;
  private:
    const Title_State_Renderer m_renderer{};
};

class Explore_State : public Game_State
{
  public:
    explicit Explore_State(Music_Player* music_player, const Map_Data & map_data, const long & start_script_index);
    Explore_State(const Explore_State & obj) = delete;
    Explore_State & operator =(const Explore_State & obj) = delete;
    virtual ~Explore_State();

    virtual void update(World* world);
    virtual tuple<bool, Game_State*, Game_State*> update_input(World* world, Music_Player* music_player, Input_Wrapper* input);
    virtual void render(const World* const world) const;
  private:
    Tilemap* m_map{nullptr};
    Script_Handler* m_script_handler{nullptr};
};

class Front_Menu_State : public Game_State
{
  public:
    explicit Front_Menu_State(World* world);
    Front_Menu_State(const Front_Menu_State & obj) = delete;
    Front_Menu_State & operator =(const Front_Menu_State & obj) = delete;
    virtual ~Front_Menu_State();

    virtual void update(World* world);
    virtual tuple<bool, Game_State*, Game_State*> update_input(World* world, Music_Player* music_player, Input_Wrapper* input);
    virtual void render(const World* const world) const;
  private:
    State_Machine* m_machine{nullptr};
    World* m_world{nullptr};
};

class Game_Over_State_Renderer
{
  public:
    explicit Game_Over_State_Renderer(){}
    Game_Over_State_Renderer(const Game_Over_State_Renderer & obj) = delete;
    Game_Over_State_Renderer & operator =(const Game_Over_State_Renderer & obj) = delete;
    ~Game_Over_State_Renderer(){}
    void render(const World* const world) const;
};

class Game_Over_State : public Game_State
{
  public:
    explicit Game_Over_State();
    Game_Over_State(const Game_Over_State & obj) = delete;
    Game_Over_State & operator =(const Game_Over_State & obj) = delete;
    virtual ~Game_Over_State(){}

    virtual void update(World* world);
    virtual tuple<bool, Game_State*, Game_State*> update_input(World* world, Music_Player* music_player, Input_Wrapper* input);
    virtual void render(const World* const world) const;
  private:
    const Game_Over_State_Renderer m_renderer{};
};

class Battle_State_Renderer
{
  public:
    explicit Battle_State_Renderer();
    Battle_State_Renderer(const Battle_State_Renderer & obj) = delete;
    Battle_State_Renderer & operator =(const Battle_State_Renderer & obj) = delete;
    ~Battle_State_Renderer();
    void render(const World* const world) const;
  private:
    Texture2D m_battle_background{};
    Panel* m_owner_panel{nullptr};
};

class Battle_State : public Game_State
{
  public:
    explicit Battle_State(const World* const world);
    Battle_State(const Battle_State & obj) = delete;
    Battle_State & operator =(const Battle_State & obj) = delete;
    virtual ~Battle_State();

    virtual void update(World* world);
    virtual tuple<bool, Game_State*, Game_State*> update_input(World* world, Music_Player* music_player, Input_Wrapper* input);
    virtual void render(const World* const world) const;
  private:
    void add_turns(vector<Battle_Character*> characters, const World* const world);
    bool party_defeated(const World* const world) const;
    bool enemies_defeated(const World* const world) const;

    const Battle_State_Renderer m_renderer{};
    vector<Battle_Character*> m_party{};
    vector<Battle_Character*> m_enemies{};
    Battle_Character* m_selected_character{nullptr};
    Battle_Event_Queue m_battle_event_queue{};
    Battle_Event_Stack m_battle_event_stack{};
};

class Battle_Transition_State_Renderer
{
  public:
    explicit Battle_Transition_State_Renderer(){};
    Battle_Transition_State_Renderer(const Battle_Transition_State_Renderer & obj) = delete;
    Battle_Transition_State_Renderer & operator =(const Battle_Transition_State_Renderer & obj) = delete;
    ~Battle_Transition_State_Renderer(){};
    void render(const World* const world, const long & alpha) const;
};

class Battle_Transition_State : public Game_State
{
  public:
    explicit Battle_Transition_State();
    Battle_Transition_State(const Battle_Transition_State & obj) = delete;
    Battle_Transition_State & operator =(const Battle_Transition_State & obj) = delete;
    virtual ~Battle_Transition_State(){}

    virtual void update(World* world);
    virtual tuple<bool, Game_State*, Game_State*> update_input(World* world, Music_Player* music_player, Input_Wrapper* input);
    virtual void render(const World* const world) const;
  private:
    long m_alpha{255};
    const Battle_Transition_State_Renderer m_renderer{};
};

class State_Manager
{
  public:
    explicit State_Manager();
    State_Manager(const State_Manager & obj) = delete;
    State_Manager & operator =(const State_Manager & obj) = delete;
    ~State_Manager();

    void change_state(const tuple<bool, Game_State*, Game_State*> & state);
    tuple<bool, Game_State*, Game_State*> update_input(World* world, Music_Player* music_player, Input_Wrapper* input);
    void render(World* world) const;
  private:
    vector<Game_State*> m_states{};
};

class Game
{
  public:
    explicit Game();
    Game(const Game & obj) = delete;
    Game & operator =(const Game & obj) = delete;
    ~Game();

    void update_music();
    void update();
    void render() const;
    void terminate_music();

  private:
    State_Manager* m_state_manager{nullptr};
    World* m_world{nullptr};
    Music_Player* m_music_player{nullptr};
    Input_Wrapper* m_input{nullptr};
    tuple<bool, Game_State*, Game_State*> m_next_state{};
};

#endif
