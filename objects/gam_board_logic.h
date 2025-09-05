void gam_board_logic::init()
{
    if(this->board_height <= 0 || this->board_width <= 0) return;

    for(int on_hght = 0; on_hght < this->board_height; on_hght++) {
        for(int on_wdth = 0; on_wdth < this->board_width; on_wdth++) {
            if(on_hght % 2 == on_wdth % 2) {
                common_position on_pos;
                on_pos.on_height = on_hght;
                on_pos.on_width = on_wdth;

                if(on_hght == 7) {
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

void gam_board_logic::find_sideway_coords(std::vector<std::vector<common_position>>& container, const common_position& pos, int& our_index)
{
    const int idx = this->find_piece_by_pos(pos);
    our_index = idx;

    if(idx == -1) return;

    container.clear();

    container = this->our_pieces[idx].give_possible_coords();
}

std::vector<gam_tile_rep> gam_board_logic::find_sideway_rep(const std::vector<common_position> sideway_cont)
{
    std::vector<gam_tile_rep> to_return;

    for(int tile = 0; tile <sideway_cont.size(); tile++) {
        const int idx = this->find_piece_by_pos(sideway_cont[tile]);

        if(idx == -1) {
            to_return.push_back(GAM_TLE_EMPTY);
        } else {
            const common_board_pawns_types our_type = this->our_pieces[idx].give_my_type();

            if(our_type == CMN_PAWN_LIGHT || our_type == CMN_JOKEY_LIGHT) {
                to_return.push_back(GAM_TLE_LIGHT);
            } else if(our_type == CMN_PAWN_DARK || our_type == CMN_JOKEY_DARK) {
                to_return.push_back(GAM_TLE_DARK);
            }
        }
    }

    return to_return;
}

//how much can we shift
int gam_board_logic::count_move(const common_position& pos, const gam_relative_directions& direction)
{
    int to_return = 0;

    int idx;
    std::vector<std::vector<common_position>> sides;

    this->find_sideway_coords(sides, pos, idx);

    if(idx == -1) return -1;

    std::vector<gam_tile_rep> tiles;
    tiles = this->find_sideway_rep(sides[direction]);

    std::vector<gam_mov_results> moves;

    bool limits = this->our_pieces[idx].pass_jokey();
    moves = this->our_pieces[idx].give_mov_results(tiles, limits);

    for(int i = 0; i < moves.size(); i++) {
        if(moves[i] == GAM_MOV_SHIFT) {
            to_return += 1;
        } else {
            break;
        }
    }
    

    return to_return;
}

//idx of a strike
int gam_board_logic::count_strike(const common_position& pos, const gam_relative_directions& direction, const bool& is_restrike_check)
{
    int idx;
    std::vector<std::vector<common_position>> sides;

    this->find_sideway_coords(sides, pos, idx);

    if(idx == -1) return -1;

    bool limitations = false;
    if(is_restrike_check) {
        limitations = true;
    } else {
        if(this->our_pieces[idx].pass_jokey() == false) {
            limitations = true;
        }
    }

    std::vector<gam_tile_rep> tiles;
    tiles = this->find_sideway_rep(sides[direction]);

    std::vector<gam_mov_results> moves;

    moves = this->our_pieces[idx].give_mov_results(tiles, limitations);

    for(int i = 0; i < moves.size(); i++) {
        if(moves[i] == GAM_MOV_STRIKE) return i;
    }
    
    return -1;
}