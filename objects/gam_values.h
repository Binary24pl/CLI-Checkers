#ifndef GAM
#define GAM

#define GAM_LIGHT true
#define GAM_DARK false

enum gam_pawn_rep {
    GAM_REP_UNPLAYABLE,
    GAM_REP_EMPTY,
    GAM_REP_LIGHT_PAWN,
    GAM_REP_LIGHT_JOKEY,
    GAM_REP_DARK_PAWN,
    GAM_REP_DARK_JOKEY
};

enum gam_draw {
    GAM_DRW_SLCTB,
    GAM_DRW_SLCTD,
    GAM_DRW_TCNFRM
};

struct gam_piece_move {
    std::vector<common_position> possible_points;
    std::vector<common_position> strike_positions;
    std::vector<bool> possible_next_strike;
};

class gam_board
{
public:
    gam_board(int height, int width) {
        board_pos = nullptr;
        
        this->board_height = height;
        this->board_width = width;
        
        if(height % 2 != 0 || width % 2 != 0) {
            this->board_height = -1;
            this->board_width = -1;
        }
    };

    ~gam_board() {
        if(this->board_pos != nullptr) {
            for(int rem = 0; rem < this->board_height; rem++) {
                delete[] this->board_pos[rem];
            }

            delete[] this->board_pos;
        }
    }

    void init();

    common_board_interface communicate_draw(const bool& whose_turn, const gam_draw& what_draw, const common_position& pos, const common_position& move_to, const common_position& strike_at);

    //think lounge
    bool think_movable(const bool& whose_turn, const common_position& at_pos);

    bool think_options(const bool& whose_turn, const common_position& at_pos, const common_position& to_pos);

    bool think_strike(const bool& whose_turn, const common_position& at_pos, const common_position& to_pos, const common_position& strike_at);

    bool think_restrike(const bool& whose_turn, const common_position& at_pos, const common_position& to_pos, const common_position& strike_at);

    bool think_check_win(const bool& after_who);

private:
    //selectable lounge
    void give_movable(const bool& whose_turn, std::vector<common_position>& positions);

    template<gam_pawn_rep pawn, gam_pawn_rep jokey>
    bool check_movable(const bool& whose_turn, const common_position& our_pos);

    template<int fronts, int sides, gam_pawn_rep strikable_pawn, gam_pawn_rep stikable_jokey>
    bool check_sideways(const common_position our_pos);

    void handle_position_slct(int on_hght, int on_wdth, common_board_interface& interface, const std::vector<common_position>& selectable);

    //selected lounge

    void give_options(const bool& whose_turn, gam_piece_move& our_opts, const common_position& our_pos, const bool& unlimited);

    template<int fronts, int sides, gam_pawn_rep strikable_pawn, gam_pawn_rep strikable_jokey>
    void sideway_options(gam_piece_move& our_opts, const common_position& our_pos, const bool& unlimited);

    template<int fronts, int sides, gam_pawn_rep strikable_pawn, gam_pawn_rep strikable_jokey>
    void strike_options(gam_piece_move& our_opts, const common_position& our_pos);

    void handle_position_sltd(int on_hght, int on_wdth, common_board_interface& interface, const gam_piece_move& options, const common_position& selected);

    // to confirm lounge

    void handle_position_cnfm(int on_hght, int on_wdth, const bool& is_strike, common_board_interface& interface, const common_position& origin, const common_position& destination, const common_position& strike_through);

    int board_height, board_width;
    gam_pawn_rep** board_pos;
};

#endif