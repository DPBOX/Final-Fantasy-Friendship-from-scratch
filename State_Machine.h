#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "UI.h"

//State Machine class
class State_Machine
{
  public:
    explicit State_Machine(){}
    void set_start_state_front_menu(const World* const world);
    State_Machine(const State_Machine & obj) = delete;
    State_Machine & operator =(const State_Machine & obj) = delete;
    ~State_Machine();

    void update();
    void update_input(State_Machine* machine, World* world);
    void change_state(const World* const world);    //State changer
    void render(const World* const world) const;
    
    // checks if the current state is an exit state
    bool check_exit() const;
    
  private:
    class Machine_State;
    class Front_Menu;
    class Item_Menu;
    class Status_Menu;
    class Machine_State_Renderer;
    class Front_Menu_Renderer;
    class Item_Menu_Renderer;
    class Status_Menu_Renderer;
    
    enum state_list
    {
      NULL_STATE,
      FRONT_MENU_STATE,
      ITEM_MENU_STATE,
      STATUS_MENU_STATE
    };
  
    //State variables
    long m_state_ID{-1};
    long m_next_state{-1};
    string m_selected_party_member{"NULL"};

    //Game state object
    Machine_State* m_current_state{nullptr};
    Machine_State_Renderer* m_current_state_renderer{nullptr};
    
    //State status manager
    void set_next_state(const state_list & new_state, const string & selected_party_member = "NULL");
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
    virtual ~Machine_State(){};
    virtual bool root_menu_cursor_shown() const;
};

//Game state base class
class State_Machine::Machine_State_Renderer
{
  private:
    friend class State_Machine;
    explicit Machine_State_Renderer(){}
    Machine_State_Renderer(const Machine_State_Renderer & obj) = delete;
    Machine_State_Renderer & operator =(const Machine_State_Renderer & obj) = delete;
    virtual void render(const World* const world) const = 0;
    virtual ~Machine_State_Renderer(){};
};

class State_Machine::Front_Menu : private State_Machine::Machine_State
{
  public:
    const Selection* get_selection() const;
    const Selection* get_party_menu() const;
    string get_option_selected() const;
    void render_party_info(const World* const world) const;
  private:
    friend class State_Machine;
    explicit Front_Menu(const World* const world);
    Front_Menu(const Front_Menu & obj) = delete;
    Front_Menu & operator =(const Front_Menu & obj) = delete;
    virtual ~Front_Menu();
    
    //Main Loop Functons
    virtual void update(){}
    virtual void update_input(State_Machine* machine, World* world);
    
    virtual bool root_menu_cursor_shown() const;

    Selection* m_selection{nullptr};
    Selection* m_party_menu{nullptr};
    List<Player_Summary> m_party_info{};
    string m_option_selected{"NULL"};
};

class State_Machine::Front_Menu_Renderer : private State_Machine::Machine_State_Renderer
{
  private:
    friend class State_Machine;
    explicit Front_Menu_Renderer(const State_Machine::Front_Menu* const front_menu) :
                                 m_gold(new Panel(TEXTBOX_PADDING_SCREEN, SCREEN_HEIGHT - (2 * TEXT_FONT_HEIGHT + TEXTBOX_PADDING_SHORT * 2) - TEXTBOX_PADDING_SCREEN_Y, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT, 2 * TEXT_FONT_HEIGHT + TEXTBOX_PADDING_SHORT * 2)),
                                 m_map(new Panel(TEXTBOX_PADDING_SCREEN, SCREEN_HEIGHT - ((2 * TEXT_FONT_HEIGHT + TEXTBOX_PADDING_SHORT * 2) * 2) - TEXTBOX_PADDING_SCREEN_Y, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT, 2 * TEXT_FONT_HEIGHT + TEXTBOX_PADDING_SHORT * 2)),
                                 m_party_panel(new Panel(TEXTBOX_PADDING_SCREEN + (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT, TEXTBOX_PADDING_SCREEN_Y, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) - (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT, SCREEN_HEIGHT - TEXTBOX_PADDING_SCREEN_Y * 2)),
                                 m_menu(new Panel(TEXTBOX_PADDING_SCREEN, TEXTBOX_PADDING_SCREEN_Y, (SCREEN_WIDTH  - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT, TEXT_FONT_HEIGHT * NUM_FRONT_MENU_CHOICES + TEXTBOX_PADDING_SHORT * 2)),
                                 m_formation(new Panel(TEXTBOX_PADDING_SCREEN, TEXTBOX_PADDING_SCREEN_Y, (SCREEN_WIDTH  - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT, TEXT_FONT_HEIGHT * FORMATION_MENU_TEXT.size() + TEXTBOX_PADDING_SHORT * 2)),
                                 m_selection_renderer(new Selection_Renderer(front_menu->get_selection(), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SHORT + TEXTBOX_PADDING_SCREEN_Y, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT)),
                                 m_party_menu_renderer(new Selection_Renderer(front_menu->get_party_menu(), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT, TEXTBOX_PADDING_SHORT + TEXTBOX_PADDING_SCREEN_Y + PLAYER_SUMMARY_SECTION_PADDING, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) - (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT, TEXT_FONT_HEIGHT * 4 + PLAYER_SUMMARY_SECTION_PADDING)), m_front_menu(front_menu){mem += 7;}
    Front_Menu_Renderer(const Front_Menu_Renderer & obj) = delete;
    Front_Menu_Renderer & operator =(const Front_Menu_Renderer & obj) = delete;
    virtual ~Front_Menu_Renderer();

    //Main Loop Functons
    virtual void render(const World* const world) const;

    string split_map_name_text(const bool & line_number) const;
    string get_play_time(const double & play_time_ticks) const;

    const Panel* const m_gold{};
    const Panel* const m_map{};
    const Panel* const m_party_panel{};
    const Panel* const m_menu{};
    const Panel* const m_formation{};
    const Selection_Renderer* const m_selection_renderer{};
    const Selection_Renderer* const m_party_menu_renderer{};
    const string m_top_bar_text{"Current Map Name"};

    const State_Machine::Front_Menu* const m_front_menu{};
};

class State_Machine::Item_Menu : private State_Machine::Machine_State
{
  public:
    const Selection* get_category_menu() const;
    const Selection* get_item_menu() const;
    const Selection* get_key_item_menu() const;
  private:
    friend class State_Machine;
    explicit Item_Menu(const World* const world) : m_category(new Selection(NUM_ITEM_MENU_CHOICES, NUM_ITEM_MENU_CHOICES, 1, 1)), m_items_menu(new Selection(world->get_number_of_items(), NUM_ITEM_MENU_COLUMNS, MAX_ITEM_MENU_ROWS, ITEM_MENU_ROWS, false, true)), m_key_items_menu(new Selection(world->get_number_of_key_items(), NUM_ITEM_MENU_COLUMNS, MAX_ITEM_MENU_ROWS, ITEM_MENU_ROWS, false, false)){mem += 3;}
    Item_Menu(const Item_Menu & obj) = delete;
    Item_Menu & operator =(const Item_Menu & obj) = delete;
    virtual ~Item_Menu();
    
    //Main Loop Functons
    virtual void update(){}
    virtual void update_input(State_Machine* machine, World* world);

    Selection* m_category{nullptr};
    Selection* m_items_menu{nullptr};
    Selection* m_key_items_menu{nullptr};
};

class State_Machine::Item_Menu_Renderer : private State_Machine::Machine_State_Renderer
{
  private:
    friend class State_Machine;
    explicit Item_Menu_Renderer(const State_Machine::Item_Menu* const item_menu) :
                                m_switch(new Panel(TEXTBOX_PADDING_SCREEN + (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / ITEM_MENU_SPLIT, TEXTBOX_PADDING_SCREEN_Y, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) - (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / ITEM_MENU_SPLIT, TEXT_FONT_HEIGHT + TEXTBOX_PADDING_SHORT * 2)),
                                m_item_text(new Panel(TEXTBOX_PADDING_SCREEN, TEXTBOX_PADDING_SCREEN_Y, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / ITEM_MENU_SPLIT, TEXT_FONT_HEIGHT + TEXTBOX_PADDING_SHORT * 2)),
                                m_description(new Panel(TEXTBOX_PADDING_SCREEN, TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT + TEXTBOX_PADDING_SHORT * 2, SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2, TEXT_FONT_HEIGHT + TEXTBOX_PADDING_SHORT * 2)),
                                m_item_list(new Panel(TEXTBOX_PADDING_SCREEN, TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 2 + TEXTBOX_PADDING_SHORT * 4, SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2, SCREEN_HEIGHT - TEXTBOX_PADDING_SCREEN_Y * 2 - (TEXT_FONT_HEIGHT + TEXTBOX_PADDING_SHORT * 2) * 2)),
                                m_category_renderer(new Selection_Renderer(item_menu->get_category_menu(), TEXTBOX_PADDING_SCREEN + (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / ITEM_MENU_SPLIT + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT, SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2 - ((SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / ITEM_MENU_SPLIT))),
                                m_items_renderer(new Selection_Renderer(item_menu->get_item_menu(), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 2 + TEXTBOX_PADDING_SHORT * 5, SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2)),
                                m_key_items_renderer(new Selection_Renderer(item_menu->get_key_item_menu(), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 2 + TEXTBOX_PADDING_SHORT * 5, SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2)){mem += 7;}
    Item_Menu_Renderer(const Item_Menu_Renderer & obj) = delete;
    Item_Menu_Renderer & operator =(const Item_Menu_Renderer & obj) = delete;
    virtual ~Item_Menu_Renderer();

    //Main Loop Functons
    virtual void render(const World* const world) const;

    const Panel* const m_switch{nullptr};
    const Panel* const m_item_text{nullptr};
    const Panel* const m_description{nullptr};
    const Panel* const m_item_list{nullptr};
    const Selection_Renderer* const m_category_renderer{};
    const Selection_Renderer* const m_items_renderer{};
    const Selection_Renderer* const m_key_items_renderer{};
    const string m_top_bar_text{"Items"};
};

class State_Machine::Status_Menu : private State_Machine::Machine_State
{
  public:
    const Selection* get_selection_menu() const;
    const Selection* get_weapons_menu() const;
    const Selection* get_shields_menu() const;
    const Selection* get_helms_menu() const;
    const Selection* get_armor_menu() const;
    const Selection* get_accessories_menu() const;
    string get_character() const{return m_character;}
    long get_slot() const{return m_slot;}
    void render_hp_bar(const World* const world, const long & x, const long & y) const;
    void render_mp_bar(const World* const world, const long & x, const long & y) const;
    void render_exp_bar(const World* const world, const long & x, const long & y) const;
    void render_soul_bar(const World* const world, const long & x, const long & y) const;
    void render_scroll_bar(const World* const world, const long & x, const long & y) const;
  private:
    friend class State_Machine;
    explicit Status_Menu(const World* const world, const string & selected_party_member) : m_character(selected_party_member), m_selection_menu(new Selection(static_cast<long>(STAT_STRINGS.size()), NUM_STATUS_MENU_COLUMNS, STATUS_MENU_ROWS, STATUS_MENU_ROWS, true, true)),
                    m_weapons_menu(new Selection(world->get_number_of_equipped_and_inventory_weapons(), NUM_EQUIPMENT_MENU_COLUMNS, MAX_NUM_EQUIPMENT_MENU_ROWS, NUM_EQUIPMENT_MENU_ROWS, false, false)),
                    m_shields_menu(new Selection(world->get_number_of_equipped_and_inventory_shields(), NUM_EQUIPMENT_MENU_COLUMNS, MAX_NUM_EQUIPMENT_MENU_ROWS, NUM_EQUIPMENT_MENU_ROWS, false, false)),
                    m_helms_menu(new Selection(world->get_number_of_equipped_and_inventory_helms(), NUM_EQUIPMENT_MENU_COLUMNS, MAX_NUM_EQUIPMENT_MENU_ROWS, NUM_EQUIPMENT_MENU_ROWS, false, false)),
                    m_armor_menu(new Selection(world->get_number_of_equipped_and_inventory_armor(), NUM_EQUIPMENT_MENU_COLUMNS, MAX_NUM_EQUIPMENT_MENU_ROWS, NUM_EQUIPMENT_MENU_ROWS, false, false)),
                    m_accessories_menu(new Selection(world->get_number_of_equipped_and_inventory_accessories(), NUM_EQUIPMENT_MENU_COLUMNS, MAX_NUM_EQUIPMENT_MENU_ROWS, NUM_EQUIPMENT_MENU_ROWS, false, false)),
                    m_hp(new Progress_Bar{"Progress Bar Green", ((SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3) - STATUS_PROGRESS_BAR_PADDING}),
                    m_mp(new Progress_Bar{"Progress Bar Blue", ((SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3) - STATUS_PROGRESS_BAR_PADDING}),
                    m_exp(new Progress_Bar{"Progress Bar Pink", ((SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3) - STATUS_PROGRESS_BAR_PADDING}),
                    m_soul_break(new Progress_Bar{"Progress Bar Red", ((SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3) - STATUS_PROGRESS_BAR_PADDING}),
                    m_scroll(new Progress_Bar{"Progress Bar Orange", ((SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3) - STATUS_PROGRESS_BAR_PADDING}){mem += 11;}
    Status_Menu(const Status_Menu & obj) = delete;
    Status_Menu & operator =(const Status_Menu & obj) = delete;
    virtual ~Status_Menu();
    
    //Main Loop Functons
    virtual void update(){}
    virtual void update_input(State_Machine* machine, World* world);

    string m_character{"NULL"};
    Selection* m_selection_menu{nullptr};
    Selection* m_weapons_menu{nullptr};
    Selection* m_shields_menu{nullptr};
    Selection* m_helms_menu{nullptr};
    Selection* m_armor_menu{nullptr};
    Selection* m_accessories_menu{nullptr};
    Progress_Bar* m_hp{};
    Progress_Bar* m_mp{};
    Progress_Bar* m_exp{};
    Progress_Bar* m_soul_break{};
    Progress_Bar* m_scroll{};
    long m_slot{0};
};

class State_Machine::Status_Menu_Renderer : private State_Machine::Machine_State_Renderer
{
  private:
    friend class State_Machine;
    explicit Status_Menu_Renderer(const State_Machine::Status_Menu* const status_menu) : m_status_menu(status_menu),
    m_panel(new Panel(TEXTBOX_PADDING_SCREEN, TEXTBOX_PADDING_SCREEN_Y, SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2, SCREEN_HEIGHT - TEXTBOX_PADDING_SCREEN_Y * 2)),
    m_equipment_panel(new Panel(TEXTBOX_PADDING_SCREEN, TEXTBOX_PADDING_SCREEN_Y, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3, TEXTBOX_PADDING_SHORT * 2 + TEXT_FONT_HEIGHT * 9)),
    m_selection_renderer(new Selection_Renderer(status_menu->get_selection_menu(), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 12, SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2)),
    m_weapons_renderer(new Selection_Renderer(status_menu->get_weapons_menu(), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3)),
    m_shields_renderer(new Selection_Renderer(status_menu->get_shields_menu(), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3)),
    m_helms_renderer(new Selection_Renderer(status_menu->get_helms_menu(), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3)),
    m_armor_renderer(new Selection_Renderer(status_menu->get_armor_menu(), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3)),
    m_accessories_renderer(new Selection_Renderer(status_menu->get_accessories_menu(), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3)){mem += 8;}
    Status_Menu_Renderer(const Status_Menu_Renderer & obj) = delete;
    Status_Menu_Renderer & operator =(const Status_Menu_Renderer & obj) = delete;
    virtual ~Status_Menu_Renderer();

    //Main Loop Functons
    virtual void render(const World* const world) const;

    const State_Machine::Status_Menu* const m_status_menu{};
    const Panel* const m_panel{};
    const Panel* const m_equipment_panel{};
    const Selection_Renderer* const m_selection_renderer{};
    const Selection_Renderer* const m_weapons_renderer{};
    const Selection_Renderer* const m_shields_renderer{};
    const Selection_Renderer* const m_helms_renderer{};
    const Selection_Renderer* const m_armor_renderer{};
    const Selection_Renderer* const m_accessories_renderer{};
};

#endif
