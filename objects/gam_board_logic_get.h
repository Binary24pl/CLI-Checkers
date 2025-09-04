std::vector<common_position> gam_board_logic::get_move_to(const common_position& pos)
{
    std::vector<common_position> to_return;

    int work_idx;

    std::vector<std::vector<common_position>> temp_coords;
    this->find_sideway_coords(temp_coords, pos, work_idx);

    if(work_idx == -1) return to_return;

    int up_left, up_right, down_left, down_right;
    up_left = up_right = down_left = down_right = 0;

    const common_board_pawns_types identiy = this->our_pieces[work_idx].give_my_type();

    if(identiy == CMN_JOKEY_LIGHT || identiy == CMN_JOKEY_DARK) {
        up_left = this->count_move(pos, GAM_DRCT_FRONT_LEFT);
        up_right = this->count_move(pos, GAM_DRCT_FRONT_RIGHT);
        down_left = this->count_move(pos, GAM_DRCT_BACK_LEFT);
        down_right = this->count_move(pos, GAM_DRCT_BACK_RIGHT);
    } else if(identiy == CMN_PAWN_LIGHT) {
        up_left = this->count_move(pos, GAM_DRCT_FRONT_LEFT);
        up_right = this->count_move(pos, GAM_DRCT_FRONT_RIGHT);
    } else if(identiy == CMN_PAWN_DARK) {
        down_left = this->count_move(pos, GAM_DRCT_BACK_LEFT);
        down_right = this->count_move(pos, GAM_DRCT_BACK_RIGHT);
    }

    for(int ul_add = 0; ul_add < up_left; ul_add++) {
        to_return.push_back(temp_coords[GAM_DRCT_FRONT_LEFT][ul_add]);
    }
    for(int ur_add = 0; ur_add < up_right; ur_add++) {
        to_return.push_back(temp_coords[GAM_DRCT_FRONT_RIGHT][ur_add]);
    }
    for(int dl_add = 0; dl_add < down_left; dl_add++) {
        to_return.push_back(temp_coords[GAM_DRCT_BACK_LEFT][dl_add]);
    }
    for(int dr_add = 0; dr_add < down_right; dr_add++) {
        to_return.push_back(temp_coords[GAM_DRCT_BACK_RIGHT][dr_add]);
    }

    return to_return;
}
void gam_board_logic::get_movable(const common_position& pos, std::vector<common_position>& to_add, const bool& whose_turn)
{
    int work_idx;
    work_idx = this->find_piece_by_pos(pos);

    if(work_idx == -1) return;

    if(whose_turn) {
        if(this->our_pieces[work_idx].give_my_type() == CMN_PAWN_DARK || this->our_pieces[work_idx].give_my_type() == CMN_JOKEY_DARK) return;
    } else {
        if(this->our_pieces[work_idx].give_my_type() == CMN_PAWN_LIGHT || this->our_pieces[work_idx].give_my_type() == CMN_JOKEY_LIGHT) return;
    }

    if(this->get_move_to(pos).size() > 0) {
        to_add.push_back(pos);
    }
}

std::vector<common_position> gam_board_logic::get_strike_to(const common_position& pos, const bool& is_restrike)
{
    std::vector<common_position> to_return;

    int work_idx;

    std::vector<std::vector<common_position>> temp_coords;
    this->find_sideway_coords(temp_coords, pos, work_idx);

    if(work_idx == -1) return to_return;

    int up_left, up_right, down_left, down_right;
    up_left = up_right = down_left = down_right = -1;

    const common_board_pawns_types identiy = this->our_pieces[work_idx].give_my_type();

    if(is_restrike || identiy == CMN_JOKEY_LIGHT || identiy == CMN_JOKEY_DARK) {
        up_left = this->count_strike(pos, GAM_DRCT_FRONT_LEFT, is_restrike);
        up_right = this->count_strike(pos, GAM_DRCT_FRONT_RIGHT, is_restrike);
        down_left = this->count_strike(pos, GAM_DRCT_BACK_LEFT, is_restrike);
        down_right = this->count_strike(pos, GAM_DRCT_BACK_RIGHT, is_restrike);
    } else if(identiy == CMN_PAWN_LIGHT) {
        up_left = this->count_strike(pos, GAM_DRCT_FRONT_LEFT, is_restrike);
        up_right = this->count_strike(pos, GAM_DRCT_FRONT_RIGHT, is_restrike);
    } else if(identiy == CMN_PAWN_DARK) {
        down_left = this->count_strike(pos, GAM_DRCT_BACK_LEFT, is_restrike);
        down_right = this->count_strike(pos, GAM_DRCT_BACK_RIGHT, is_restrike);
    }

    if(up_left != -1) {
        to_return.push_back(temp_coords[GAM_DRCT_FRONT_LEFT][up_left]);
    }
    if(up_right != -1) {
        to_return.push_back(temp_coords[GAM_DRCT_FRONT_RIGHT][up_right]);
    }
    if(down_left != -1) {
        to_return.push_back(temp_coords[GAM_DRCT_BACK_LEFT][down_left]);
    }
    if(down_right != -1) {
        to_return.push_back(temp_coords[GAM_DRCT_BACK_RIGHT][down_right]);
    }

    return to_return;
}

void gam_board_logic::get_strikable(const common_position& pos, std::vector<common_position>& to_add, const bool& whose_turn)
{
    int work_idx;
    work_idx = this->find_piece_by_pos(pos);

    if(work_idx == -1) return;

    if(whose_turn) {
        if(this->our_pieces[work_idx].give_my_type() == CMN_PAWN_DARK || this->our_pieces[work_idx].give_my_type() == CMN_JOKEY_DARK) return;
    } else {
        if(this->our_pieces[work_idx].give_my_type() == CMN_PAWN_LIGHT || this->our_pieces[work_idx].give_my_type() == CMN_JOKEY_LIGHT) return;
    }

    if(this->get_strike_to(pos, false).size() > 0) {
        to_add.push_back(pos);
    }
}

bool gam_board_logic::get_restrikeable(const common_position& pos)
{
    int work_idx;
    work_idx = this->find_piece_by_pos(pos);

    if(work_idx == -1) return false;

    if(this->get_strike_to(pos, true).size() > 0) return true;

    return false;
}