#ifndef UI_H
#define UI_H

class World;
class Equipment;

struct Font_Params
{
  explicit Font_Params(const string & name = "Text", const Image_Params & image = TEXT_FONT_IMAGE, const long & cell_width = FONT_TEXT_CELL_WIDTH, const array<long, NUM_FONT_CELLS> & char_widths = FONT_TEXT_CHAR_WIDTHS) : m_name(name), m_data(image.m_data), m_size(image.m_size), m_cell_width(cell_width), m_char_widths(char_widths){}
  explicit Font_Params(const Font_Params & obj) = default;
  Font_Params & operator =(const Font_Params & obj) = default;
  string m_name{"NULL"};
  const unsigned char* m_data{nullptr};
  long m_size{1};
  long m_cell_width{0};
  const array<long, NUM_FONT_CELLS> m_char_widths{};
};

const Font_Params TEXT_FONT{};
const Font_Params HEADING_FONT{"Heading", HEADING_FONT_IMAGE, FONT_HEADING_CELL_WIDTH, FONT_HEADING_CHAR_WIDTHS};
const Font_Params CHARACTER_TITLE_FONT{"Character Title", TEXT_FONT_YELLOW_IMAGE, FONT_TEXT_CELL_WIDTH, FONT_TEXT_CHAR_WIDTHS};
const Font_Params RED_FONT{"Red", TEXT_FONT_RED_IMAGE, FONT_TEXT_CELL_WIDTH, FONT_TEXT_CHAR_WIDTHS};
const Font_Params GREEN_FONT{"Green", TEXT_FONT_GREEN_IMAGE, FONT_TEXT_CELL_WIDTH, FONT_TEXT_CHAR_WIDTHS};
const Font_Params TEMPEST_FONT{"Character Title", TEXT_FONT_TEMPEST_IMAGE, FONT_TEXT_CELL_WIDTH, FONT_TEXT_CHAR_WIDTHS};
const Font_Params NIGHTWISH_FONT{"Character Title", TEXT_FONT_NIGHTWISH_IMAGE, FONT_TEXT_CELL_WIDTH, FONT_TEXT_CHAR_WIDTHS};
const Font_Params GALLUS_FONT{"Character Title", TEXT_FONT_GALLUS_IMAGE, FONT_TEXT_CELL_WIDTH, FONT_TEXT_CHAR_WIDTHS};

class Fnt
{
  public:
    explicit Fnt(const Font_Params & font_to_load = TEXT_FONT);
    Fnt(const Fnt & obj) = delete;
    Fnt & operator =(const Fnt & obj) = delete;
    ~Fnt();

    string get_name() const;
    long get_height() const;
    long get_cell_width() const;
    long get_char_width(const long & index) const;
    long get_word_width(string word) const;
    void render_text(string text, const long & x_pos, const long & y_pos, const long & alpha = 255) const;
    void render_text_center(string text, const long & y_pos, const long & alpha = 255) const;
    void render_letter(const long & x, const long & y, const char & id, const long & alpha = 255) const;
  private:
    string m_name{"NULL"};
    long m_cell_width{0};
    array<long, NUM_FONT_CELLS> m_char_widths{};
    Texture2D m_font_img{};
};

class Progress_Bar
{
  public:
    explicit Progress_Bar(){}
    explicit Progress_Bar(const string & background_image_name, const string & bar_image_name, const long & length, const long & padding_x = 0, const long & padding_y = 0) : m_background_image_name(background_image_name), m_bar_image_name(bar_image_name), m_length(length), m_padding_x(padding_x), m_padding_y(padding_y){}
    Progress_Bar(const Progress_Bar & obj) = delete;
    Progress_Bar & operator =(const Progress_Bar & obj) = delete;

    void set_value(const long & value, const long & maximum, const long & minimum = 0);
    void render(World* world, const long & x, const long & y) const;
  private:
    string m_background_image_name{"NULL"};
    string m_bar_image_name{"NULL"};
    long m_length{64};
    double m_value{50};
    long m_padding_x{0};
    long m_padding_y{0};
};

class Panel
{
  public:
    explicit Panel(){}
    Panel(const Panel & obj) = delete;
    Panel & operator =(const Panel & obj) = delete;
    ~Panel(){}

    void set_position(const double & x, const double & y, const double & width, const double & height);
    void render(World* world) const;
  private:
    double m_x{0};
    double m_y{0};
    double m_w{9};
    double m_h{9};
};

class Player_Summary
{
  public:
    explicit Player_Summary(const long & x, const long & y, const string & party_member_name, const bool & row);
    Player_Summary(const Player_Summary & obj) = delete;
    Player_Summary & operator =(const Player_Summary & obj) = delete;
    ~Player_Summary();
    
    void render(World* world) const;
    
    string get_name() const;
    void set_portrait_tween(const bool & start);
    void set_y_tween(const long & index1, const long & index2, const bool & index);
    void update_tweens(World* world);
    bool get_switch() const;
    void toggle_switch_rect();
    
  private:
    long m_x{0};
    long m_y{0};
    string m_player_name{"NULL"};
    Progress_Bar* m_hp{};
    Progress_Bar* m_mp{};
    Progress_Bar* m_exp{};
    Progress_Bar* m_soul_break{};
    Progress_Bar* m_scroll{};
    double m_portrait_tween_current{0};
    long m_portrait_tween_end{0};
    double m_y_tween_current{0};
    long m_y_tween_end{0};
    bool m_switch_rect{false};
    long m_difference_of_swap_indexes{0};
};

template <typename T>
class Selection
{
  public:
    explicit Selection(const vector<T*> & data, const long & columns, const long & rows, const long & display_rows, const long & spacing_y, const bool & show_cursor = true, const bool show_menu = true, const string & render_mode = "Normal") : m_choices(data), m_columns(columns), m_max_rows(rows), m_display_rows(display_rows), m_spacing_y(spacing_y), m_show_cursor(show_cursor), m_show_menu(show_menu), m_render_mode(render_mode){}
    Selection(const Selection & obj) = delete;
    Selection & operator =(const Selection & obj) = delete;
    ~Selection(){}

    void rebuild_choices(const vector<T*> & data);
    void update_input(World* world);
    void render(World* world, const string & party_member_name = "NULL", const vector<long> & equipment_stat_differences = vector<long>{}) const;
    
    void set_position(const long & x, const long & y);
    void set_spacing_x(const long & text_area_width);
    long get_height() const;
    long get_highlighted_item() const;
    const T* get_highlighted_item_obj() const;
    void show_cursor();
    void hide_cursor();
    bool cursor_shown() const;
    void show_menu();
    void hide_menu();
    bool menu_shown() const;
    string c_get_options(World* world) const;

  private:
    void render_item(World* world, const string & font, const long & x, const long & y, const string & item_name) const;

    long m_x{0};
    long m_y{0};
    List<T> m_choices{};
    long m_columns{1};
    long m_max_rows{1};
    long m_display_rows{1};
    long m_focus_x{0};
    long m_focus_y{0};
    long m_spacing_x{0};
    long m_spacing_y{0};
    bool m_show_cursor{true};
    bool m_show_menu{true};
    long m_display_start{0};
    long m_highlighted_item{0};
    string m_render_mode{"Normal"};
    Blinking_Animation m_continue_arrow_animation{false, false, CONTINUE_ARROW_INTERVAL};
};

template <>
void Selection<string>::update_input(World* world);

template <>
void Selection<string>::render(World* world, const string & party_member_name, const vector<long> & equipment_stat_differences) const;

template <>
void Selection<Equipment>::render(World* world, const string & party_member_name, const vector<long> & equipment_stat_differences) const;

template <>
void Selection<string>::render_item(World* world, const string & font, const long & x, const long & y, const string & item_index) const;

class Textbox
{
  public:
    explicit Textbox(){}
    void add_text(const string & text);
    void add_title(const string & title);
    void add_portrait(const Image_Params & image);
    void add_selection_menu(Selection<string>* s);
    void create_fitted(const long & size_x, const long & size_y, World* world);
    void create_fitted_choices(const long & size_x, const long & size_y, const vector<string> & choices, World* world);
    void create_fixed(const long & size_x, const long & size_y, const long & size_width, const long & size_height, World* world);
    Textbox(const Textbox & obj) = delete;
    Textbox & operator =(const Textbox & obj) = delete;
    ~Textbox();

    void update_input(World* world);
    void render(World* world) const;
    
    long get_selected_item() const;
    bool dead() const;

  private:
    void on_click();
    void break_text(string text, World* world, const string & font_name);
    void render_textbox(string text, World* world, const string & font_name) const;
  
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
    Selection<string>* m_selection{nullptr};
    Texture2D m_portrait_img{};
    Blinking_Animation m_continue_arrow_animation{false, false, 0};
};

#endif
