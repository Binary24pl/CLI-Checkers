void gam_board_piece::init(const common_position& pos, const bool& side)
{
    if(this->is_set) return; //we dont reiniy

    if(this->board_height <= 0 || this->board_width <=0) return;

    if(this->util_is_pos_valid(pos) == false) return;

    this->origin.on_height = pos.on_height;
    this->origin.on_width = pos.on_width;
    this->side = side;

    this->set_pawn_directions();

    this->is_set = true;
}

void gam_board_piece::set_pawn_directions()
{
    this->directional_functions.reserve(GAM_DRCT_COUNT);

    if(this->side) {
        this->directional_functions[GAM_DRCT_FRONT_LEFT] = &gam_board_piece::util_give_two_steps<1, -1>;
        this->directional_functions[GAM_DRCT_FRONT_RIGHT] = &gam_board_piece::util_give_two_steps<1, 1>;
        this->directional_functions[GAM_DRCT_BACK_LEFT] = &gam_board_piece::util_give_two_steps<-1, -1>;
        this->directional_functions[GAM_DRCT_BACK_RIGHT] = &gam_board_piece::util_give_two_steps<-1, 1>;
    } else {
        this->directional_functions[GAM_DRCT_FRONT_LEFT] = &gam_board_piece::util_give_two_steps<-1, 1>;
        this->directional_functions[GAM_DRCT_FRONT_RIGHT] = &gam_board_piece::util_give_two_steps<-1, -1>;
        this->directional_functions[GAM_DRCT_BACK_LEFT] = &gam_board_piece::util_give_two_steps<1, 1>;
        this->directional_functions[GAM_DRCT_BACK_RIGHT] = &gam_board_piece::util_give_two_steps<1, -1>;
    }
}

bool gam_board_piece::util_is_pos_valid(const common_position& pos)
{
    if(pos.on_height < 0 || pos.on_height >= this->board_height) return false;

    if(pos.on_width < 0 || pos.on_height >= this->board_width) return false;

    return true;
}

template<int fronts, int sides>
void gam_board_piece::util_give_two_steps(common_position& first_step, common_position& second_step)
{
    first_step.on_height = origin.on_height + fronts;
    first_step.on_width = origin.on_width + side;

    second_step.on_height = origin.on_height + (fronts * 2);
    second_step.on_width = origin.on_width + (sides * 2);
}