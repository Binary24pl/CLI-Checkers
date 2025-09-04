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