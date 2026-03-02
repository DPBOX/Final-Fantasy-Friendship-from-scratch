#ifndef BATTLE_H
#define BATTLE_H
#include "Animation.h"

class Battle_Event_Queue;
class Progress_Bar;
class Selection;
class Selection_Renderer;
class Panel;

class Battle_Character
{
  public:
    explicit Battle_Character(){}
    Battle_Character(const Battle_Character & obj) = delete;
    Battle_Character & operator =(const Battle_Character & obj) = delete;
    virtual ~Battle_Character(){}

    virtual void update(World* world, const Battle_Event_Queue* const battle_event_queue) = 0;
    virtual void render(const World* const world) const = 0;

    virtual bool is_ally() const{return m_ally;}
    virtual string get_name() const{return m_name;}
    virtual long get_speed(const World* const world) const = 0;
    virtual long get_hp(const World* const world) const = 0;
    virtual void change_animation(const long & animation_index, const long & animation_speed, const bool & loop){m_animation = Animation(m_animation_list[animation_index], m_animation_list[animation_index].size() - 1, loop, animation_speed);}
    virtual void enable_animations(){m_animations_enabled = true;}
    virtual void disable_animations(){m_animations_enabled = false;}
    virtual void enable_render_arrow(){m_render_arrow = true;}
    virtual void disable_render_arrow(){m_render_arrow = false;}
  protected:
    // the character's name
    string m_name{"NULL"};
    // which side the character is on
    bool m_ally{true};
    // its index in the ally or enemy list. This will also determine its position on the battlefield
    long m_list_index{0};
    //The animation it's currently playing
    Animation m_animation{vector<long>{}, 0, false, 0};
    //A list of the character's animations
    vector<vector<long>> m_animation_list{};
    //Enables some of the character's animations if true
    bool m_animations_enabled{false};
    //The arrow icon over the character's sprite when it is selected
    Texture2D m_battle_arrow_icon_texture{};
    //The arrow icon's animation
    Animation m_arrow_icon_animation{BATTLE_ARROW_ICON_ANIM, 0, true, BATTLE_ARROW_ICON_ANIMATION_SPEED};
    //whether or not to render the arrow icon
    bool m_render_arrow{false};
};

class Battle_Ally : public Battle_Character
{
  public:
    explicit Battle_Ally(const string & name, const long & list_index, const long & animation_speed, const vector<vector<long>> & animation_list);
    Battle_Ally(const Battle_Ally & obj) = delete;
    Battle_Ally & operator =(const Battle_Ally & obj) = delete;
    virtual ~Battle_Ally();

    virtual void update(World* world, const Battle_Event_Queue* const battle_event_queue);
    virtual void render(const World* const world) const;

    virtual long get_speed(const World* const world) const{return world->get_party_member_stat(m_name, "Speed");}
    virtual long get_hp(const World* const world) const{return world->get_party_member_unmodified_stat(m_name, "HP");}
    virtual void update_animations(){m_font_animation.update();}
  private:
    Progress_Bar* m_hp{nullptr};
    Progress_Bar* m_mp{nullptr};
    Progress_Bar* m_atb{nullptr};
    Progress_Bar* m_soulbreak{nullptr};
    Blinking_Animation m_font_animation{true, false, BLINKING_ANIMATION_SPEED};
};

class Battle_Enemy : public Battle_Character
{
  public:
    explicit Battle_Enemy(const Enemy_Info & enemy, const long & list_index, const long & animation_speed);
    Battle_Enemy(const Battle_Enemy & obj) = delete;
    Battle_Enemy & operator =(const Battle_Enemy & obj) = delete;
    virtual ~Battle_Enemy(){UnloadTexture(m_sprite); UnloadTexture(m_battle_arrow_icon_texture);}

    virtual void update(World* world, const Battle_Event_Queue* const battle_event_queue);
    virtual void render(const World* const world) const;

    virtual long get_speed(const World* const world) const;
    virtual long get_hp(const World* const world) const;
  private:
    Stats m_stats{};
    Texture2D m_sprite{};
    long m_sprite_width{1};
};

class Battle_Event_Stack;

class Battle_Event_Stack_State
{
  public:
    explicit Battle_Event_Stack_State(){}
    Battle_Event_Stack_State(const Battle_Event_Stack_State & obj) = delete;
    Battle_Event_Stack_State & operator =(const Battle_Event_Stack_State & obj) = delete;
    virtual ~Battle_Event_Stack_State(){}

    virtual string get_name() const;

    virtual void update(){}
    virtual void update_top(Battle_Event_Stack* state_manager, World* world, Input_Wrapper* input) = 0;
    virtual void render(const World* const world) const = 0;
  protected:
    string m_name{"Battle Event Stack State"};
    vector<Battle_Character*> m_party{};
    vector<Battle_Character*> m_enemies{};
};

class Combat_Choice_State : public Battle_Event_Stack_State
{
  public:
    explicit Combat_Choice_State(Battle_Character* owner, vector<Battle_Character*> party, vector<Battle_Character*> enemies);
    Combat_Choice_State(const Combat_Choice_State & obj) = delete;
    Combat_Choice_State & operator =(const Combat_Choice_State & obj) = delete;
    virtual ~Combat_Choice_State();

    virtual void update_top(Battle_Event_Stack* state_manager, World* world, Input_Wrapper* input);
    virtual void render(const World* const world) const;
  protected:
    Battle_Character* m_character{nullptr};
    Selection* m_commands{nullptr};

    Selection_Renderer* m_commands_renderer{};
    Panel* m_panel{nullptr};
};

enum class Combat_Target_Mode{Single_Foe, All_Foes, Single_All_Foes, Single_Ally, All_Allies, Single_All_Allies, Anyone, Everyone, User};

class Combat_Target_State : public Battle_Event_Stack_State
{
  public:
    explicit Combat_Target_State(Battle_Character* owner, const Combat_Target_Mode & target_mode, vector<Battle_Character*> party, vector<Battle_Character*> enemies);
    Combat_Target_State(const Combat_Target_State & obj) = delete;
    Combat_Target_State & operator =(const Combat_Target_State & obj) = delete;
    virtual ~Combat_Target_State();

    virtual void update_top(Battle_Event_Stack* state_manager, World* world, Input_Wrapper* input);
    virtual void render(const World* const world) const;
  protected:
    Battle_Character* m_character{nullptr};
    Selection* m_commands{nullptr};

    Selection_Renderer* m_commands_renderer{};
    Panel* m_panel{nullptr};
    long m_num_choices{1};
    Combat_Target_Mode m_target_mode{Combat_Target_Mode::Single_Foe};
};

class Battle_Event_Stack
{
  public:
    explicit Battle_Event_Stack(){}
    Battle_Event_Stack(const Battle_Event_Stack & obj) = delete;
    Battle_Event_Stack & operator =(const Battle_Event_Stack & obj) = delete;
    ~Battle_Event_Stack();

    void set_next_state(Battle_Event_Stack_State* new_state);
    void set_next_state2(Battle_Event_Stack_State* new_state);
    void pop_state();
    void pop_all();

    void change_state();
    bool empty();

    void create_new_combat_choice_state(Battle_Character* owner, vector<Battle_Character*> party, vector<Battle_Character*> enemies);
    void create_new_combat_target_state(Battle_Character* owner, const Combat_Target_Mode & target_mode, vector<Battle_Character*> party, vector<Battle_Character*> enemies);

    void update(Battle_Event_Stack* state_manager, World* world, Input_Wrapper* input);
    void render(const World* const world) const;

  private:
    vector<Battle_Event_Stack_State*> m_states{};
    Battle_Event_Stack_State* m_next_state{nullptr};
    Battle_Event_Stack_State* m_next_state2{nullptr};
    bool m_pop{false};
    bool m_pop_all{false};
};

class Battle_Event_Comparator;

class Battle_Event
{
  public:
    explicit Battle_Event(){}
    Battle_Event(const Battle_Event & obj) = delete;
    Battle_Event & operator =(const Battle_Event & obj) = delete;
    virtual ~Battle_Event(){}
    virtual bool operator >(const Battle_Event & e) const
    {
      if(m_count_down > e.get_count_down())
      {
        return true;
      }
      return false;
    }
    virtual void execute(priority_queue<Battle_Event*, vector<Battle_Event*>, Battle_Event_Comparator> & queue, Battle_Event_Stack* state_stack) = 0;
    virtual void update() = 0;
    virtual bool is_finished() const{return m_finished;}
    virtual long get_count_down() const{return m_count_down;}
    virtual Battle_Character* get_owner() const{return m_owner;}
    virtual void reduce_count_down();
    virtual string get_name() const{return m_name;}
  protected:
    string m_name{"NULL"};
    long m_count_down{-2};
    Battle_Character* m_owner{nullptr};
    Battle_Character* m_target{nullptr};
    bool m_finished{false};
    vector<Battle_Character*> m_party{};
    vector<Battle_Character*> m_enemies{};
};

struct Battle_Event_Comparator
{
  bool operator()(const Battle_Event* lhs, const Battle_Event* rhs) const
  {
    return *lhs > *rhs;
  }
};

class CETurn : public Battle_Event
{
  public:
    explicit CETurn(Battle_Character* owner, const World* const world, vector<Battle_Character*> party, vector<Battle_Character*> enemies);
    virtual void execute(priority_queue<Battle_Event*, vector<Battle_Event*>, Battle_Event_Comparator> & queue, Battle_Event_Stack* state_stack);
    virtual void update(){}
};

class Battle_Event_Queue
{
  public:
    explicit Battle_Event_Queue(){}
    Battle_Event_Queue(const Battle_Event_Queue & obj) = delete;
    Battle_Event_Queue & operator =(const Battle_Event_Queue & obj) = delete;
    ~Battle_Event_Queue(){clear();}
    void update(Battle_Event_Stack* state_stack);
    void push(Battle_Event* e){m_queue.push(e);}
    bool actor_has_event(Battle_Character*) const;
    void remove_events_owned_by(Battle_Character*);
    void clear();
    bool empty() const{return m_queue.empty() && m_current_event == nullptr;}
    long get_character_atb_position(const string & name) const;
  private:
    priority_queue<Battle_Event*, vector<Battle_Event*>, Battle_Event_Comparator> m_queue{};
    Battle_Event* m_current_event{nullptr};
};

#endif
