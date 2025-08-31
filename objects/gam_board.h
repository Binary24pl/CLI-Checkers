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
            //std::string debug = "unplayable";

            this->board_pos[on_hght][on_wdth] = GAM_REP_UNPLAYABLE;

            if(on_hght % 2 == on_wdth % 2) {
                if(on_hght < 2) {
                    this->board_pos[on_hght][on_wdth] = GAM_REP_DARK_PAWN;
                    //debug = "dark";
                } else if(on_hght >= (this->board_height - 2)) {
                    this->board_pos[on_hght][on_wdth] = GAM_REP_LIGHT_PAWN;
                    //debug = "light";
                } else {
                    this->board_pos[on_hght][on_wdth] = GAM_REP_EMPTY;
                    //debug = "empty";
                }
            }

            //std::cout << on_hght << " : " << on_wdth << " - " << debug << std::endl;
        }
    }
}

void gam_board::give_movable(const bool& whose_turn, std::vector<common_position>& positions)
{
    if(positions.size() != 0) positions.clear();

    bool (gam_board::*ourteam_check)(const bool&, const common_position&) = nullptr;

    if(whose_turn) {
        ourteam_check = &gam_board::check_movable<GAM_REP_LIGHT_PAWN, GAM_REP_LIGHT_JOKEY>;
    } else {
        ourteam_check = &gam_board::check_movable<GAM_REP_DARK_PAWN, GAM_REP_DARK_JOKEY>;
    }

    for(int on_hght = 0; on_hght < this->board_height; on_hght++) {
        for(int on_wdth = 0; on_wdth < this->board_width; on_wdth++) {
            common_position temp;
            
            temp.on_height = on_hght;
            temp.on_width = on_wdth;

            if((this->*ourteam_check)(whose_turn, temp)) {
                std::cout << temp.on_height << " : " << temp.on_width << " - is moveable" << std::endl;
            }
        }
    }
}

template<gam_pawn_rep pawn, gam_pawn_rep jokey>
bool gam_board::check_movable(const bool& whose_turn, const common_position& our_pos)
{
    if(our_pos.on_height < 0 || our_pos.on_height >= this->board_height || our_pos.on_width < 0 || our_pos.on_width >= this->board_width) return false;

    gam_pawn_rep our_pawn = this->board_pos[our_pos.on_height][our_pos.on_width];

    bool (gam_board::*up_left)(const common_position) = nullptr;
    bool (gam_board::*up_right)(const common_position) = nullptr;
    bool (gam_board::*down_left)(const common_position) = nullptr;
    bool (gam_board::*down_right)(const common_position) = nullptr;

    if(whose_turn) {
        up_left = &gam_board::check_sideways<-1, -1, GAM_REP_DARK_PAWN, GAM_REP_DARK_JOKEY>;
        up_right = &gam_board::check_sideways<-1, 1, GAM_REP_DARK_PAWN, GAM_REP_DARK_JOKEY>;
        down_left = &gam_board::check_sideways<1, -1, GAM_REP_LIGHT_PAWN, GAM_REP_LIGHT_JOKEY>;
        down_right = &gam_board::check_sideways<1, 1, GAM_REP_LIGHT_PAWN, GAM_REP_LIGHT_JOKEY>;
    } else {
        up_left = &gam_board::check_sideways<-1, -1, GAM_REP_LIGHT_PAWN, GAM_REP_LIGHT_JOKEY>;
        up_right = &gam_board::check_sideways<-1, 1, GAM_REP_LIGHT_PAWN, GAM_REP_LIGHT_JOKEY>;
        down_left = &gam_board::check_sideways<1, -1, GAM_REP_DARK_PAWN, GAM_REP_DARK_JOKEY>;
        down_right = &gam_board::check_sideways<1, 1, GAM_REP_DARK_PAWN, GAM_REP_DARK_JOKEY>;
    }

    if(our_pawn == pawn || our_pawn == jokey) {
        //std::cout << our_pos.on_height << " : " << our_pos.on_width << " - board piece" << std::endl;

        if(our_pawn == pawn) {
            if(whose_turn) {
                return (this->*up_left)(our_pos) || (this->*up_right)(our_pos);
            } else {
                return (this->*down_left)(our_pos) || (this->*down_right)(our_pos);
            }
        } else {
            return (this->*up_left)(our_pos) || (this->*up_right)(our_pos) || (this->*down_left)(our_pos) || (this->*down_right)(our_pos);
        }
    }


    return false;
}

template<int fronts, int sides, gam_pawn_rep strikable_pawn, gam_pawn_rep stikable_jokey>
bool gam_board::check_sideways(const common_position our_pos)
{
    //std::cout << "checking for fronts of: " << fronts << " and sides of : " << sides << ". ";

    common_position step_one, step_two;

    step_one.on_height = our_pos.on_height + fronts;
    step_one.on_width = our_pos.on_width + sides;

    step_two.on_height = our_pos.on_height + (fronts * 2);
    step_two.on_width = our_pos.on_width + (sides * 2);

    int possible_steps = 0;

    if(step_one.on_height >= 0 && step_one.on_width >= 0 && step_one.on_height < this->board_height && step_one.on_width < this->board_width) {
        possible_steps += 1;

        if(step_two.on_height >= 0 && step_two.on_width >= 0 && step_two.on_height < this->board_height && step_two.on_width < this->board_width) {
            possible_steps += 1;
        }
    }

    //std::cout << "With " << possible_steps << " possible steps" << std::endl;

    if(possible_steps == 0) return false;

    if(this->board_pos[step_one.on_height][step_one.on_width] == GAM_REP_EMPTY) return true;

    if(possible_steps == 1) return false;

    if(this->board_pos[step_one.on_height][step_one.on_width] == strikable_pawn || this->board_pos[step_one.on_height][step_one.on_width] == stikable_jokey) {
        if(this->board_pos[step_two.on_height][step_two.on_width] == GAM_REP_EMPTY) return true;
    }

    return false;
}