common_board_interface gam_board_logic::communicate_with_interface(const gam_round_phase& game_phase, const bool& whose_turn, const common_position& select = {-1, -1}, const common_position& move_to = {-1, -1})
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

        case GAM_PHS_PRE_MOVE : {
            this->communicate_phase_pre(to_return, select, move_to);
            break;
        }

        case GAM_PHS_CHAIN_START : {
            this->communicate_phase_chain_start(whose_turn, to_return, select);
            break;
        }

        case GAM_PHS_PRE_CHAIN : {
            this->communicate_phase_pre(to_return, select, move_to);
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
    strikes = this->get_strike_to(selection, false);
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

void gam_board_logic::communicate_phase_pre(common_board_interface& to_eidt, const common_position& at_pos, const common_position& to_pos)
{
    common_position possible_enemy;

    if(at_pos.on_height < to_pos.on_height) {
        possible_enemy.on_height = to_pos.on_height - 1;
    } else {
        possible_enemy.on_height = to_pos.on_height + 1;
    }

    if(at_pos.on_width < to_pos.on_width) {
        possible_enemy.on_width = to_pos.on_width - 1;
    } else {
        possible_enemy.on_width = to_pos.on_width + 1;
    }

    if(possible_enemy.on_height == at_pos.on_height && possible_enemy.on_width == at_pos.on_width) {
        possible_enemy.on_height = -1;
        possible_enemy.on_width = -1;
    } else if(this->find_piece_by_pos(possible_enemy) == -1) {
        possible_enemy.on_height = -1;
        possible_enemy.on_width = -1;
    }

    for(int on_hght = 0; on_hght < this->board_height; on_hght++) {
        for(int on_wdth = 0; on_wdth < this->board_width; on_wdth++) {
            if(on_hght % 2 == on_wdth % 2) {
                common_position our_local;
                our_local.on_height = on_hght;
                our_local.on_width = on_wdth;

                this->communicate_handle_pre(to_eidt, our_local, at_pos, to_pos, possible_enemy);
            }
        }
    }
}

void gam_board_logic::communicate_handle_pre(common_board_interface& to_edit, const common_position& local_pos, const common_position& at_pos, const common_position& to_pos, const common_position& posb_strike)
{
    int work_idx;
    work_idx = this->find_piece_by_pos(local_pos);

    if(work_idx == -1) {
        common_board_playable temp;
        temp.position.on_height = local_pos.on_height;
        temp.position.on_width = local_pos.on_width;
        temp.current_state = CMN_STAT_NEITHER;

        if(local_pos.on_height == to_pos.on_height && local_pos.on_width == to_pos.on_width) {
            temp.current_state = CMN_STAT_SELECTED;
        }

        to_edit.playable.push_back(temp);
        return;
    }

    common_board_pawns temp;
    temp.type = this->our_pieces[work_idx].give_my_type();
    temp.position.on_height = local_pos.on_height;
    temp.position.on_width = local_pos.on_width;
    temp.current_state = CMN_STAT_NEITHER;

    if(at_pos.on_height == local_pos.on_height && at_pos.on_width == local_pos.on_width) {
        temp.current_state = CMN_STAT_SELECTED;
    }

    if(posb_strike.on_height == local_pos.on_height && posb_strike.on_width == local_pos.on_width) {
        temp.current_state = CMN_STAT_STRIKABLE;
    }

    to_edit.pawns.push_back(temp);
}

void gam_board_logic::communicate_phase_chain_start(const bool& whose_turn, common_board_interface& to_edit, const common_position& selection)
{
    std::vector<common_position> end_points, enemy_points;
    end_points = this->get_strike_to(selection, true);
    enemy_points = this->compose_to_strike(selection, end_points);

    for(int on_hght = 0; on_hght < this->board_height; on_hght++) {
        for(int on_wdth = 0; on_wdth < this->board_width; on_wdth++) {
            if(on_hght % 2 == on_wdth % 2) {
                common_position our_local;
                our_local.on_height = on_hght;
                our_local.on_width = on_wdth;

                this->communicate_handle_chain_start(to_edit, our_local, selection, end_points, enemy_points);
            }
        }
    }
}

void gam_board_logic::communicate_handle_chain_start(common_board_interface& to_edit, const common_position& local_pos, const common_position& at_pos, const std::vector<common_position>& ends, const std::vector<common_position>& enemies)
{
    int work_idx;
    work_idx = this->find_piece_by_pos(local_pos);

    if(work_idx == -1) {
        common_board_playable temp;
        temp.position.on_height = local_pos.on_height;
        temp.position.on_width = local_pos.on_width;
        temp.current_state = CMN_STAT_NEITHER;

        for(int i = 0; i < ends.size(); i++) {
            if(local_pos.on_height == ends[i].on_height && local_pos.on_width == ends[i].on_width) {
                temp.current_state = CMN_STAT_SELECTABLE;
                break;
            }
        }

        to_edit.playable.push_back(temp);
        return;
    }

    common_board_pawns temp;
    temp.position.on_height = local_pos.on_height;
    temp.position.on_width = local_pos.on_width;
    temp.type = this->our_pieces[work_idx].give_my_type();
    temp.current_state = CMN_STAT_NEITHER;

    if(at_pos.on_height == local_pos.on_height && at_pos.on_width == local_pos.on_width) {
        temp.current_state = CMN_STAT_SELECTED;
    }

    for(int i = 0; i < enemies.size(); i++) {
        if(local_pos.on_height == enemies[i].on_height && local_pos.on_width == enemies[i].on_width) {
            temp.current_state = CMN_STAT_STRIKABLE;
            break;
        }
    }

    to_edit.pawns.push_back(temp);
}