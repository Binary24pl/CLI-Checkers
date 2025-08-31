void gam_board::init()
{
    if(this->board_height <= 0 || this->board_width <= 0) {
        return;
    }

    this->board_pos = new gam_pawn_rep*[this->board_height];
    for(int row = 0; row < this->board_height; row++) {
        this->board_pos[row] = new gam_pawn_rep[this->board_width];
    }

    for(int on_hght = 0; on_hght < this->board_height; on_hght++) {
        for(int on_wdth = 0; on_wdth < this->board_width; on_wdth++) {
            this->board_pos[on_hght][on_wdth] = GAM_REP_UNPLAYABLE;

            if(on_hght % 2 == on_wdth % 2) {
                if(on_hght < 2) {
                    this->board_pos[on_hght][on_wdth] = GAM_REP_DARK_PAWN;
                } else if(on_hght >= (this->board_height - 2)) {
                    this->board_pos[on_hght][on_wdth] = GAM_REP_LIGHT_PAWN;
                } else {
                    this->board_pos[on_hght][on_wdth] = GAM_REP_EMPTY;
                }
            }
        }
    }
}