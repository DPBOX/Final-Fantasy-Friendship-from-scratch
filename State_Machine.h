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
    bool update_input(World* world, Input_Wrapper* input);
    void change_state(const World* const world);    //State changer
    void render(const World* const world) const;
    
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
    virtual tuple<bool, state_list, string> update_input(World* world, Input_Wrapper* input) = 0;
    virtual ~Machine_State(){};
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
    virtual tuple<bool, state_list, string> update_input(World* world, Input_Wrapper* input);

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
                                 m_gold(new Panel(PANEL_MENU_UL_X, PANEL_GOLD_Y, PANEL_FRONT_MENU_WIDTH_LEFT, PANEL_HEIGHT_TWO_LINES)),
                                 m_map(new Panel(PANEL_MENU_UL_X, PANEL_MAP_NAME_Y, PANEL_FRONT_MENU_WIDTH_LEFT, PANEL_HEIGHT_TWO_LINES)),
                                 m_party_panel(new Panel(PANEL_FRONT_MENU_X_RIGHT, PANEL_MENU_UL_Y, PANEL_FRONT_MENU_WIDTH_RIGHT, PANEL_HEIGHT_SCREEN)),
                                 m_menu(new Panel(PANEL_MENU_UL_X, PANEL_MENU_UL_Y, PANEL_FRONT_MENU_WIDTH_LEFT, TEXT_FONT_HEIGHT * NUM_FRONT_MENU_CHOICES + TEXTBOX_PANEL_OFFSET_Y * 2)),
                                 m_selection_renderer(new Selection_Renderer(front_menu->get_selection(), TEXTBOX_MENU_UL_X, TEXTBOX_MENU_UL_Y, PANEL_FRONT_MENU_WIDTH_LEFT - TEXTBOX_PANEL_OFFSET_X * 2)),
                                 m_party_menu_renderer(new Selection_Renderer(front_menu->get_party_menu(), TEXTBOX_MENU_UL_X + PANEL_FRONT_MENU_WIDTH_LEFT, TEXTBOX_MENU_UL_Y, PANEL_FRONT_MENU_WIDTH_RIGHT - TEXTBOX_PANEL_OFFSET_X * 2, TEXT_FONT_HEIGHT * PLAYER_SUMMARY_HEIGHT_IN_TILES + PLAYER_SUMMARY_SECTION_PADDING_Y)), m_front_menu(front_menu){mem += 6;}
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
    virtual tuple<bool, state_list, string> update_input(World* world, Input_Wrapper* input);

    Selection* m_category{nullptr};
    Selection* m_items_menu{nullptr};
    Selection* m_key_items_menu{nullptr};
};

class State_Machine::Item_Menu_Renderer : private State_Machine::Machine_State_Renderer
{
  private:
    friend class State_Machine;
    explicit Item_Menu_Renderer(const State_Machine::Item_Menu* const item_menu) :
                                m_switch(new Panel(PANEL_ITEM_MENU_X_RIGHT, PANEL_MENU_UL_Y, PANEL_ITEM_MENU_WIDTH_RIGHT, PANEL_HEIGHT_ONE_LINE)),
                                m_item_text(new Panel(PANEL_MENU_UL_X, PANEL_MENU_UL_Y, PANEL_ITEM_MENU_WIDTH_LEFT, PANEL_HEIGHT_ONE_LINE)),
                                m_description(new Panel(PANEL_MENU_UL_X, PANEL_MENU_UL_Y + PANEL_HEIGHT_ONE_LINE, PANEL_WIDTH_SCREEN, PANEL_HEIGHT_ONE_LINE)),
                                m_item_list(new Panel(PANEL_MENU_UL_X, PANEL_MENU_UL_Y + PANEL_HEIGHT_ONE_LINE * 2, PANEL_WIDTH_SCREEN, SCREEN_HEIGHT - PANEL_SCREEN_OFFSET_Y * 2 - PANEL_HEIGHT_ONE_LINE * 2)),
                                m_category_renderer(new Selection_Renderer(item_menu->get_category_menu(), TEXTBOX_MENU_UL_X + PANEL_ITEM_MENU_WIDTH_LEFT, TEXTBOX_MENU_UL_Y, PANEL_ITEM_MENU_WIDTH_RIGHT - TEXTBOX_PANEL_OFFSET_X * 2)),
                                m_items_renderer(new Selection_Renderer(item_menu->get_item_menu(), TEXTBOX_MENU_UL_X, PANEL_MENU_UL_Y + PANEL_HEIGHT_ONE_LINE * 2 + TEXTBOX_PANEL_OFFSET_Y, PANEL_WIDTH_SCREEN - TEXTBOX_PANEL_OFFSET_X * 2)),
                                m_key_items_renderer(new Selection_Renderer(item_menu->get_key_item_menu(), TEXTBOX_MENU_UL_X, PANEL_MENU_UL_Y + PANEL_HEIGHT_ONE_LINE * 2 + TEXTBOX_PANEL_OFFSET_Y, PANEL_WIDTH_SCREEN - TEXTBOX_PANEL_OFFSET_X * 2)){mem += 7;}
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
    const Selection* get_armor_menu() const;
    const Selection* get_accessories_menu() const;
    string get_character() const{return m_character;}
    long get_slot() const{return m_slot;}
    void render_hp_bar(const World* const world, const long & x, const long & y) const;
    void render_mp_bar(const World* const world, const long & x, const long & y) const;
    void render_exp_bar(const World* const world, const long & x, const long & y) const;
  private:
    friend class State_Machine;
    explicit Status_Menu(const World* const world, const string & selected_party_member) : m_character(selected_party_member), m_selection_menu(new Selection(static_cast<long>(STAT_STRINGS.size()), NUM_STATUS_MENU_COLUMNS, STATUS_MENU_ROWS, STATUS_MENU_ROWS, true, true)),
                    m_weapons_menu(new Selection(world->get_number_of_equipped_and_inventory_weapons(), NUM_EQUIPMENT_MENU_COLUMNS, MAX_NUM_EQUIPMENT_MENU_ROWS, NUM_EQUIPMENT_MENU_ROWS, false, false)),
                    m_armor_menu(new Selection(world->get_number_of_equipped_and_inventory_armor(), NUM_EQUIPMENT_MENU_COLUMNS, MAX_NUM_EQUIPMENT_MENU_ROWS, NUM_EQUIPMENT_MENU_ROWS, false, false)),
                    m_accessories_menu(new Selection(world->get_number_of_equipped_and_inventory_accessories(), NUM_EQUIPMENT_MENU_COLUMNS, MAX_NUM_EQUIPMENT_MENU_ROWS, NUM_EQUIPMENT_MENU_ROWS, false, false)),
                    m_hp(new Progress_Bar{"Progress Bar Green", PANEL_STATUS_MENU_WIDTH_LEFT - TEXTBOX_PANEL_OFFSET_X * 2 - STATUS_PROGRESS_BAR_PADDING}),
                    m_mp(new Progress_Bar{"Progress Bar Blue", PANEL_STATUS_MENU_WIDTH_LEFT - TEXTBOX_PANEL_OFFSET_X * 2 - STATUS_PROGRESS_BAR_PADDING}),
                    m_exp(new Progress_Bar{"Progress Bar Pink", PANEL_STATUS_MENU_WIDTH_LEFT - TEXTBOX_PANEL_OFFSET_X * 2 - STATUS_PROGRESS_BAR_PADDING}){mem += 7;}
    Status_Menu(const Status_Menu & obj) = delete;
    Status_Menu & operator =(const Status_Menu & obj) = delete;
    virtual ~Status_Menu();
    
    //Main Loop Functons
    virtual void update(){}
    virtual tuple<bool, state_list, string> update_input(World* world, Input_Wrapper* input);

    string m_character{"NULL"};
    Selection* m_selection_menu{nullptr};
    Selection* m_weapons_menu{nullptr};
    Selection* m_armor_menu{nullptr};
    Selection* m_accessories_menu{nullptr};
    Progress_Bar* m_hp{};
    Progress_Bar* m_mp{};
    Progress_Bar* m_exp{};
    long m_slot{0};
};

class State_Machine::Status_Menu_Renderer : private State_Machine::Machine_State_Renderer
{
  private:
    friend class State_Machine;
    explicit Status_Menu_Renderer(const State_Machine::Status_Menu* const status_menu) : m_status_menu(status_menu),
    m_panel(new Panel(PANEL_MENU_UL_X, PANEL_MENU_UL_Y, PANEL_WIDTH_SCREEN, PANEL_HEIGHT_SCREEN)),
    m_panel_stats(new Panel(PANEL_STATUS_MENU_X_RIGHT, PANEL_MENU_UL_Y, PANEL_STATUS_MENU_WIDTH_RIGHT, PANEL_HEIGHT_THIRTEEN_LINES)),
    m_panel_description(new Panel(PANEL_MENU_UL_X, SCREEN_HEIGHT - PANEL_HEIGHT_TWO_LINES - PANEL_SCREEN_OFFSET_Y, PANEL_WIDTH_SCREEN, PANEL_HEIGHT_TWO_LINES)),
    m_equipment_panel(new Panel(PANEL_MENU_UL_X, PANEL_MENU_UL_Y, PANEL_STATUS_MENU_WIDTH_LEFT, PANEL_HEIGHT_THIRTEEN_LINES)),
    m_selection_renderer(new Selection_Renderer(status_menu->get_selection_menu(), PANEL_STATUS_MENU_X_RIGHT + TEXTBOX_PANEL_OFFSET_X, TEXTBOX_MENU_UL_Y + TEXT_FONT_HEIGHT * 9, PANEL_STATUS_MENU_WIDTH_RIGHT - TEXTBOX_PANEL_OFFSET_X * 2)),
    m_weapons_renderer(new Selection_Renderer(status_menu->get_weapons_menu(), TEXTBOX_MENU_UL_X, TEXTBOX_MENU_UL_Y, PANEL_STATUS_MENU_WIDTH_LEFT - TEXTBOX_PANEL_OFFSET_X * 2)),
    m_armor_renderer(new Selection_Renderer(status_menu->get_armor_menu(), TEXTBOX_MENU_UL_X, TEXTBOX_MENU_UL_Y, PANEL_STATUS_MENU_WIDTH_LEFT - TEXTBOX_PANEL_OFFSET_X * 2)),
    m_accessories_renderer(new Selection_Renderer(status_menu->get_accessories_menu(), TEXTBOX_MENU_UL_X, TEXTBOX_MENU_UL_Y, PANEL_STATUS_MENU_WIDTH_LEFT - TEXTBOX_PANEL_OFFSET_X * 2)){mem += 8;}
    Status_Menu_Renderer(const Status_Menu_Renderer & obj) = delete;
    Status_Menu_Renderer & operator =(const Status_Menu_Renderer & obj) = delete;
    virtual ~Status_Menu_Renderer();

    //Main Loop Functons
    virtual void render(const World* const world) const;

    const State_Machine::Status_Menu* const m_status_menu{};
    const Panel* const m_panel{};
    const Panel* const m_panel_stats{};
    const Panel* const m_panel_description{};
    const Panel* const m_equipment_panel{};
    const Selection_Renderer* const m_selection_renderer{};
    const Selection_Renderer* const m_weapons_renderer{};
    const Selection_Renderer* const m_armor_renderer{};
    const Selection_Renderer* const m_accessories_renderer{};
};

#endif
