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

enum gam_tile_rep
{
    GAM_TLE_EMPTY,
    GAM_TLE_DARK,
    GAM_TLE_LIGHT
};

enum gam_round_phase
{
    GAM_PHS_START,
    GAM_PHS_SELECTED,
    GAM_PHS_PRE_MOVE,
    GAM_PHS_POST_MOVE,
    GAM_PHS_CHAIN_START,
    GAM_PHS_PRE_CHAIN,
    GAM_PHS_POST_CHAIN,
    GAM_PHS_FINISHED
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

    bool pass_jokey() {
        return this->is_jokey;
    }

    void init(const common_position& pos, const bool& side);

    bool give_am_i_on_coords(const common_position& pos);
    common_board_pawns_types give_my_type();
    std::vector<std::vector<common_position>> give_possible_coords();
    std::vector<gam_mov_results> give_mov_results(const std::vector<gam_tile_rep>& container, const bool& unlimited);

    void set_to_jokey();
    void set_new_pos(const common_position& pos);

private:
    int board_height;
    int board_width;

    bool whose_side;
    bool is_jokey;
    bool is_set;

    common_position origin;

    void give_handle_mov_res_pos(const std::vector<gam_tile_rep>& container, const int& pos, int& combat_scenario, std::vector<gam_mov_results>& to_push);

    bool util_is_pos_valid(const common_position& pos);

    template<int fronts, int sides>
    std::vector<common_position> give_sideway_coords();
};

class gam_board_logic
{
public:
    gam_board_logic(int height, int width) {
        this->board_height = height;
        this->board_width = width;
        
        if(height < 0 || width < 0 || height % 2 != 0 || width % 2 != 0) {
            this->board_height = -1;
            this->board_width = -1;
        }
    };

    ~gam_board_logic() {};
    
    void init();
    void test() {
        
        return;
    }

    common_board_interface communicate_with_interface(const gam_round_phase& game_phase, const bool& whose_turn, const common_position& select, const common_position& move_to);
private:
    int board_height;
    int board_width;

    std::vector<gam_board_piece> our_pieces;

    int find_piece_by_pos(const common_position& pos);
    void find_sideway_coords(std::vector<std::vector<common_position>>& container, const common_position& pos, int& our_index);
    std::vector<gam_tile_rep> find_sideway_rep(const std::vector<common_position> sideway_cont);

    int count_move(const common_position& pos, const gam_relative_directions& direction);
    int count_strike(const common_position& pos, const gam_relative_directions& direction, const bool& is_restrike_check);
    
    std::vector<common_position> get_move_to(const common_position& pos);
    void get_movable(const common_position& pos, std::vector<common_position>& to_add, const bool& whose_turn);
    std::vector<common_position> get_strike_to(const common_position& pos, const bool& is_restrike);
    void get_strikable(const common_position& pos, std::vector<common_position>& to_add, const bool& whose_turn);
    bool get_restrikeable(const common_position& pos);

    std::vector<common_position> compose_movable(const bool& whose_turn);
    std::vector<common_position> compose_strikable(const bool& whose_turn);
    std::vector<common_position> compose_selectable(const bool& whose_turn);
    std::vector<common_position> compose_to_strike(const common_position& relative_to, const std::vector<common_position>& strike_ends);

    void communicate_phase_start(const bool& whose_turn, common_board_interface& to_edit);
    void communicate_handle_start(common_board_interface& to_edit, const common_position& local_pos, const std::vector<common_position>& local_poses);
    void communicate_phase_selected(const bool& whose_turn, common_board_interface& to_edit, const common_position& selection);
    void communicate_handle_selected(common_board_interface& to_eidt, const common_position& local_pos, const common_position& current_pos, const std::vector<common_position>& move_points, const std::vector<common_position>& strike_points, const std::vector<common_position>& to_strike);
    void communicate_phase_pre(common_board_interface& to_eidt, const common_position& at_pos, const common_position& to_pos);
    void communicate_handle_pre(common_board_interface& to_edit, const common_position& local_pos, const common_position& at_pos, const common_position& to_pos, const common_position& posb_strike);
};

#endif