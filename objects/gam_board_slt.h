//options lounge

void gam_board::give_options(const bool& whose_turn, gam_piece_move& our_opts, const common_position& our_pos, const bool& unlimited)
{
    void (gam_board::*up_left)(gam_piece_move&, const common_position&, const bool&) = nullptr;
    void (gam_board::*up_right)(gam_piece_move&, const common_position&, const bool&) = nullptr;
    void (gam_board::*down_left)(gam_piece_move&, const common_position&, const bool&) = nullptr;
    void (gam_board::*down_right)(gam_piece_move&, const common_position&, const bool&) = nullptr;

    if(whose_turn) {
        up_left = &gam_board::sideway_options<-1, -1, GAM_REP_DARK_PAWN, GAM_REP_DARK_JOKEY>;
        up_right = &gam_board::sideway_options<-1, 1, GAM_REP_DARK_PAWN, GAM_REP_DARK_JOKEY>;
        down_left = &gam_board::sideway_options<1, -1, GAM_REP_DARK_PAWN, GAM_REP_DARK_JOKEY>;
        down_right = &gam_board::sideway_options<1, 1, GAM_REP_DARK_PAWN, GAM_REP_DARK_JOKEY>;
    } else {
        up_left = &gam_board::sideway_options<-1, -1, GAM_REP_LIGHT_PAWN, GAM_REP_LIGHT_JOKEY>;
        up_right = &gam_board::sideway_options<-1, 1, GAM_REP_LIGHT_PAWN, GAM_REP_LIGHT_JOKEY>;
        down_left = &gam_board::sideway_options<1, -1, GAM_REP_LIGHT_PAWN, GAM_REP_LIGHT_JOKEY>;
        down_right = &gam_board::sideway_options<1, 1, GAM_REP_LIGHT_PAWN, GAM_REP_LIGHT_JOKEY>;
    }

    if(unlimited) {
        (this->*up_left)(our_opts, our_pos, unlimited);
        (this->*up_right)(our_opts, our_pos, unlimited);
        (this->*down_left)(our_opts, our_pos, unlimited);
        (this->*down_right)(our_opts, our_pos, unlimited);
    } else {
        if(whose_turn) {
            (this->*up_left)(our_opts, our_pos, unlimited);
            (this->*up_right)(our_opts, our_pos, unlimited);
        } else {
            (this->*down_left)(our_opts, our_pos, unlimited);
            (this->*down_right)(our_opts, our_pos, unlimited);
        }
    }
}

template<int fronts, int sides, gam_pawn_rep strikable_pawn, gam_pawn_rep strikable_jokey>
void gam_board::sideway_options(gam_piece_move& our_opts, const common_position& our_pos, const bool& unlimited)
{
    common_position next_pos;
    next_pos.on_height = our_pos.on_height + fronts;
    next_pos.on_width = our_pos.on_width + sides;

    if(next_pos.on_height < 0 || next_pos.on_width < 0 || next_pos.on_height >= this->board_height || next_pos.on_width >= this->board_width) return;

    common_position no_strike;
    no_strike.on_height = -1;
    no_strike.on_width = -1;

    if(this->board_pos[next_pos.on_height][next_pos.on_width] != GAM_REP_EMPTY && this->board_pos[next_pos.on_height][next_pos.on_width] != strikable_pawn && this->board_pos[next_pos.on_height][next_pos.on_width] != strikable_jokey) return;

    if(this->board_pos[next_pos.on_height][next_pos.on_width] == GAM_REP_EMPTY) {
        our_opts.possible_next_strike.push_back(false);
        our_opts.possible_points.push_back(next_pos);
        our_opts.strike_positions.push_back(no_strike);

        if(unlimited) {
            this->sideway_options<fronts, sides, strikable_pawn, strikable_jokey>(our_opts, next_pos, unlimited);
        }

        return;
    }

    common_position behind_enemy;
    behind_enemy.on_height = next_pos.on_height + fronts;
    behind_enemy.on_width = next_pos.on_width + sides;

    if(behind_enemy.on_height < 0 || behind_enemy.on_width < 0; behind_enemy.on_height >= this->board_height || behind_enemy.on_width >= board_width) return;

    if(this->board_pos[behind_enemy.on_height][behind_enemy.on_width] != GAM_REP_EMPTY) return;

    our_opts.possible_points.push_back(behind_enemy);
    our_opts.strike_positions.push_back(next_pos);

    this->strike_options<fronts, sides, strikable_pawn, strikable_jokey>(our_opts, behind_enemy);
}

template<int fronts, int sides, gam_pawn_rep strikable_pawn, gam_pawn_rep strikable_jokey>
void gam_board::strike_options(gam_piece_move& our_opts, const common_position& our_pos)
{
    const int coords = 3;

    common_position calc_vals[coords];

    calc_vals[0].on_height = fronts * -1;
    calc_vals[0].on_width = sides * -1;

    calc_vals[1].on_height = fronts;
    calc_vals[1].on_width = sides * -1;

    calc_vals[2].on_height = fronts * -1;
    calc_vals[2].on_width = sides;

    common_position possible_enemies[coords];
    common_position possibly_behind_em[coords];

    bool multiple = false;

    for(int i = 0; i < coords; i++) {
        possible_enemies[i].on_height = our_pos.on_height + (calc_vals[i].on_height * 1);
        possible_enemies[i].on_width = our_pos.on_width + (calc_vals[i].on_width * 1);

        possibly_behind_em[i].on_height = our_pos.on_height + (calc_vals[i].on_height * 1);
        possibly_behind_em[i].on_width = our_pos.on_width + (calc_vals[i].on_width * 1);
    }

    for(int check = 0; check < coords; check++) {
        if(possibly_behind_em[check].on_height >= 0 && possibly_behind_em[check].on_width >= 0 && possibly_behind_em[check].on_height < this->board_height && possibly_behind_em[check].on_width < this->board_width) {
            if((this->board_pos[possible_enemies[check].on_height][possible_enemies[check].on_width] == strikable_pawn || this->board_pos[possible_enemies[check].on_height][possible_enemies[check].on_width] == strikable_jokey) && this->board_pos[possibly_behind_em[check].on_height][possibly_behind_em[check].on_width] == GAM_REP_EMPTY) {
                multiple = true;
                break;
            }
        }
    }

    our_opts.possible_next_strike.push_back(multiple);
}

void gam_board::handle_position_sltd(int on_hght, int on_wdth, common_board_interface& interface, const gam_piece_move& options, const common_position& selected)
{
    gam_pawn_rep our_tile = this->board_pos[on_hght][on_wdth];

    if(our_tile == GAM_REP_EMPTY) {
        common_board_playable temp;

        temp.position.on_height = on_hght;
        temp.position.on_width = on_wdth;

        temp.current_state = CMN_STAT_NEITHER;

        for(int i = 0; i < options.possible_points.size(); i++) {
            if(options.possible_points[i].on_height == on_hght && options.possible_points[i].on_width == on_wdth) {
                temp.current_state = CMN_STAT_SELECTABLE;
                break;
            }
        }

        interface.playable.push_back(temp);
        return;
    }

    common_board_pawns temp;
    temp.position.on_height = on_hght;
    temp.position.on_width = on_wdth;

    switch(our_tile) {
        case GAM_REP_LIGHT_PAWN : {
            temp.type = CMN_PAWN_LIGHT;
            break;
        }

        case GAM_REP_LIGHT_JOKEY : {
            temp.type = CMN_JOKEY_LIGHT;
            break;
        }

        case GAM_REP_DARK_PAWN : {
            temp.type = CMN_PAWN_DARK;
            break;
        }

        case GAM_REP_DARK_JOKEY : {
            temp.type = CMN_JOKEY_DARK;
            break;
        }

        default : {
            break;
        }
    }

    temp.current_state = CMN_STAT_NEITHER;

    if(on_hght == selected.on_height && on_wdth == selected.on_width) {
        temp.current_state = CMN_STAT_SELECTED;
    } else {
        for(int i = 0; i < options.strike_positions.size(); i++) {
            if(options.strike_positions[i].on_height == on_hght && options.strike_positions[i].on_width == on_wdth) {
                temp.current_state = CMN_STAT_STRIKABLE;
            }
        }
    }

    interface.pawns.push_back(temp);
}