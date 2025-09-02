gam_select_results gam_board::scenario_select(const bool& whose_turn, const common_position& pos)
{
    if(this->think_movable(whose_turn, pos)) return GAM_SLT_VALID;

    return GAM_SLT_INVALID;
}

gam_select_results gam_board::scenario_pre_move(const bool& whose_turn, const common_position& pos, const common_position end)
{
    if(pos.on_height == end.on_height && pos.on_width == end.on_width) return GAM_SLT_UNSELECT;

    if(this->think_options(whose_turn, pos, end)) return GAM_SLT_VALID;

    return GAM_SLT_INVALID;
}

gam_move_results gam_board::scenario_post_move(const bool& whose_turn, const common_position& origin, const common_position& end)
{
    if(origin.on_height < 0 || origin.on_width < 0 || origin.on_height >= this->board_height || origin.on_width >= this->board_width) return GAM_MOV_INVALID;

    if(end.on_height < 0 || end.on_width < 0 || end.on_height >= this->board_height || end.on_width >= this->board_width) return GAM_MOV_INVALID;

    if(this->think_options(whose_turn, origin, end) == false) return GAM_MOV_INVALID;

    common_position possible_strike;

    if(origin.on_height < end.on_height) {
        possible_strike.on_height = end.on_height - 1;
    } else {
        possible_strike.on_height = end.on_height + 1;
    }

    if(origin.on_width < end.on_width) {
        possible_strike.on_width = end.on_width - 1;
    } else {
        possible_strike.on_height = end.on_width + 1;
    }

    gam_move_results end_results = GAM_MOV_FINISHED;

    if(this->think_strike(whose_turn, origin, end, possible_strike)) {
        if(this->think_restrike(whose_turn, origin, end, possible_strike)) end_results = GAM_MOV_UNFINISHED;

        this->board_pos[possible_strike.on_height][possible_strike.on_width] = GAM_REP_EMPTY;
    }

    const gam_pawn_rep our_piece = this->board_pos[origin.on_height][origin.on_width];

    this->board_pos[end.on_height][end.on_width] = our_piece;
    this->board_pos[origin.on_height][origin.on_width] = GAM_REP_EMPTY;

    return end_results;
}

gam_move_results gam_board::scenario_restrike(const bool& whose_turn, const common_position& origin, const common_position& end)
{
    std::vector<common_position> strikes, ends;
    
    void(gam_board::*check_chain)(const common_position&, std::vector<common_position>&, std::vector<common_position>&) = nullptr;

    if(whose_turn) {
        check_chain = &gam_board::give_chain_strike<GAM_REP_DARK_PAWN, GAM_REP_DARK_JOKEY>;
    } else {
        check_chain = &gam_board::give_chain_strike<GAM_REP_LIGHT_PAWN, GAM_REP_LIGHT_JOKEY>;
    }

    (this->*check_chain)(origin, strikes, ends);

    if(strikes.size() != ends.size()) return GAM_MOV_INVALID;

    int idx = -1;

    for(int i = 0; i < ends.size(); i++) {
        if(end.on_height == ends[i].on_height && end.on_width == ends[i].on_width) {
            idx = i;
            break;
        }
    }

    if(idx < 0) return GAM_MOV_INVALID;

    const common_position to_strike = strikes[idx];
    const gam_pawn_rep our_piece = this->board_pos[origin.on_height][origin.on_width];

    bool results = this->think_restrike(whose_turn, origin, end, to_strike);

    this->board_pos[end.on_height][end.on_width] = our_piece;
    this->board_pos[origin.on_height][origin.on_width] = GAM_REP_EMPTY;
    this->board_pos[to_strike.on_height][to_strike.on_width] = GAM_REP_EMPTY;

    if(results) return GAM_MOV_UNFINISHED;

    return GAM_MOV_FINISHED;
}