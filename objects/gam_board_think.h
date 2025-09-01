bool gam_board::think_movable(const bool& whose_turn, const common_position& at_pos)
{
    std::vector<common_position> possible_selections;
    this->give_movable(whose_turn, possible_selections);

    for(int i = 0; i < possible_selections.size(); i++) {
        if(possible_selections[i].on_height == at_pos.on_height && possible_selections[i].on_width == at_pos.on_width) return true;
    }

    return false;
}

bool gam_board::think_options(const bool& whose_turn, const common_position& at_pos, const common_position& to_pos)
{
    gam_piece_move our_options;

    if(at_pos.on_height < 0 || at_pos.on_width < 0 || at_pos.on_height >= this->board_height || at_pos.on_width >= this->board_width) return false;

    bool unlimited = false;
    if(this->board_pos[at_pos.on_height][at_pos.on_width] == GAM_REP_DARK_JOKEY || this->board_pos[at_pos.on_height][at_pos.on_width] == GAM_REP_LIGHT_JOKEY) unlimited = true;

    this->give_options(whose_turn, our_options, at_pos, unlimited);

    for(int i = 0; i < our_options.possible_points.size(); i++) {
        if(to_pos.on_height == our_options.possible_points[i].on_height && to_pos.on_width == our_options.possible_points[i].on_width) return true;
    }

    return false;
}

bool gam_board::think_strike(const bool& whose_turn, const common_position& at_pos, const common_position& to_pos, const common_position& strike_at)
{
    gam_piece_move our_options;

    if(at_pos.on_height < 0 || at_pos.on_width < 0 || at_pos.on_height >= this->board_height || at_pos.on_width >= this->board_width) return false;

    bool unlimited = false;
    if(this->board_pos[at_pos.on_height][at_pos.on_width] == GAM_REP_DARK_JOKEY || this->board_pos[at_pos.on_height][at_pos.on_width] == GAM_REP_LIGHT_JOKEY) unlimited = true;

    this->give_options(whose_turn, our_options, at_pos, unlimited);

    for(int i = 0; i < our_options.possible_points.size(); i++) {
        if(to_pos.on_height == our_options.possible_points[i].on_height && to_pos.on_width == our_options.possible_points[i].on_width) {
            if(our_options.strike_positions[i].on_height == strike_at.on_height && our_options.strike_positions[i].on_width == strike_at.on_width) return true;
        }
    }

    return false;
}

bool gam_board::think_restrike(const bool& whose_turn, const common_position& at_pos, const common_position& to_pos, const common_position& strike_at)
{
    if(at_pos.on_height < 0 || at_pos.on_width < 0 || at_pos.on_height >= this->board_height || at_pos.on_width >= this->board_width) return false;

    if(to_pos.on_height < 0 || to_pos.on_width < 0 || to_pos.on_height >= this->board_height || to_pos.on_width >= this->board_width) return false;

    if(strike_at.on_height < 0 || strike_at.on_width < 0 || strike_at.on_height >= this->board_height || strike_at.on_width >= this->board_width) return false;

    bool unlimited = false;
    if(this->board_pos[at_pos.on_height][at_pos.on_width] == GAM_REP_DARK_JOKEY || this->board_pos[at_pos.on_height][at_pos.on_width] == GAM_REP_LIGHT_JOKEY) unlimited = true;

    gam_piece_move our_options;

    this->give_options(whose_turn, our_options, at_pos, unlimited);

    if(our_options.possible_next_strike.size() != our_options.possible_points.size() && our_options.possible_points.size() != our_options.strike_positions.size()) return false;

    int local_size = our_options.possible_points.size();

    for(int i = 0; i < local_size; i++) {
        if(to_pos.on_height == our_options.possible_points[i].on_height && to_pos.on_width == our_options.possible_points[i].on_width && strike_at.on_height == our_options.strike_positions[i].on_height && strike_at.on_width == our_options.strike_positions[i].on_width) {
            return our_options.possible_next_strike[i];
        }
    }

    return false;
}