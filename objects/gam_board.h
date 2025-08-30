void gam_board::init()
{
    if(this->board_height <= 0 || this->board_width <= 0) {
        return;
    }

    this->board_pos = new gam_pawn_rep*[this->board_height];
    for(int row = 0; row < this->board_height; row++) {
        this->board_pos[row] = new gam_pawn_rep[this->board_width];
    }

    for(int on_hght = 0; on_hght < this->board_height; on_hght++) {
        for(int on_wdth = 0; on_wdth < this->board_width; on_wdth++) {
            this->board_pos[on_hght][on_hght] = GAM_REP_UNPLAYABLE;

            if(on_hght % 2 == on_wdth % 2) {
                if(on_hght < 2) {
                    this->board_pos[on_hght][on_wdth] = GAM_REP_LIGHT_PAWN;
                } else if(on_hght >= (this->board_height - 2)) {
                    this->board_pos[on_hght][on_wdth] = GAM_REP_DARK_PAWN;
                } else {
                    this->board_pos[on_hght][on_wdth] = GAM_REP_EMPTY;
                }
            }
        }
    }
}

void gam_board::give_movable(const bool& whose_turn, std::vector<common_position>& positions)
{
    if(positions.size() != 0) return;
    
    bool (gam_board::*is_pawn)(gam_pawn_rep&) = nullptr;
    bool (gam_board::*is_jokey)(gam_pawn_rep&) = nullptr;
    int direction = 0;

    if(whose_turn) {
        is_pawn = &gam_board::find_me<GAM_REP_LIGHT_PAWN>;
        is_jokey = &gam_board::find_me<GAM_REP_LIGHT_JOKEY>;
        direction = -1;
    } else {
        is_pawn = &gam_board::find_me<GAM_REP_DARK_PAWN>;
        is_jokey = &gam_board::find_me<GAM_REP_DARK_JOKEY>;
        direction = 1;
    }

    for(int on_hght = 0; on_hght < this->board_height; on_hght++) {
        for(int on_wdth = 0; on_wdth < this->board_width; on_wdth++) {
            common_position current_pos;
            current_pos.on_height = on_hght;
            current_pos.on_width = on_wdth;

            if((this->*is_pawn)(this->board_pos[on_hght][on_wdth])) {
                if(this->is_movable(whose_turn, direction, current_pos)) {
                    std::cout << on_hght << " : " << on_wdth << std::endl;
                }
            } else if((this->*is_jokey)(this->board_pos[on_hght][on_wdth])) {
                if(this->is_movable(whose_turn, 0, current_pos)) {
                    std::cout << on_hght << " : " << on_wdth << std::endl;
                }
            }
        }
    }
}

template<gam_pawn_rep lookup>
bool gam_board::find_me(gam_pawn_rep& compared)
{
    return compared == lookup;
}

bool gam_board::is_movable(const bool& whose_turn, const int& directions, const common_position& current_pos)
{
    if(current_pos.on_height < 0 || current_pos.on_width < 0 || current_pos.on_height >= this->board_height || current_pos.on_width >= this->board_width) return false;

    bool unlimited = false;

    if(directions == 0) unlimited = true;

    bool (gam_board::*direct_check_up_left)(const common_position& current_pos) = nullptr;
    bool (gam_board::*direct_check_up_right)(const common_position& current_pos) = nullptr;
    bool (gam_board::*direct_check_down_left)(const common_position& current_pos) = nullptr;
    bool (gam_board::*direct_check_down_right)(const common_position& current_pos) = nullptr;

    if(whose_turn) {
        direct_check_up_left = &gam_board::side_way_check<-1, -1, GAM_REP_DARK_PAWN, GAM_REP_DARK_JOKEY>;
        
        direct_check_up_right = &gam_board::side_way_check<-1, 1, GAM_REP_DARK_PAWN, GAM_REP_DARK_JOKEY>;

        direct_check_up_left = &gam_board::side_way_check<1, -1, GAM_REP_DARK_PAWN, GAM_REP_DARK_JOKEY>;
        
        direct_check_up_right = &gam_board::side_way_check<1, 1, GAM_REP_DARK_PAWN, GAM_REP_DARK_JOKEY>;
    } else {
        direct_check_up_left = &gam_board::side_way_check<-1, -1, GAM_REP_LIGHT_PAWN, GAM_REP_LIGHT_JOKEY>;
        
        direct_check_up_right = &gam_board::side_way_check<-1, 1, GAM_REP_LIGHT_PAWN, GAM_REP_LIGHT_JOKEY>;

        direct_check_up_left = &gam_board::side_way_check<1, -1, GAM_REP_LIGHT_PAWN, GAM_REP_LIGHT_JOKEY>;
        
        direct_check_up_right = &gam_board::side_way_check<1, 1, GAM_REP_LIGHT_PAWN, GAM_REP_LIGHT_JOKEY>;
    }

    if(unlimited) {
        return (this->*direct_check_up_left)(current_pos) || (this->*direct_check_up_right)(current_pos) || (this->*direct_check_down_left)(current_pos) || (this->*direct_check_down_right)(current_pos);
    } else {
        if(directions > 0) {
            return (this->*direct_check_down_left)(current_pos) || (this->*direct_check_down_right)(current_pos);
        } else {
            return (this->*direct_check_up_left)(current_pos) || (this->*direct_check_up_right)(current_pos);
        }
    }


    return false;
}

template<int fronts, int sides, gam_pawn_rep strikeable_pawn, gam_pawn_rep strikable_jokey>
bool gam_board::side_way_check(const common_position& current_pos)
{
    int possible_depth = 0;

    common_position step;
    step.on_height = current_pos.on_height + fronts;
    step.on_width = current_pos.on_width + sides;

    if(step.on_height >= 0 && step.on_height < this->board_height && step.on_width >= 0 && step.on_width < this->board_width) {
        possible_depth += 1;

        step.on_height += fronts;
        step.on_width += sides;

        if(step.on_height >= 0 && step.on_height < this->board_height && step.on_width >= 0 && step.on_width < this->board_width) {
            possible_depth += 1;
        }
    }

    if(possible_depth != 0) {
        if(this->board_pos[current_pos.on_height + fronts][current_pos.on_width + sides] == GAM_REP_EMPTY) return true;

        if(possible_depth == 2 && (this->board_pos[current_pos.on_height + fronts][current_pos.on_width + sides] == strikeable_pawn || this->board_pos[current_pos.on_height + fronts][current_pos.on_width + sides] == strikable_jokey) && this->board_pos[current_pos.on_height + (2 * fronts)][current_pos.on_width + (2 * sides)] == GAM_REP_EMPTY) return true;
    }

    return false;
}