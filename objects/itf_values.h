#ifndef ITF
#define ITF

#define ITF_BHB "▄"
#define ITF_C_END "\e[0m"

enum itf_colors {
    ITF_C_BLACK = (int)'0',
    ITF_C_RED = (int)'1',
    ITF_C_GREEN = (int)'2',
    ITF_C_YELLOW = (int)'3',
    ITF_C_BLUE = (int)'4',
    ITF_C_PURPLE = (int)'5',
    ITF_C_CYAN = (int)'6',
    ITF_C_WHITE = (int)'7'
};

#define ITF_FG_LOW "3"
#define ITF_FG_HIGH "9"
#define ITF_BG_LOW "4"
#define ITF_BG_HIGH "10"

#define ITF_LOW_INTEN false
#define ITF_HIGH_INTEN true

struct itf_pixels {
    itf_colors color;
    bool intensity;
    bool used;
};

struct itf_text_pallete {
    itf_colors fg_color;
    itf_colors bg_color;
    bool fg_inten;
    bool bg_inten;
};

//used to create bash color string
std::string itf_give_color(const std::string& to_color, const itf_text_pallete& of_color)
{
    std::string to_return = "\e[0;";


    if(of_color.bg_inten) {
        to_return += ITF_BG_HIGH;
    } else {
        to_return += ITF_BG_LOW;
    }

    to_return += (char)of_color.bg_color;
    to_return += ";";


    if(of_color.fg_inten) {
        to_return += ITF_FG_HIGH;
    } else {
        to_return += ITF_FG_LOW;
    }

    to_return += (char)of_color.fg_color;
    to_return += "m";

    to_return += to_color;
    to_return += ITF_C_END;

    return to_return;
}

class itf_tile {
public:
    itf_tile() {};

    ~itf_tile() {};

    void test();
};

#include "itf_tile.h"

#endif