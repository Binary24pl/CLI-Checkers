#ifndef GAM
#define GAM

#define GAM_LIGHT true
#define GAM_DARK false

class gam_board_piece
{
public:
    gam_board_piece(int height, int width) {};

    ~gam_board_piece() {};

private:
    int board_height;
    int board_width;
};

#endif