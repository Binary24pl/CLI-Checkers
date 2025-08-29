//finish it later;

void itf_board::init() {
    if(this->board_height == -1 || this->board_width == -1) {
        return;
    }

    itf_preload_content(this->pre_gen_content);

    this->buffer_size = this->pre_gen_content[ITF_IDX_EMPTY]->tile_buffer.size();

    this->state_visual = new itf_preload_idx*[this->board_height];
    for(int sv = 0; sv < this->board_height; sv++) {
        this->state_visual[sv] = new itf_preload_idx[this->board_width];
    }
}

void itf_board::show_visual_state() {
    this->top_numeric_indexies();

    itf_text_pallete used_color;
    used_color.bg_color = ITF_C_BLACK;
    used_color.fg_color = ITF_C_RED;
    used_color.bg_inten = ITF_LOW_INTEN;
    used_color.fg_inten = ITF_HIGH_INTEN;

    std::vector<std::string> local_bfr;
    for(int start_vals = 0; start_vals < this->buffer_size; start_vals++) local_bfr.push_back("");

    for(int on_hght = 0; on_hght < this->board_height; on_hght++) {
        for(int rst_bfr = 0; rst_bfr < this->buffer_size; rst_bfr++) local_bfr[rst_bfr] = "";

        for(int on_wdth = 0; on_wdth < this->board_width; on_wdth++) {
            const std::vector<std::string> other_buffer = this->pre_gen_content[this->state_visual[on_hght][on_wdth]]->tile_buffer;

            for(int add_bfr = 0; add_bfr < this->buffer_size; add_bfr++) local_bfr[add_bfr] += other_buffer[add_bfr];
        }

        for(int shw_bfr = 0; shw_bfr < this->buffer_size; shw_bfr++) {
            std::cout << local_bfr[shw_bfr];
            if(shw_bfr != this->buffer_size - 1) std::cout << std::endl;
        }
        int letter_index_num = (int)'A';
        letter_index_num += on_hght;

        char letter_index_char = (char)letter_index_num;
        
        std::string letter_index_str = "";
        letter_index_str += letter_index_char;

        letter_index_str = itf_give_color(letter_index_str, used_color);
        std::cout << letter_index_str << std::endl;
        
    }
}

void itf_board::top_numeric_indexies() {
    std::string to_view = "";

    itf_text_pallete used_color;
    used_color.bg_color = ITF_C_BLACK;
    used_color.fg_color = ITF_C_RED;
    used_color.bg_inten = ITF_LOW_INTEN;
    used_color.fg_inten = ITF_HIGH_INTEN;

    for(int idx = 0; idx < this->board_width; idx++) {
        std::string num = common_translate_value<int, std::string>(idx + 1);
        int diff = this->tile_width - num.length();

        num = itf_give_color(num, used_color);

        to_view += num;
        for(int wh_ch = 0; wh_ch < diff; wh_ch++) to_view += " ";
    }

    std::cout << to_view << std::endl;
}

void itf_board::test() {
    for(int on_hght = 0; on_hght < this->board_height; on_hght++) {
        for(int on_wdth = 0; on_wdth < this->board_width; on_wdth++) {
            if(on_hght % 2 == on_wdth % 2) {
                this->state_visual[on_hght][on_wdth] = ITF_IDX_EMPTY;
            } else {
                this->state_visual[on_hght][on_wdth] = ITF_IDX_NON_PLAYABLE;
            }
        }
    }
}

void itf_board::read_vals(const common_board_interface& our_vals) {
    for(int on_hght = 0; on_hght < this->board_height; on_hght++) {
        for(int on_wdth = 0; on_wdth < this->board_width; on_wdth++) {
            this->state_visual[on_hght][on_wdth] = ITF_IDX_NON_PLAYABLE;
        }
    }

    for(int read_tiles = 0; read_tiles < our_vals.playable.size(); read_tiles++) {
        if(our_vals.playable[read_tiles].current_state != CMN_STAT_STRIKABLE) {
            if(our_vals.playable[read_tiles].current_state == CMN_STAT_NEITHER) {
                this->state_visual[our_vals.playable[read_tiles].position.on_height][our_vals.playable[read_tiles].position.on_width] = ITF_IDX_EMPTY;
            } else if(our_vals.playable[read_tiles].current_state == CMN_STAT_SELECTABLE) {
                this->state_visual[our_vals.playable[read_tiles].position.on_height][our_vals.playable[read_tiles].position.on_width] = ITF_IDX_SELECTABLE_EMPTY;
            } else if(our_vals.playable[read_tiles].current_state == CMN_STAT_SELECTED) {
                this->state_visual[our_vals.playable[read_tiles].position.on_height][our_vals.playable[read_tiles].position.on_width] = ITF_IDX_SELECTED_EMPTY;
            }
        }
    }

    for(int read_pawns = 0; read_pawns < our_vals.pawns.size(); read_pawns++) {
        this->handle_pawn(our_vals.pawns[read_pawns]);
    }
}

void itf_board::handle_pawn(const common_board_pawns& our_pawn)
{
    const common_board_pawns_types our_type = our_pawn.type;
    const common_states our_state = our_pawn.current_state;
    const common_position our_pos = our_pawn.position;

    switch(our_type) {
        case CMN_PAWN_LIGHT : {
            switch(our_state) {
                case CMN_STAT_NEITHER : {
                    this->state_visual[our_pos.on_height][our_pos.on_width] = ITF_IDX_LIGHT_PAWN;
                    break;
                }

                case CMN_STAT_SELECTABLE : {
                    this->state_visual[our_pos.on_height][our_pos.on_width] = ITF_IDX_LIGHT_PAWN_SELECTABLE;
                    break;
                }

                case CMN_STAT_SELECTED : {
                    this->state_visual[our_pos.on_height][our_pos.on_width] = ITF_IDX_LIGHT_PAWN_SELECTED;
                    break;
                }

                case CMN_STAT_STRIKABLE : {
                    this->state_visual[our_pos.on_height][our_pos.on_width] = ITF_IDX_LIGHT_PAWN_STRIKABLE;
                    break;
                }

                default : {}
            }
            break;
        }

        case CMN_PAWN_DARK : {
            switch(our_state) {
                case CMN_STAT_NEITHER : {
                    this->state_visual[our_pos.on_height][our_pos.on_width] = ITF_IDX_DARK_PAWN;
                    break;
                }

                case CMN_STAT_SELECTABLE : {
                    this->state_visual[our_pos.on_height][our_pos.on_width] = ITF_IDX_DARK_PAWN_SELECTABLE;
                    break;
                }

                case CMN_STAT_SELECTED : {
                    this->state_visual[our_pos.on_height][our_pos.on_width] = ITF_IDX_DARK_PAWN_SELECTED;
                    break;
                }

                case CMN_STAT_STRIKABLE : {
                    this->state_visual[our_pos.on_height][our_pos.on_width] = ITF_IDX_DARK_PAWN_STRIKABLE;
                    break;
                }

                default : {}
            }
            break;
        }

        case CMN_JOKEY_LIGHT : {
            switch(our_state) {
                case CMN_STAT_NEITHER : {
                    this->state_visual[our_pos.on_height][our_pos.on_width] = ITF_IDX_LIGHT_JOKEY;
                    break;
                }

                case CMN_STAT_SELECTABLE : {
                    this->state_visual[our_pos.on_height][our_pos.on_width] = ITF_IDX_LIGHT_JOKEY_SELECTABLE;
                    break;
                }

                case CMN_STAT_SELECTED : {
                    this->state_visual[our_pos.on_height][our_pos.on_width] = ITF_IDX_LIGHT_JOKEY_SELECTED;
                    break;
                }

                case CMN_STAT_STRIKABLE : {
                    this->state_visual[our_pos.on_height][our_pos.on_width] = ITF_IDX_LIGHT_JOKEY_STRIKABLE;
                    break;
                }

                default : {}
            }
            break;
        }

        case CMN_JOKEY_DARK : {
            switch(our_state) {
                case CMN_STAT_NEITHER : {
                    this->state_visual[our_pos.on_height][our_pos.on_width] = ITF_IDX_DARK_JOKEY;
                    break;
                }

                case CMN_STAT_SELECTABLE : {
                    this->state_visual[our_pos.on_height][our_pos.on_width] = ITF_IDX_DARK_JOKEY_SELECTABLE;
                    break;
                }

                case CMN_STAT_SELECTED : {
                    this->state_visual[our_pos.on_height][our_pos.on_width] = ITF_IDX_DARK_JOKEY_SELECTED;
                    break;
                }

                case CMN_STAT_STRIKABLE : {
                    this->state_visual[our_pos.on_height][our_pos.on_width] = ITF_IDX_DARK_JOKEY_STRIKABLE;
                    break;
                }

                default : {}
            }
            break;
        }

        default : {}
    }
}