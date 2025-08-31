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

    void give_movable(const bool& whose_turn, std::vector<common_position>& positions);

    template<gam_pawn_rep pawn, gam_pawn_rep jokey>
    bool check_movable(const bool& whose_turn, const common_position& our_pos);

    template<int fronts, int sides, gam_pawn_rep strikable_pawn, gam_pawn_rep stikable_jokey>
    bool check_sideways(const common_position our_pos);
private:
    int board_height, board_width;
    gam_pawn_rep** board_pos;
};

#endif