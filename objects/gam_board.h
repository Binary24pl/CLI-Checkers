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

common_board_interface gam_board::communicate_draw(const bool& whose_turn, const gam_draw& what_draw, const common_position& pos = {-1 , -1}, const common_position& move_to = {-1 , -1}, const common_position& strike_at = {-1 , -1})
{
    common_board_interface to_return;

    if(what_draw == GAM_DRW_SLCTB) {
        std::vector<common_position> selectable_poses;

        this->give_movable(whose_turn, selectable_poses);

        for(int on_hght = 0; on_hght < this->board_height; on_hght++) {
            for(int on_wdth = 0; on_wdth < this->board_height; on_wdth++) {
                if(this->board_pos[on_hght][on_wdth] != GAM_REP_UNPLAYABLE) this->handle_position_slct(on_hght, on_wdth, to_return, selectable_poses);
            }
        }
    } else if(what_draw == GAM_DRW_SLCTD) {
        if(pos.on_height < 0 || pos.on_width < 0 || pos.on_height >= this->board_height || pos.on_width >= this->board_width) return to_return;

        gam_pawn_rep pawn, jokey;

        if(whose_turn) {
            pawn = GAM_REP_LIGHT_PAWN;
            jokey = GAM_REP_LIGHT_JOKEY;
        } else {
            pawn = GAM_REP_DARK_PAWN;
            jokey = GAM_REP_DARK_JOKEY;
        }

        if(this->board_pos[pos.on_height][pos.on_width] != pawn && this->board_pos[pos.on_height][pos.on_width] != jokey) return to_return;

        gam_piece_move temp;

        bool unlimited = false;

        if(this->board_pos[pos.on_height][pos.on_width] == jokey) unlimited = true;

        this->give_options(whose_turn, temp, pos, unlimited);

        for(int on_hght = 0; on_hght < this->board_height; on_hght++) {
            for(int on_wdth = 0; on_wdth < this->board_height; on_wdth++) {
                if(this->board_pos[on_hght][on_wdth] != GAM_REP_UNPLAYABLE) this->handle_position_sltd(on_hght, on_wdth, to_return, temp, pos);
            }
        }
    } else if(what_draw == GAM_DRW_TCNFRM) {
        if(pos.on_height < 0 || pos.on_width < 0 || pos.on_height >= this->board_height || pos.on_width >= this->board_width) return to_return;

        if(move_to.on_height < 0 || move_to.on_width < 0 || move_to.on_height >= this->board_height || move_to.on_width >= this->board_width) return to_return;

        bool strikable = false;

        if(strike_at.on_height != -1 && strike_at.on_width != -1) {
            if(strike_at.on_height < 0 || strike_at.on_width < 0 || strike_at.on_height >= this->board_height || strike_at.on_width >= this->board_width) return to_return;

            strikable = true;
        }
    }

    return to_return;
}

void gam_board::handle_position_cnfm(int on_hght, int on_wdth, const bool& is_strike, common_board_interface& interface, const common_position& origin, const common_position& destination, const common_position& strike_through)
{
    if(this->board_pos[on_hght][on_wdth] == GAM_REP_EMPTY) {
        common_board_playable temp;
        temp.position.on_height = on_hght;
        temp.position.on_width = on_wdth;
        temp.current_state = CMN_STAT_NEITHER;

        if(on_hght == destination.on_height && on_wdth == destination.on_width) temp.current_state = CMN_STAT_SELECTED;

        interface.playable.push_back(temp);
        return;
    }

    common_board_pawns temp;

    temp.position.on_height = on_hght;
    temp.position.on_width = on_wdth;
    temp.current_state = CMN_STAT_NEITHER;

    switch(this->board_pos[on_hght][on_wdth]) {
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

    if(is_strike && strike_through.on_height == on_hght && strike_through.on_width == on_wdth) {
        temp.current_state = CMN_STAT_STRIKABLE;
    }

    if(origin.on_height == on_hght && origin.on_width == on_wdth) {
        temp.current_state = CMN_STAT_SELECTED;
    }

    interface.pawns.push_back(temp);
}