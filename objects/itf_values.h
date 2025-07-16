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

enum itf_preload_idx {
    ITF_IDX_NON_PLAYABLE = 0,
    ITF_IDX_EMPTY = 1,
    ITF_IDX_SELECTABLE_EMPTY = 2,
    ITF_IDX_SELECTED_EMPTY = 3,
    ITF_IDX_LIGHT_PAWN = 4,
    ITF_IDX_LIGHT_JOKEY = 5,
    ITF_IDX_DARK_PAWN = 6,
    ITF_IDX_DARK_JOKEY = 7,
    ITF_IDX_LIGHT_PAWN_SELECTABLE = 8,
    ITF_IDX_LIGHT_PAWN_SELECTED = 9,
    ITF_IDX_LIGHT_PAWN_STRIKABLE = 10,
    ITF_IDX_LIGHT_JOKEY_SELECTABLE = 11,
    ITF_IDX_LIGHT_JOKEY_SELECTED = 12,
    ITF_IDX_LIGHT_JOKEY_STRIKABLE = 13,
    ITF_IDX_DARK_PAWN_SELECTABLE = 14,
    ITF_IDX_DARK_PAWN_SELECTED = 15,
    ITF_IDX_DARK_PAWN_STRIKABLE = 16,
    ITF_IDX_DARK_JOKEY_SELECTABLE = 17,
    ITF_IDX_DARK_JOKEY_SELECTED = 18,
    ITF_IDX_DARK_JOKEY_STRIKABLE = 19
};

#define ITF_COUNT_IDX 20

#define ITF_FG_LOW "3"
#define ITF_FG_HIGH "9"
#define ITF_BG_LOW "4"
#define ITF_BG_HIGH "10"

#define ITF_LOW_INTEN false
#define ITF_HIGH_INTEN true

#define ITF_MOVE_PEN true

#define ITF_RCT_FULL false
#define ITF_RCT_HLOW true

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
    void paint_line(const itf_colors color, const bool intensity, const itf_lines_drct direction, const int size);
    void paint_rect(const itf_colors color, const bool intensity, const bool is_hollow, const int hght, const int wdth);

    std::vector<std::string> tile_buffer;
    itf_pencil draw_pencil;
private:
    itf_pixels** tile_build;
    std::vector<itf_pixels**> draw_layers;

    int height, width;
};

#include "itf_tile.h"

void itf_show_pallette()
{
    const int hght = 2;
    const int wdth = 8;

    itf_tile* showcase;
    showcase = new itf_tile(hght, wdth);

    showcase->init();

    const int colors_count = 8;
    const itf_colors all_colors[colors_count] = {
        ITF_C_BLACK,
        ITF_C_RED,
        ITF_C_GREEN,
        ITF_C_YELLOW,
        ITF_C_BLUE,
        ITF_C_PURPLE,
        ITF_C_CYAN,
        ITF_C_WHITE
    };

    for(int elem_color = 0; elem_color < colors_count; elem_color++) {
        showcase->draw_pencil.on_wdth = elem_color;

        showcase->draw_pencil.on_hght = 0;
        showcase->paint_pixel(all_colors[elem_color], ITF_LOW_INTEN);

        showcase->draw_pencil.on_hght = 1;
        showcase->paint_pixel(all_colors[elem_color], ITF_HIGH_INTEN);
    }

    showcase->create_build();
    showcase->create_buffer();

    std::cout << showcase->tile_buffer[0] << std::endl;

    delete showcase;
}

void itf_preload_content(std::vector<itf_tile*>& container)
{
    //creating new tiles
    const int sqr = 8;
    for(int add = 0; add < ITF_COUNT_IDX; add++) {
        itf_tile* to_add;
        to_add = new itf_tile(sqr, sqr);

        to_add->init();
        container.push_back(to_add);
    }

    //giving background
    container[ITF_IDX_NON_PLAYABLE]->paint_fill(ITF_C_WHITE, ITF_LOW_INTEN);
    for(int bg = ITF_IDX_EMPTY; bg < ITF_COUNT_IDX; bg++) {
        container[bg]->paint_fill(ITF_C_GREEN, ITF_HIGH_INTEN);
    }

    //giving pawned new layer
    for(int pawns = ITF_IDX_LIGHT_PAWN; pawns < ITF_COUNT_IDX; pawns++) {
        container[pawns]->create_new_layer(ITF_MOVE_PEN);
        
        //I wanna make a on 2,2 a 4 by 4 squeres
        container[pawns]->draw_pencil.on_hght = 2;
        container[pawns]->draw_pencil.on_wdth = 2;
    }

    //creating light ones
    for(int light = ITF_IDX_LIGHT_PAWN; light < ITF_COUNT_IDX; light++) {
        if((light == ITF_IDX_LIGHT_PAWN || light == ITF_IDX_LIGHT_JOKEY) || (light >= ITF_IDX_LIGHT_PAWN_SELECTABLE && light <= ITF_IDX_LIGHT_JOKEY_STRIKABLE)) {
            container[light]->paint_rect(ITF_C_YELLOW, ITF_HIGH_INTEN, ITF_RCT_FULL, 4, 4);
            container[light]->paint_rect(ITF_C_YELLOW, ITF_LOW_INTEN, ITF_RCT_HLOW, 4, 4);

            
        }
    }

    for(int cmpl = 0; cmpl < ITF_COUNT_IDX; cmpl++) {
        //compilation of the squeres
        container[cmpl]->create_build();
        container[cmpl]->create_buffer();
    }
}

void itf_clean_content(std::vector<itf_tile*>& container)
{
    for(int clean = 0; clean < ITF_COUNT_IDX; clean++) delete container[clean];
}

#endif