#ifndef FONT_H
#define FONT_H

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
    ~Fnt(){UnloadTexture(m_font_img);}

    string get_name() const{return m_name;}
    long get_height() const{return m_font_img.height;}
    long get_cell_width() const{return m_cell_width;}
    long get_char_width(const long & index) const{return m_char_widths[index];}
    long get_word_width(string word) const;
    void render_text(string text, const long & x_pos, const long & y_pos, const long & alpha = 255) const;
    void render_text_center(string text, const long & y_pos, const long & alpha = 255) const{render_text(text, SCREEN_WIDTH / 2 - get_word_width(text) / 2, y_pos, alpha);}
    void render_letter(const long & x, const long & y, const char & id, const long & alpha = 255) const{DrawTexturePro(m_font_img, Rectangle{static_cast<float>(m_cell_width * id), 0, static_cast<float>(m_cell_width), static_cast<float>(m_font_img.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y), static_cast<float>(m_cell_width), static_cast<float>(m_font_img.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alpha)});}
  private:
    string m_name{"NULL"};
    long m_cell_width{0};
    array<long, NUM_FONT_CELLS> m_char_widths{};
    Texture2D m_font_img{};
};

#endif
