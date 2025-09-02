template<gam_pawn_rep strikable_pawn, gam_pawn_rep strikable_jokey>
void gam_board::give_chain_strike(const common_position& our_pos, std::vector<common_position>& strikes, std::vector<common_position>& end_points)
{
    if(strikes.size() != 0) strikes.clear();
    if(end_points.size() != 0) end_points.clear();

    void (gam_board::*up_left)(const common_position&, std::vector<common_position>&, std::vector<common_position>&) = gam_board::sideway_chain<-1, -1, strikable_pawn, strikable_jokey>;
    void (gam_board::*up_right)(const common_position&, std::vector<common_position>&, std::vector<common_position>&) = gam_board::sideway_chain<-1, 1, strikable_pawn, strikable_jokey>;
    void (gam_board::*down_left)(const common_position&, std::vector<common_position>&, std::vector<common_position>&) = gam_board::sideway_chain<1, -1, strikable_pawn, strikable_jokey>;
    void (gam_board::*down_right)(const common_position&, std::vector<common_position>&, std::vector<common_position>&) = gam_board::sideway_chain<1, 1, strikable_pawn, strikable_jokey>;

    (this->*up_left)(our_pos, strikes, end_points);
    (this->*up_right)(our_pos, strikes, end_points);
    (this->*down_left)(our_pos, strikes, end_points);
    (this->*down_right)(our_pos, strikes, end_points);
}

template<int fronts, int sides, gam_pawn_rep strikable_pawn, gam_pawn_rep strikable_jokey>
void gam_board::sideway_chain(const common_position& our_pos, std::vector<common_position>& strikes, std::vector<common_position>& end_points)
{
    common_position possible_enemy, strike_destination;
    
    possible_enemy.on_height = our_pos.on_height + (fronts * 1);
    possible_enemy.on_width = our_pos.on_width + (sides * 1);

    strike_destination.on_height = our_pos.on_height + (fronts * 2);
    strike_destination.on_width = our_pos.on_width + (sides * 2);

    if(possible_enemy.on_height < 0 || possible_enemy.on_width < 0 || possible_enemy.on_height >= this->board_height || possible_enemy.on_width >= this->board_width) return;

    if(this->board_pos[possible_enemy.on_height][possible_enemy.on_width] != strikable_pawn && this->board_pos[possible_enemy.on_height][possible_enemy.on_width] != strikable_jokey) return;

    if(strike_destination.on_height < 0 || strike_destination.on_width < 0 || strike_destination.on_height >= this->board_height || strike_destination.on_width >= board_width) return;

    if(this->board_pos[strike_destination.on_height][strike_destination.on_width] != GAM_REP_EMPTY) return;

    strikes.push_back(possible_enemy);
    end_points.push_back(strike_destination);
}