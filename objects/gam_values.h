#ifndef GAM
#define GAM

enum gam_pawn_rep {
    GAM_REP_UNPLAYABLE,
    GAM_REP_EMPTY,
    GAM_REP_LIGHT_PAWN,
    GAM_REP_LIGHT_JOKEY,
    GAM_REP_DARK_PAWN,
    GAM_REP_DARK_JOKEY
};

enum gam_selection_phase {
    GAM_SPH_CAN_SLCT,
    GAM_SPH_CAN_MOVE,
    GAM_SPH_CONFIRM,
    GAM_SPH_CHECK_COMBO
};

#define GAM_TRN_LIGHT true
#define GAM_TRN_DARK false

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

        this->current_phase = GAM_SPH_CAN_SLCT;
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
private:
    int board_height, board_width;
    gam_pawn_rep** board_pos;
    gam_selection_phase current_phase;
};

#endif