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

enum itf_lines_drct {
    ITF_D_UP,
    ITF_D_DOWN,
    ITF_D_LEFT,
    ITF_D_RIGHT
};

#define ITF_FG_LOW "3"
#define ITF_FG_HIGH "9"
#define ITF_BG_LOW "4"
#define ITF_BG_HIGH "10"

#define ITF_LOW_INTEN false
#define ITF_HIGH_INTEN true

#define ITF_MOVE_PEN true

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

struct itf_pencil {
    int on_hght;
    int on_wdth;
    int on_layer;
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
    itf_tile(const int& h, const int& w) {
        if(h % 2 != 0 && w % 2 != 0) {
            this->height = -1;
            this->width = -1;
        } else {
            this->height = h;
            this->width = w;

            const int buf_cap = h / 2;
            for(int add_buffer = 0; add_buffer < buf_cap; add_buffer++) {
                this->tile_buffer.push_back("");
            }
        }

        this->draw_pencil.on_hght = this->draw_pencil.on_wdth = this->draw_pencil.on_layer = 0;
    };

    ~itf_tile() {
        if(this->height != -1 && this->width != -1) {
            for(int cln_rws = 0; cln_rws < this->height; cln_rws++) delete[] this->tile_build[cln_rws];
            delete[] this->tile_build;
        }

        //if layers contain anything really
        if(this->draw_layers.size() > 0) {
            for(int dst_layer = 0; dst_layer < this->draw_layers.size(); dst_layer++) {
                itf_pixels** rnd_layer; //rnd stands for read and destroy
                rnd_layer = this->draw_layers[dst_layer];

                for(int cln_rws = 0; cln_rws < this->height; cln_rws++) delete[] rnd_layer[cln_rws];
                delete[] rnd_layer;
            }
        }
    };

    void init(); // reads what output did validation make and creates needed data
    void create_new_layer(bool move_pen);

    //as name suggest, these lil fellas are responsible for creating a final product
    void create_build();
    void create_buffer();

    void paint_fill(const itf_colors color, const bool intensity);
    void paint_pixel(const itf_colors color, const bool intensity);
    void paint_line(const itf_colors color, const bool intensity, const itf_lines_drct direction, const int size); //todo
    void paint_rect(const itf_colors color, const bool intensity, const bool is_hollow, const int height, const int width); //todo

    std::vector<std::string> tile_buffer;
    itf_pencil draw_pencil;
private:
    itf_pixels** tile_build;
    std::vector<itf_pixels**> draw_layers;

    int height, width;
};

#include "itf_tile.h"

#endif