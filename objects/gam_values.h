#ifndef GAM
#define GAM

#define GAM_LIGHT true
#define GAM_DARK false

enum gam_relative_directions
{
    GAM_DRCT_FRONT_LEFT,
    GAM_DRCT_FRONT_RIGHT,
    GAM_DRCT_BACK_LEFT,
    GAM_DRCT_BACK_RIGHT,
    GAM_DRCT_COUNT
};

enum gam_mov_results
{
    GAM_MOV_RESTRICTED,
    GAM_MOV_SHIFT,
    GAM_MOV_STRIKE,
    GAM_MOV_IMPOSSIBLE
};

class gam_board_piece
{
public:
    gam_board_piece(int height, int width) {
        this->board_height = height;
        this->board_width = width;

        if(height < 0 || width < 0 || height % 2 != 0 || width % 2 != 0) {
            this->board_height = -1;
            this->board_width = -1;
        }

        this->is_set = false;
    };

    ~gam_board_piece() {};

    void init(const common_position& pos, const bool& side);

    std::vector<int> give_possible_directions(bool ignore_restriction);
    bool give_am_i_on_coords(const common_position& pos);
    common_board_pawns_types give_my_type();

    void set_to_jokey();

private:
    int board_height;
    int board_width;

    bool whose_side;
    bool is_jokey;
    bool is_set;

    common_position origin;

    std::vector<void(gam_board_piece::*)(common_position&, common_position&)> directional_functions;

    void set_pawn_directions();

    bool util_is_pos_valid(const common_position& pos);
    template<int fronts, int sides>
    void util_give_two_steps(common_position& first_step, common_position& second_step);
};

#endif