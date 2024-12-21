#ifndef UI_H
#define UI_H

#include "World.h"

class Progress_Bar
{
  public:
    explicit Progress_Bar(){}
    explicit Progress_Bar(const string & color, const long & length, const long & padding_x = 0, const long & padding_y = 0) : m_color(color), m_length(length), m_padding_x(padding_x), m_padding_y(padding_y){}
    Progress_Bar(const Progress_Bar & obj) = delete;
    Progress_Bar & operator =(const Progress_Bar & obj) = delete;

    void set_value(const long & value, const long & maximum, const long & minimum = 0){m_value = static_cast<double>(value - minimum) / (maximum - minimum) * MAX_PROGRESS_BAR_VALUE;}
    void render(const World* const world, const long & x, const long & y) const;
  private:
    string m_color{"Green"};
    long m_length{64};
    double m_value{50};
    long m_padding_x{0};
    long m_padding_y{0};
};

class Panel
{
  public:
    explicit Panel(const double & x, const double & y, const double & width, const double & height) : m_x(x), m_y(y), m_w(width), m_h(height){}
    Panel(const Panel & obj) = delete;
    Panel & operator =(const Panel & obj) = delete;
    ~Panel(){}

    void set_position(const double & x, const double & y, const double & width, const double & height){m_x = x; m_y = y; m_w = width; m_h = height;}
    void render(const World* const world) const{world->render_panel(m_x, m_y, m_w, m_h);}
  private:
    double m_x{0};
    double m_y{0};
    double m_w{9};
    double m_h{9};
};

class Player_Summary
{
  public:
    explicit Player_Summary(const long & x, const long & y, const Player_Info & player, const string & party_member_name, const bool & row, const string & party_member_species, const string & party_member_class, const long & level, const long & hp, const long & max_hp, const long & mp, const long & max_mp, const long & exp, const long & exp_to_next_level) : m_x(x), m_y(y), m_player_name(party_member_name), m_row(row), m_player_species(party_member_species), m_player_class(party_member_class), m_level(level), m_current_hp(hp), m_max_hp(max_hp), m_current_mp(mp), m_max_mp(max_mp), m_current_exp(exp), m_exp_to_next_level(exp_to_next_level), m_portrait_tween_current(row == true ? 0 : PLAYER_SUMMARY_ROW_OFFSET), m_portrait_tween_end(row == true ? 0 : PLAYER_SUMMARY_ROW_OFFSET), m_y_tween_current(y), m_y_tween_end(y), m_hp(new Progress_Bar{"Progress Bar Green", PLAYER_SUMMARY_PROGRESS_BAR_LENGTH}), m_mp(new Progress_Bar{"Progress Bar Blue", PLAYER_SUMMARY_PROGRESS_BAR_LENGTH}), m_exp(new Progress_Bar{"Progress Bar Pink", PLAYER_SUMMARY_PROGRESS_BAR_LENGTH}), m_soul_break(new Progress_Bar{"Progress Bar Red", PLAYER_SUMMARY_PROGRESS_BAR_LENGTH}), m_scroll(new Progress_Bar{"Progress Bar Orange", PLAYER_SUMMARY_PROGRESS_BAR_LENGTH}){mem += 5; Image image{LoadImageFromMemory(".png", player.m_small_portrait_data, player.m_small_portrait_size)}; m_small_portrait = LoadTextureFromImage(image); UnloadImage(image);}
    Player_Summary(const Player_Summary & obj) = delete;
    Player_Summary & operator =(const Player_Summary & obj) = delete;
    ~Player_Summary();
    
    void render(const World* const world) const;

    string get_name() const{return m_player_name;}
    void set_portrait_tween(const bool & start){m_portrait_tween_end = start == true ? 0 : PLAYER_SUMMARY_ROW_OFFSET;}
    void set_y_tween(const long & index1, const long & index2, const bool & index);
    void update_tweens();
    bool get_switch() const{return m_switch_rect;}
    void toggle_switch_rect(){m_switch_rect == true ? m_switch_rect = false : m_switch_rect = true;}
    void set_member_front_row(){m_row = true;}
    void set_member_back_row(){m_row = false;}
  private:
    long m_x{0};
    long m_y{0};
    string m_player_name{"NULL"};
    bool m_row{true};
    string m_player_species{"NULL"};
    string m_player_class{"NULL"};
    long m_level{1};
    long m_current_hp{0};
    long m_max_hp{0};
    long m_current_mp{0};
    long m_max_mp{0};
    long m_current_exp{0};
    long m_exp_to_next_level{0};
    double m_portrait_tween_current{0};
    long m_portrait_tween_end{0};
    double m_y_tween_current{0};
    long m_y_tween_end{0};
    bool m_switch_rect{false};
    long m_difference_of_swap_indexes{0};
    Progress_Bar* m_hp{nullptr};
    Progress_Bar* m_mp{nullptr};
    Progress_Bar* m_exp{nullptr};
    Progress_Bar* m_soul_break{nullptr};
    Progress_Bar* m_scroll{nullptr};
    Texture2D m_small_portrait{};
};

class Selection
{
  public:
    explicit Selection(const long & num_choices, const long & columns, const long & rows, const long & display_rows, const bool & show_cursor = true, const bool show_menu = true) : m_num_choices(num_choices), m_columns(columns), m_max_rows(rows), m_display_rows(display_rows), m_show_cursor(show_cursor), m_show_menu(show_menu){}
    Selection(const Selection & obj) = delete;
    Selection & operator =(const Selection & obj) = delete;
    ~Selection(){}

    void update_input(World* world, const long & x, const long & y, const long & spacing_x, const long & spacing_y = TEXT_FONT_HEIGHT);

    long get_highlighted_item() const{return m_highlighted_item;}
    void show_cursor(){m_show_cursor = true;}
    void hide_cursor(){m_show_cursor = false;}
    bool cursor_shown() const{return m_show_cursor;}
    void show_menu(){m_show_menu = true;}
    void hide_menu(){m_show_cursor = false; m_show_menu = false;}
    bool menu_shown() const{return m_show_menu;}

    long get_display_start() const{return m_display_start;}
    long get_display_rows() const{return m_display_rows;}
    long get_columns() const{return m_columns;}
    long get_number_of_choices() const{return m_num_choices;}
    void change_number_of_choices(const long & new_number){m_num_choices = new_number;}
    bool animation_is_visible() const{return m_continue_arrow_animation.is_visible();}

  private:
    long m_num_choices{1};
    long m_columns{1};
    long m_max_rows{1};
    long m_display_rows{1};
    long m_focus_x{0};
    long m_focus_y{0};
    bool m_show_cursor{true};
    bool m_show_menu{true};
    long m_display_start{0};
    long m_highlighted_item{0};
    Blinking_Animation m_continue_arrow_animation{true, false, 8};
};

class Selection_Renderer
{
  public:
    explicit Selection_Renderer(const Selection* const selection, const long & x, const long & y, const long & spacing_x, const long & spacing_y = TEXT_FONT_HEIGHT) : m_selection(selection), m_x(x), m_y(y), m_spacing_x(spacing_x / selection->get_columns()), m_spacing_y(spacing_y){}
    Selection_Renderer(const Selection_Renderer & obj) = delete;
    Selection_Renderer & operator =(const Selection_Renderer & obj) = delete;
    ~Selection_Renderer(){}
    void render(const vector<string> & choices, const World* const world) const;
    void render_items(const vector<string> & choices, const World* const world, const vector<string> & item_descriptions, const vector<long> & item_quantities) const;
    void render_key_items(const vector<string> & choices, const World* const world, const vector<string> & item_descriptions) const;
    void render_equipment(const vector<string> & choices, const World* const world, const string & character_name, const string & equipment_type, const long & slot, const vector<string> & item_descriptions, const vector<long> & item_quantities, const vector<string> & item_equipped_bys, const vector<long> & item_icons, const vector<bool> & item_usable_bys, const vector<long> & item_slots = vector<long>{}) const;
    void render_status_menu(const vector<string> & choices, const World* const world,
                            const long & strength, const long & unmodified_strength, const long & strength_difference,
                            const long & attack, const long & unmodified_attack, const long & attack_difference,
                            const long & speed, const long & unmodified_speed, const long & speed_difference,
                            const long & defense, const long & unmodified_defense, const long & defense_difference,
                            const long & intellect, const long & unmodified_intellect, const long & intellect_difference,
                            const long & resistance, const long & unmodified_resistance, const long & resistance_difference,
                            const long & stamina, const long & unmodified_stamina, const long & stamina_difference,
                            const long & accuracy, const long & unmodified_accuracy, const long & accuracy_difference,
                            const long & spirit, const long & unmodified_spirit, const long & spirit_difference,
                            const long & critical, const long & unmodified_critical, const long & critical_difference,
                            const long & evasion, const long & unmodified_evasion, const long & evasion_difference,
                            const long & magic_evasion, const long & unmodified_magic_evasion, const long & magic_evasion_difference,
                            const string & weapon_name, const long & weapon_icon, const string & shield_name, const long & shield_icon, const string & helm_name, const long & helm_icon, const string & armor_name, const long & armor_icon, const string & accessory_one_name, const long & accessory_one_icon, const string & accessory_two_name, const long & accessory_two_icon) const;
  private:
    const Selection* const m_selection{};
    long m_x{0};
    long m_y{0};
    long m_spacing_x{0};
    long m_spacing_y{0};
};

class Textbox
{
  public:
    explicit Textbox(){}
    void add_text(const string & text){m_text = text;}
    void add_title(const string & title){m_title_text = title;}
    void add_portrait(const Image_Params & image){Image the_image{LoadImageFromMemory(".png", image.m_data, image.m_size)}; m_portrait_img = LoadTextureFromImage(the_image); UnloadImage(the_image);}
    void add_selection_menu(Selection* s, Selection_Renderer* sr){m_selection = s; m_selection_renderer = sr;}
    void create_fitted(const long & size_x, const long & size_y){create_fixed(size_x, size_y, get_text_font_word_width(m_text) + TEXTBOX_PADDING_LONG * 2, TEXT_FONT_HEIGHT + TEXTBOX_PADDING_SHORT * 2);}
    void create_fitted_choices(const long & size_x, const long & size_y, const vector<string> & choices);
    void create_fixed(const long & size_x, const long & size_y, const long & size_width, const long & size_height);
    Textbox(const Textbox & obj) = delete;
    Textbox & operator =(const Textbox & obj) = delete;
    ~Textbox();

    void update_input(World* world);
    void render(const World* const world) const;
    
    long get_selected_item() const{return m_selection->get_highlighted_item();}
    bool dead() const{return m_dead;}

  private:
    void on_click();
    void break_text(string text);
  
    string m_text{""};
    string m_title_text{""};
    long m_size_x{-1};
    long m_size_y{-1};
    long m_size_w{-1};
    long m_size_h{-1};
    long m_text_area_x{-1};
    long m_text_area_y{-1};
    long m_text_area_w{-1};
    long m_text_area_h{-1};
    long m_title_x{-1};
    long m_title_y{-1};
    long m_portrait_x{-1};
    long m_portrait_y{-1};
    
    //The center of the panel
    double m_center_x{0};
    double m_center_y{0};

    //The starting location, width, and height of the panel as well as its position, width, and height while expanding and shrinking
    double m_start_x{0};
    double m_start_y{0};
    double m_start_w{0};
    double m_start_h{0};

    //The speed of the expansion and shrinking
    double m_x_speed{0};
    double m_y_speed{0};

    bool m_start{false};
    bool m_shrink{false};
    bool m_dead{false};
    bool m_expanded{false};
    
    vector<string> m_text_chunks{};
    Panel* m_panel{nullptr};
    Selection* m_selection{nullptr};
    const Selection_Renderer* m_selection_renderer{nullptr};
    vector<string> m_choices{" "};
    Texture2D m_portrait_img{};
    Blinking_Animation m_continue_arrow_animation{true, false, 8};
};

#endif
