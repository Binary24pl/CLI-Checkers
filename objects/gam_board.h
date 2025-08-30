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
            this->board_pos[on_hght][on_wdth] = GAM_REP_UNPLAYABLE;

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
    if(current_pos.on_height < 0 || current_pos.on_height >= this->board_height || current_pos.on_width < 0 | current_pos.on_width >= this->board_width) return false;

    bool (gam_board::*up_left)(const common_position&) = nullptr;
    bool (gam_board::*up_right)(const common_position&) = nullptr;
    bool (gam_board::*down_left)(const common_position&) = nullptr;
    bool (gam_board::*down_right)(const common_position&) = nullptr;

    if(whose_turn) {
        up_left = &gam_board::side_way_check<-1, -1, GAM_REP_DARK_PAWN, GAM_REP_DARK_JOKEY>;
        up_right = &gam_board::side_way_check<-1, 1, GAM_REP_DARK_PAWN, GAM_REP_DARK_JOKEY>;
        down_left = &gam_board::side_way_check<1, -1, GAM_REP_DARK_PAWN, GAM_REP_DARK_JOKEY>;
        down_right = &gam_board::side_way_check<1, 1, GAM_REP_DARK_PAWN, GAM_REP_DARK_JOKEY>;
    } else {
        up_left = &gam_board::side_way_check<-1, -1, GAM_REP_LIGHT_PAWN, GAM_REP_LIGHT_JOKEY>;
        up_right = &gam_board::side_way_check<-1, 1, GAM_REP_LIGHT_PAWN, GAM_REP_LIGHT_JOKEY>;
        down_left = &gam_board::side_way_check<1, -1, GAM_REP_LIGHT_PAWN, GAM_REP_LIGHT_JOKEY>;
        down_right = &gam_board::side_way_check<1, 1, GAM_REP_LIGHT_PAWN, GAM_REP_LIGHT_JOKEY>;
    }

    if(directions > 0) {
        bool results = (this->*down_left)(current_pos) || (this->*down_right)(current_pos);

        return results;
    } else if(directions < 0) {
        bool results = (this->*up_left)(current_pos) || (this->*up_right)(current_pos);

        return results;
    } else {
        bool results = (this->*down_left)(current_pos) || (this->*down_right)(current_pos) || (this->*up_left)(current_pos) || (this->*up_right)(current_pos);

        return results;
    }

    return false;
}

template<int fronts, int sides, gam_pawn_rep strikeable_pawn, gam_pawn_rep strikable_jokey>
bool gam_board::side_way_check(const common_position& current_pos)
{
    int possible_steps = 0;

    std::cout << current_pos.on_height << " : " << current_pos.on_width << " -conf(" << fronts << ", " << sides << "); ";

    std::cout << possible_steps << std::endl;

    return false;
}