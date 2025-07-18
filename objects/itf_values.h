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
    ITF_IDX_LIGHT_PAWN_SELECTABLE = 6,
    ITF_IDX_LIGHT_PAWN_SELECTED = 7,
    ITF_IDX_LIGHT_PAWN_STRIKABLE = 8,
    ITF_IDX_LIGHT_JOKEY_SELECTABLE = 9,
    ITF_IDX_LIGHT_JOKEY_SELECTED = 10,
    ITF_IDX_LIGHT_JOKEY_STRIKABLE = 11,
    ITF_IDX_DARK_PAWN = 12,
    ITF_IDX_DARK_JOKEY = 13,
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

    //coloring
    const itf_colors non_playable_c = ITF_C_BLACK;
    const bool non_playable_i = ITF_HIGH_INTEN;

    const itf_colors playable_c = ITF_C_GREEN;
    const bool playable_i = ITF_LOW_INTEN;

    const itf_colors light_c = ITF_C_WHITE;

    const itf_colors dark_c = ITF_C_YELLOW;

    const bool all_slct_i = ITF_HIGH_INTEN;
    const itf_colors to_slct = ITF_C_BLUE;
    const itf_colors slct_ed = ITF_C_CYAN;
    const itf_colors strike = ITF_C_RED;

    //implementing backgrounds
    container[ITF_IDX_NON_PLAYABLE]->paint_fill(non_playable_c, non_playable_i);
    for(int bg = ITF_IDX_EMPTY; bg < ITF_COUNT_IDX; bg++) {
        container[bg]->paint_fill(playable_c, playable_i);
    }

    //making new layer for pawns and jokeys
    for(int elms = ITF_IDX_LIGHT_PAWN; elms < ITF_COUNT_IDX; elms++) {
        container[elms]->create_new_layer(ITF_MOVE_PEN);
        container[elms]->draw_pencil.on_hght = 2;
        container[elms]->draw_pencil.on_wdth = 2;
    }

    //light
    for(int lght = ITF_IDX_LIGHT_PAWN; lght <= ITF_IDX_LIGHT_JOKEY_STRIKABLE; lght++) {
        container[lght]->paint_rect(light_c, ITF_HIGH_INTEN, ITF_RCT_FULL, 4, 4);
        container[lght]->paint_rect(light_c, ITF_LOW_INTEN, ITF_RCT_HLOW, 4, 4);

        container[lght]->draw_pencil.on_hght = 1;
        container[lght]->draw_pencil.on_wdth = 3;
        container[lght]->paint_line(light_c, ITF_LOW_INTEN, ITF_D_RIGHT, 2);
        container[lght]->draw_pencil.on_hght = 2;
        container[lght]->paint_line(light_c, ITF_HIGH_INTEN, ITF_D_RIGHT, 2);

        container[lght]->draw_pencil.on_hght = 6;
        container[lght]->paint_line(light_c, ITF_LOW_INTEN, ITF_D_RIGHT, 2);
        container[lght]->draw_pencil.on_hght = 5;
        container[lght]->paint_line(light_c, ITF_HIGH_INTEN, ITF_D_RIGHT, 2);

        container[lght]->draw_pencil.on_hght = 3;
        container[lght]->draw_pencil.on_wdth = 1;
        container[lght]->paint_line(light_c, ITF_LOW_INTEN, ITF_D_DOWN, 2);
        container[lght]->draw_pencil.on_wdth = 2;
        container[lght]->paint_line(light_c, ITF_HIGH_INTEN, ITF_D_DOWN, 2);

        container[lght]->draw_pencil.on_wdth = 6;
        container[lght]->paint_line(light_c, ITF_LOW_INTEN, ITF_D_DOWN, 2);
        container[lght]->draw_pencil.on_wdth = 5;
        container[lght]->paint_line(light_c, ITF_HIGH_INTEN, ITF_D_DOWN, 2);

        if(lght == ITF_IDX_LIGHT_JOKEY || (lght >= ITF_IDX_LIGHT_JOKEY_SELECTABLE && lght <= ITF_IDX_DARK_JOKEY_STRIKABLE)) {
            container[lght]->draw_pencil.on_hght = 3;
            container[lght]->draw_pencil.on_wdth = 3;
            container[lght]->paint_rect(light_c, ITF_LOW_INTEN, ITF_RCT_FULL, 2, 2);
        }

        container[lght]->draw_pencil.on_hght = 0;
        container[lght]->draw_pencil.on_wdth = 0;
    }

    for(int dark = ITF_IDX_DARK_PAWN; dark <= ITF_IDX_DARK_JOKEY_STRIKABLE; dark++) {
        container[dark]->paint_rect(dark_c, ITF_HIGH_INTEN, ITF_RCT_FULL, 4, 4);
        container[dark]->paint_rect(dark_c, ITF_LOW_INTEN, ITF_RCT_HLOW, 4, 4);

        container[dark]->draw_pencil.on_hght = 1;
        container[dark]->draw_pencil.on_wdth = 3;
        container[dark]->paint_line(dark_c, ITF_LOW_INTEN, ITF_D_RIGHT, 2);
        container[dark]->draw_pencil.on_hght = 2;
        container[dark]->paint_line(dark_c, ITF_HIGH_INTEN, ITF_D_RIGHT, 2);

        container[dark]->draw_pencil.on_hght = 6;
        container[dark]->paint_line(dark_c, ITF_LOW_INTEN, ITF_D_RIGHT, 2);
        container[dark]->draw_pencil.on_hght = 5;
        container[dark]->paint_line(dark_c, ITF_HIGH_INTEN, ITF_D_RIGHT, 2);

        container[dark]->draw_pencil.on_hght = 3;
        container[dark]->draw_pencil.on_wdth = 1;
        container[dark]->paint_line(dark_c, ITF_LOW_INTEN, ITF_D_DOWN, 2);
        container[dark]->draw_pencil.on_wdth = 2;
        container[dark]->paint_line(dark_c, ITF_HIGH_INTEN, ITF_D_DOWN, 2);

        container[dark]->draw_pencil.on_wdth = 6;
        container[dark]->paint_line(dark_c, ITF_LOW_INTEN, ITF_D_DOWN, 2);
        container[dark]->draw_pencil.on_wdth = 5;
        container[dark]->paint_line(dark_c, ITF_HIGH_INTEN, ITF_D_DOWN, 2);

        if(dark == ITF_IDX_DARK_JOKEY || (dark >= ITF_IDX_DARK_JOKEY_SELECTABLE && dark <= ITF_IDX_DARK_JOKEY_STRIKABLE)) {
            container[dark]->draw_pencil.on_hght = 3;
            container[dark]->draw_pencil.on_wdth = 3;
            container[dark]->paint_rect(dark_c, ITF_LOW_INTEN, ITF_RCT_FULL, 2, 2);
        }

        container[dark]->draw_pencil.on_hght = 0;
        container[dark]->draw_pencil.on_wdth = 0;
    }

    for(int nwlr = 0; nwlr < ITF_COUNT_IDX; nwlr++) {
        if((nwlr >= ITF_IDX_SELECTABLE_EMPTY && nwlr <= ITF_IDX_SELECTED_EMPTY) || (nwlr >= ITF_IDX_LIGHT_PAWN_SELECTABLE && nwlr <= ITF_IDX_DARK_JOKEY_STRIKABLE)) {
            container[nwlr]->create_new_layer(ITF_MOVE_PEN);
        }
    }

    for(int idx_slct = 0; idx_slct < ITF_COUNT_IDX; idx_slct++) {
        if(idx_slct == ITF_IDX_SELECTABLE_EMPTY || idx_slct == ITF_IDX_LIGHT_PAWN_SELECTABLE || idx_slct == ITF_IDX_LIGHT_JOKEY_SELECTABLE || idx_slct == ITF_IDX_DARK_PAWN_SELECTABLE || idx_slct == ITF_IDX_DARK_JOKEY_SELECTABLE) {
            container[idx_slct]->paint_rect(to_slct, all_slct_i, ITF_RCT_HLOW, 8, 8);
        } else if(idx_slct == ITF_IDX_SELECTED_EMPTY || idx_slct == ITF_IDX_LIGHT_PAWN_SELECTED || idx_slct == ITF_IDX_LIGHT_JOKEY_SELECTED || idx_slct == ITF_IDX_DARK_PAWN_SELECTED || idx_slct == ITF_IDX_DARK_JOKEY_SELECTED) {
            container[idx_slct]->paint_rect(slct_ed, all_slct_i, ITF_RCT_HLOW, 8, 8);
        } else if(idx_slct == ITF_IDX_LIGHT_PAWN_STRIKABLE || idx_slct == ITF_IDX_LIGHT_JOKEY_STRIKABLE || idx_slct == ITF_IDX_DARK_PAWN_STRIKABLE || idx_slct == ITF_IDX_DARK_JOKEY_STRIKABLE) {
            container[idx_slct]->paint_rect(strike, all_slct_i, ITF_RCT_HLOW, 8, 8);
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


class itf_board {
public:
    itf_board(const int& height, const int& width) {
        if(height % 2 != 0 || width % 2 != 0) {
            this->board_height = -1;
            this->board_width = -1;
        } else {
            this->board_height = height;
            this->board_width = width;
        }
    }

    ~itf_board() {
        //soon
    }
private:
    int board_height, board_width;
    int buffer_size;
    std::vector<itf_tile*> pre_gen_content;
};

#endif