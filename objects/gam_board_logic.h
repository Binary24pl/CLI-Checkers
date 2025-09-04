void gam_board_logic::init()
{
    if(this->board_height <= 0 || this->board_width <= 0) return;

    for(int on_hght = 0; on_hght < this->board_height; on_hght++) {
        for(int on_wdth = 0; on_wdth < this->board_width; on_wdth++) {
            if(on_hght % 2 == on_wdth % 2) {
                common_position on_pos;
                on_pos.on_height = on_hght;
                on_pos.on_width = on_wdth;

                if(on_hght == 7) {
                    gam_board_piece temp(10, 10);
                    temp.init(on_pos, GAM_DARK);

                    this->our_pieces.push_back(temp);
                    //std::cout << "Dark on: " <<  on_hght << " <:> " << on_wdth << std::endl;
                } else if(on_hght >= (this->board_height - 2)) {
                    gam_board_piece temp(10, 10);
                    temp.init(on_pos, GAM_LIGHT);

                    this->our_pieces.push_back(temp);
                    //std::cout << "Light on: " <<  on_hght << " <:> " << on_wdth << std::endl;
                }
            }
        }
    }
}

int gam_board_logic::find_piece_by_pos(const common_position& pos)
{
    for(int i = 0; i < this->our_pieces.size(); i++) {
        if(this->our_pieces[i].give_am_i_on_coords(pos)) return i;
    }

    return -1;
}

void gam_board_logic::find_sideway_coords(std::vector<std::vector<common_position>>& container, const common_position& pos, int& our_index)
{
    const int idx = this->find_piece_by_pos(pos);
    our_index = idx;

    if(idx == -1) return;

    container.clear();

    container = this->our_pieces[idx].give_possible_coords();
}

std::vector<gam_tile_rep> gam_board_logic::find_sideway_rep(const std::vector<common_position> sideway_cont)
{
    std::vector<gam_tile_rep> to_return;

    for(int tile = 0; tile <sideway_cont.size(); tile++) {
        const int idx = this->find_piece_by_pos(sideway_cont[tile]);

        if(idx == -1) {
            to_return.push_back(GAM_TLE_EMPTY);
        } else {
            const common_board_pawns_types our_type = this->our_pieces[idx].give_my_type();

            if(our_type == CMN_PAWN_LIGHT || our_type == CMN_JOKEY_LIGHT) {
                to_return.push_back(GAM_TLE_LIGHT);
            } else if(our_type == CMN_PAWN_DARK || our_type == CMN_JOKEY_DARK) {
                to_return.push_back(GAM_TLE_DARK);
            }
        }
    }

    return to_return;
}

//how much can we shift
int gam_board_logic::count_move(const common_position& pos, const gam_relative_directions& direction)
{
    int to_return = 0;

    int idx;
    std::vector<std::vector<common_position>> sides;

    this->find_sideway_coords(sides, pos, idx);

    if(idx == -1) return -1;

    std::vector<gam_tile_rep> tiles;
    tiles = this->find_sideway_rep(sides[direction]);

    std::vector<gam_mov_results> moves;

    bool limits = this->our_pieces[idx].pass_jokey();
    moves = this->our_pieces[idx].give_mov_results(tiles, limits);

    for(int i = 0; i < moves.size(); i++) {
        if(moves[i] == GAM_MOV_SHIFT) {
            to_return += 1;
        } else {
            break;
        }
    }
    

    return to_return;
}

//idx of a strike
int gam_board_logic::count_strike(const common_position& pos, const gam_relative_directions& direction, const bool& is_restrike_check)
{
    int idx;
    std::vector<std::vector<common_position>> sides;

    this->find_sideway_coords(sides, pos, idx);

    if(idx == -1) return -1;

    bool limitations = false;
    if(is_restrike_check) {
        limitations = true;
    } else {
        if(this->our_pieces[idx].pass_jokey() == false) {
            limitations = true;
        }
    }

    std::vector<gam_tile_rep> tiles;
    tiles = this->find_sideway_rep(sides[direction]);

    std::vector<gam_mov_results> moves;

    moves = this->our_pieces[idx].give_mov_results(tiles, limitations);

    for(int i = 0; i < moves.size(); i++) {
        if(moves[i] == GAM_MOV_STRIKE) return i;
    }
    
    return -1;
}

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

std::vector<common_position> gam_board_logic::compose_movable(const bool& whose_turn)
{
    std::vector<common_position> to_return;

    for(int on_hght = 0; on_hght < this->board_height; on_hght++) {
        for(int on_wdth = 0; on_wdth < this->board_width; on_wdth++) {
            common_position current_pos;

            current_pos.on_height = on_hght;
            current_pos.on_width = on_wdth;

            this->get_movable(current_pos, to_return, whose_turn);
        }
    }

    return to_return;
}

std::vector<common_position> gam_board_logic::compose_strikable(const bool& whose_turn)
{
    std::vector<common_position> to_return;

    for(int on_hght = 0; on_hght < this->board_height; on_hght++) {
        for(int on_wdth = 0; on_wdth < this->board_width; on_wdth++) {
            common_position current_pos;

            current_pos.on_height = on_hght;
            current_pos.on_width = on_wdth;

            this->get_strikable(current_pos, to_return, whose_turn);
        }
    }

    return to_return;
}

std::vector<common_position> gam_board_logic::compose_to_strike(const common_position& relative_to, const std::vector<common_position>& strike_ends)
{
    std::vector<common_position> to_return;

    for(int i = 0; i < strike_ends.size(); i++) {
        common_position possible_strike;

        if(relative_to.on_height < strike_ends[i].on_height) {
            possible_strike.on_height = strike_ends[i].on_height - 1;
        } else {
            possible_strike.on_height = strike_ends[i].on_height + 1;
        }

        if(relative_to.on_width < strike_ends[i].on_width) {
            possible_strike.on_width = strike_ends[i].on_width - 1;
        } else {
            possible_strike.on_width = strike_ends[i].on_width + 1;
        }

        to_return.push_back(possible_strike);
    }

    return to_return;
}

std::vector<common_position> gam_board_logic::compose_selectable(const bool& whose_turn)
{
    std::vector<common_position> to_return = this->compose_movable(whose_turn);
    std::vector<common_position> temp = this->compose_strikable(whose_turn);

    if(temp.size() == 0) return to_return;

    for(int temp_idx = 0; temp_idx < temp.size(); temp_idx++) {
        bool is_duplicate = false;
        for(int ret_idx = 0; ret_idx < to_return.size(); ret_idx++) {
            if(temp[temp_idx].on_height == to_return[ret_idx].on_height && 
               temp[temp_idx].on_width == to_return[ret_idx].on_width) {
                is_duplicate = true;
                break;
            }
        }
        if(is_duplicate == false) {
            to_return.push_back(temp[temp_idx]);
        }
    }

    return to_return;
}

common_board_interface gam_board_logic::communicate_with_interface(const gam_round_phase& game_phase, const bool& whose_turn, const common_position& select = {-1, -1})
{
    common_board_interface to_return;

    switch(game_phase) {
        case GAM_PHS_START : {
            this->communicate_phase_start(whose_turn, to_return);
            break;
        }

        case GAM_PHS_SELECTED : {
            this->communicate_phase_selected(whose_turn, to_return, select);
            break;
        }

        default : {
            break;
        }
    };

    return to_return;
}

void gam_board_logic::communicate_phase_start(const bool& whose_turn, common_board_interface& to_edit)
{
    std::vector<common_position> our_poses = this->compose_selectable(whose_turn);

    for(int on_hght = 0; on_hght < this->board_height; on_hght++) {
        for(int on_wdth = 0; on_wdth < this->board_width; on_wdth++) {
            if(on_hght % 2 == on_wdth % 2) {
                common_position our_local;
                
                our_local.on_height = on_hght;
                our_local.on_width = on_wdth;

                this->communicate_handle_start(to_edit, our_local, our_poses);
            }
        }
    }
}

void gam_board_logic::communicate_handle_start(common_board_interface& to_edit, const common_position& local_pos, const std::vector<common_position>& local_poses)
{
    int work_idx;
    work_idx = this->find_piece_by_pos(local_pos);

    if(work_idx == -1) {
        common_board_playable temp;
        temp.current_state = CMN_STAT_NEITHER;

        temp.position.on_height = local_pos.on_height;
        temp.position.on_width = local_pos.on_width;

        to_edit.playable.push_back(temp);
        return;
    }

    common_board_pawns temp;
    temp.current_state = CMN_STAT_NEITHER;
    temp.type = this->our_pieces[work_idx].give_my_type();
    temp.position.on_height = local_pos.on_height;
    temp.position.on_width = local_pos.on_width;

    for(int check = 0; check < local_poses.size(); check++) {
        if(local_poses[check].on_height == local_pos.on_height && local_poses[check].on_width == local_pos.on_width) {
            temp.current_state = CMN_STAT_SELECTABLE;
            break;
        }
    }

    to_edit.pawns.push_back(temp);
}

void gam_board_logic::communicate_phase_selected(const bool& whose_turn, common_board_interface& to_edit, const common_position& selection)
{
    std::vector<common_position> moves, strikes, enemies;
    moves = this->get_move_to(selection);
    strikes = this->compose_strikable(whose_turn);
    enemies = this->compose_to_strike(selection, strikes);

    for(int on_hght = 0; on_hght < this->board_height; on_hght++) {
        for(int on_wdth = 0; on_wdth < this->board_width; on_wdth++) {
            if(on_hght % 2 == on_wdth % 2) {
                common_position our_local;
                
                our_local.on_height = on_hght;
                our_local.on_width = on_wdth;

                this->communicate_handle_selected(to_edit, our_local, selection, moves, strikes, enemies);
            }
        }
    }
}

void gam_board_logic::communicate_handle_selected(common_board_interface& to_eidt, const common_position& local_pos, const common_position& current_pos, const std::vector<common_position>& move_points, const std::vector<common_position>& strike_points, const std::vector<common_position>& to_strike)
{
    int work_idx;
    work_idx = this->find_piece_by_pos(local_pos);

    if(work_idx == -1) {
        common_board_playable temp;
        temp.position.on_height = local_pos.on_height;
        temp.position.on_width = local_pos.on_width;
        temp.current_state = CMN_STAT_NEITHER;

        for(int chk_mov = 0; chk_mov < move_points.size(); chk_mov++) {
            if(move_points[chk_mov].on_height == local_pos.on_height && move_points[chk_mov].on_width == local_pos.on_width) {
                temp.current_state = CMN_STAT_SELECTABLE;
                break;
            }
        }

        for(int chk_stk = 0; chk_stk < strike_points.size(); chk_stk++) {
            if(strike_points[chk_stk].on_height == local_pos.on_height && strike_points[chk_stk].on_width == local_pos.on_width) {
                temp.current_state = CMN_STAT_SELECTABLE;
                break;
            }
        }

        to_eidt.playable.push_back(temp);
        return;
    }

    common_board_pawns temp;
    temp.current_state = CMN_STAT_NEITHER;
    temp.type = this->our_pieces[work_idx].give_my_type();
    temp.position.on_height = local_pos.on_height;
    temp.position.on_width = local_pos.on_width;

    if(local_pos.on_height == current_pos.on_height && local_pos.on_width == current_pos.on_width) {
        temp.current_state = CMN_STAT_SELECTED;
    }

    for(int chk_enm = 0; chk_enm < to_strike.size(); chk_enm++) {
        if(local_pos.on_height == to_strike[chk_enm].on_height && local_pos.on_width == to_strike[chk_enm].on_width) {
            temp.current_state = CMN_STAT_STRIKABLE;
            break;
        }
    }

    to_eidt.pawns.push_back(temp);
}