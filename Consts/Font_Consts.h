#ifndef FONT_CONSTS_H
#define FONT_CONSTS_H

const Font_Params TEXT_FONT{};
const Font_Params HEADING_FONT{"Heading", binary_Image_heading_font_png_start, reinterpret_cast<long>(&binary_Image_heading_font_png_size), FONT_HEADING_CELL_WIDTH, FONT_HEADING_CHAR_WIDTHS};
const Font_Params CHARACTER_TITLE_FONT{"Character Title", binary_Image_text_font_yellow_png_start, reinterpret_cast<long>(&binary_Image_text_font_yellow_png_size), FONT_TEXT_CELL_WIDTH, FONT_TEXT_CHAR_WIDTHS};

#endif