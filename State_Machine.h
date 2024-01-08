#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "World.h"

//State Machine class
class State_Machine
{
  public:
    explicit State_Machine(){}
    void set_start_state_front_menu(World* world);
    State_Machine(const State_Machine & obj) = delete;
    State_Machine & operator =(const State_Machine & obj) = delete;
    ~State_Machine();

    void update();
    void update_input(State_Machine* machine, World* world);
    void change_state(World* world);    //State changer
    void render(World* world) const;
    
    // checks if the current state is an exit state
    bool check_exit() const;
    
  private:
    class Machine_State;
    class Front_Menu;
    class Item_Menu;
    class Status_Menu;
    
    enum state_list
    {
      NULL_STATE,
      FRONT_MENU_STATE,
      ITEM_MENU_STATE,
      STATUS_MENU_STATE
    };
  
    //State variables
    long state_ID{-1};
    long next_state{-1};

    //Game state object
    Machine_State* current_state{nullptr};
    
    //State status manager
    void set_next_state(const state_list & new_state, const string & selected_party_member_name = "NULL");
    
    string m_selected_party_member_name{"NULL"};
};

//Game state base class
class State_Machine::Machine_State
{
  private:
    friend class State_Machine;
    explicit Machine_State(){}
    Machine_State(const Machine_State & obj) = delete;
    Machine_State & operator =(const Machine_State & obj) = delete;
    virtual void update() = 0;
    virtual void update_input(State_Machine* machine, World* world) = 0;
    virtual void render(World* world) const = 0;
    virtual ~Machine_State(){};
    virtual bool root_menu_cursor_shown() const;
};

class State_Machine::Front_Menu : private State_Machine::Machine_State
{
  private:
    friend class State_Machine;
    explicit Front_Menu(World* world);
    Front_Menu(const Front_Menu & obj) = delete;
    Front_Menu & operator =(const Front_Menu & obj) = delete;
    virtual ~Front_Menu();
    
    //Main Loop Functons
    virtual void update(){}
    virtual void update_input(State_Machine* machine, World* world);
    virtual void render(World* world) const;
    
    virtual bool root_menu_cursor_shown() const;
    string split_map_name_text(const bool & line_number) const;
    
    Panel* m_gold{nullptr};
    Panel* m_map{nullptr};
    Panel* m_party{nullptr};
    Panel* m_menu{nullptr};
    Panel* m_formation{nullptr};
    Selection<string>* m_selection{nullptr};
    Selection<Player_Summary>* m_party_menu{nullptr};
    string m_top_bar_text{"Current Map Name"};
    Texture2D m_panel_texture{};
    vector<Player_Summary*> m_party_info{};
    long m_option_selected{-1};
};

class State_Machine::Item_Menu : private State_Machine::Machine_State
{
  private:
    friend class State_Machine;
    explicit Item_Menu();
    Item_Menu(const Item_Menu & obj) = delete;
    Item_Menu & operator =(const Item_Menu & obj) = delete;
    virtual ~Item_Menu();
    
    //Main Loop Functons
    virtual void update(){}
    virtual void update_input(State_Machine* machine, World* world);
    virtual void render(World* world) const;
    
    Panel* m_switch{nullptr};
    Panel* m_item_text{nullptr};
    Panel* m_description{nullptr};
    Panel* m_item_list{nullptr};
    Selection<string>* m_category{nullptr};
    Selection<string>* m_items{nullptr};
    Selection<string>* m_equipment{nullptr};
    Selection<string>* m_key_items{nullptr};
    string m_top_bar_text{"Items"};
    Texture2D m_panel_texture{};
    Texture2D m_arrow_texture{};
};

class State_Machine::Status_Menu : private State_Machine::Machine_State
{
  private:
    friend class State_Machine;
    explicit Status_Menu(const string & character_name);
    Status_Menu(const Status_Menu & obj) = delete;
    Status_Menu & operator =(const Status_Menu & obj) = delete;
    virtual ~Status_Menu();
    
    //Main Loop Functons
    virtual void update(){}
    virtual void update_input(State_Machine* machine, World* world);
    virtual void render(World* world) const;
    
    Texture2D m_panel_texture{};
    string m_character_name{"NULL"};
    Panel* m_panel{nullptr};
    Selection<string>* m_selection{nullptr};
    Progress_Bar* m_hp{};
    Progress_Bar* m_mp{};
    Progress_Bar* m_exp{};
    Progress_Bar* m_soul_break{};
    Progress_Bar* m_scroll{};
};

#endif