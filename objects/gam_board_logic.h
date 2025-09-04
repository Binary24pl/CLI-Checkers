void gam_board_logic::init()
{
    if(this->board_height <= 0 || this->board_width <= 0) return;

    for(int on_hght = 0; on_hght < this->board_height; on_hght++) {
        for(int on_wdth = 0; on_wdth < this->board_width; on_wdth++) {
            if(on_hght % 2 == on_wdth % 2) {
                common_position on_pos;
                on_pos.on_height = on_hght;
                on_pos.on_width = on_wdth;

                if(on_hght < 2) {
                    gam_board_piece temp(10, 10);
                    temp.init(on_pos, GAM_DARK);

                    this->our_pieces.push_back(temp);
                    //std::cout << "Dark on: " <<  on_hght << " <:> " << on_wdth << std::endl;
                } else if(on_hght >= (this->board_height - 2)) {
                    gam_board_piece temp(10, 10);
                    temp.init(on_pos, GAM_LIGHT);

                    this->our_pieces.push_back(temp);
                    //std::cout << "Light on: " <<  on_hght << " <:> " << on_wdth << std::endl;
                }
            }
        }
    }
}

int gam_board_logic::find_piece_by_pos(const common_position& pos)
{
    for(int i = 0; i < this->our_pieces.size(); i++) {
        if(this->our_pieces[i].give_am_i_on_coords(pos)) return i;
    }

    return -1;
}