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