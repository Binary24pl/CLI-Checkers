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
                    std::cout << "Dark on: " <<  on_hght << " <:> " << on_wdth << std::endl;
                } else if(on_hght >= (this->board_height - 2)) {
                    gam_board_piece temp(10, 10);
                    temp.init(on_pos, GAM_LIGHT);

                    this->our_pieces.push_back(temp);
                    std::cout << "Light on: " <<  on_hght << " <:> " << on_wdth << std::endl;
                }
            }
        }
    }
}

common_board_interface gam_board_logic::communicate_draw()
{
    common_board_interface to_return;

    std::vector<int> pieces_idxs;
    std::vector<common_position> pieces_pos;

    this->prep_vectors(pieces_idxs, pieces_pos);

    for(int on_hght = 0; on_hght < this->board_height; on_hght++) {
        for(int on_wdth = 0; on_wdth < this->board_width; on_wdth++) {
            if(on_hght % 2 == on_wdth % 2) {
                this->prep_pos(pieces_idxs, pieces_pos, to_return, on_hght, on_wdth);
            }
        }
    }

    return to_return;
}

int gam_board_logic::find_piece_by_pos(const common_position& pos)
{
    for(int i = 0; i < this->our_pieces.size(); i++) {
        if(this->our_pieces[i].give_am_i_on_coords(pos)) return i;
    }

    return -1;
}

void gam_board_logic::prep_vectors(std::vector<int>& idxs, std::vector<common_position>& poses)
{
    for(int on_hght = 0; on_hght < this->board_height; on_hght++) {
        for(int on_wdth = 0; on_wdth < this->board_width; on_wdth++) {
            common_position our_pos;

            our_pos.on_height = on_hght;
            our_pos.on_width = on_wdth;

            int possible_idx = this->find_piece_by_pos(our_pos);

            if(possible_idx > -1) {
                idxs.push_back(possible_idx);
                poses.push_back(our_pos);
            }
        }
    }
}

void gam_board_logic::prep_pos(const std::vector<int>& idxs, const std::vector<common_position>& poses, common_board_interface& interface, int on_hght, int on_wdth)
{
    bool is_empty = true;
    common_position our_pos;

    our_pos.on_height = on_hght;
    our_pos.on_width = on_wdth;

    int fake_idx = -1;

    for(int i = 0; i < poses.size(); i++) {
        if(poses[i].on_height == our_pos.on_height && poses[i].on_width == our_pos.on_width) {
            fake_idx = i;
            break;
        }
    }

    if(fake_idx != -1) is_empty = false;

    if(is_empty) {
        common_board_playable temp;

        temp.position = our_pos;
        temp.current_state = CMN_STAT_NEITHER;
        
        interface.playable.push_back(temp);
        return;
    }

    common_board_pawns temp;

    temp.type = this->our_pieces[idxs[fake_idx]].give_my_type();
    temp.position = our_pos;
    temp.current_state = CMN_STAT_NEITHER;

    interface.pawns.push_back(temp);
}