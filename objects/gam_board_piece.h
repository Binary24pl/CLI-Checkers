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