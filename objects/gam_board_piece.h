void gam_board_piece::init(const common_position& pos, const bool& side)
{
    if(this->is_set) return; //we dont reiniy

    if(this->board_height <= 0 || this->board_width <=0) return;

    if(this->util_is_pos_valid(pos) == false) return;

    this->origin.on_height = pos.on_height;
    this->origin.on_width = pos.on_width;
    this->whose_side = side;
    this->is_jokey = false;

    this->is_set = true;
}

bool gam_board_piece::give_am_i_on_coords(const common_position& pos)
{
    if(pos.on_height == this->origin.on_height && pos.on_width == this->origin.on_width) 
        return true;
    
    return false;
}

std::vector<std::vector<common_position>> gam_board_piece::give_possible_coords()
{
    std::vector<std::vector<common_position>> to_return;

    to_return.push_back(this->give_sideway_coords<-1, -1>());
    to_return.push_back(this->give_sideway_coords<-1, 1>());
    to_return.push_back(this->give_sideway_coords<1, -1>());
    to_return.push_back(this->give_sideway_coords<1, 1>());

    return to_return;
}

template<int fronts, int sides>
std::vector<common_position> gam_board_piece::give_sideway_coords()
{
    std::vector<common_position> to_return;

    common_position our_sway;
    our_sway.on_height = this->origin.on_height + fronts;
    our_sway.on_width = this->origin.on_width + sides;

    while(this->util_is_pos_valid(our_sway)) {
        to_return.push_back(our_sway);
        our_sway.on_height += fronts;
        our_sway.on_width += sides;
    }

    return to_return;
}

std::vector<gam_mov_results> gam_board_piece::give_mov_results(const std::vector<gam_tile_rep>& container, const bool& unlimited = false)
{
    std::vector<gam_mov_results> to_return;

    int is_in_combat = 0;

    for(int i = 0; i < container.size(); i++) {
        if(unlimited == false && i >= 1) {
            to_return.push_back(GAM_MOV_RESTRICTED);
        } else {
            this->give_handle_mov_res_pos(container, i, is_in_combat, to_return);
        }
    }

    return to_return;
}

void gam_board_piece::give_handle_mov_res_pos(const std::vector<gam_tile_rep>& container, const int& pos, int& combat_scenario, std::vector<gam_mov_results>& to_push)
{
    if(combat_scenario == -1) {
        to_push.push_back(GAM_MOV_IMPOSSIBLE);
        return;
    }

    if(combat_scenario == 1) {
        if(container[pos] == GAM_TLE_EMPTY) {
            to_push.push_back(GAM_MOV_STRIKE);
        } else {
            to_push.push_back(GAM_MOV_IMPOSSIBLE);
        }

        combat_scenario = -1;
        return;
    }

    if(container[pos] == GAM_TLE_EMPTY) {
        to_push.push_back(GAM_MOV_SHIFT);
        return;
    }

    gam_tile_rep enemy;
    if(this->whose_side) {
        enemy = GAM_TLE_DARK;
    } else {
        enemy = GAM_TLE_LIGHT;
    }

    if(container[pos] == enemy) {
        combat_scenario = 1;
    } else {
        combat_scenario = -1;
    }

    to_push.push_back(GAM_MOV_IMPOSSIBLE);
}

common_board_pawns_types gam_board_piece::give_my_type()
{
    common_board_pawns_types to_return;

    if(this->whose_side) {
        to_return = CMN_PAWN_LIGHT;
        if(this->is_jokey) to_return = CMN_JOKEY_LIGHT;
    } else {
        to_return = CMN_PAWN_DARK;
        if(this->is_jokey) to_return = CMN_JOKEY_DARK;
    }

    return to_return;
}

void gam_board_piece::set_to_jokey()
{
    if(this->is_jokey) return;
    if(this->is_set == false) return;

    if(this->whose_side) {
        if(this->origin.on_height == 0) {
            this->is_jokey = true;
        }
    } else {
        if(this->origin.on_height == (this->board_height - 1)) {
            this->is_jokey = true;
        }
    }
}

bool gam_board_piece::util_is_pos_valid(const common_position& pos)
{
    if(pos.on_height < 0 || pos.on_height >= this->board_height) return false;

    if(pos.on_width < 0 || pos.on_height >= this->board_width) return false;

    return true;
}