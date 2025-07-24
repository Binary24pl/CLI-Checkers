#ifndef ITF
#define ITF

#define ITF_BHB "▄"
#define ITF_C_END "\e[0m"

enum itf_colors {
    ITF_C_BLACK = (int)'0',
    ITF_C_RED = (int)'1',
    ITF_C_GREEN = (int)'2',
    ITF_C_YELLOW = (int)'3',
    ITF_C_BLUE = (int)'4',
    ITF_C_PURPLE = (int)'5',
    ITF_C_CYAN = (int)'6',
    ITF_C_WHITE = (int)'7'
};

enum itf_lines_drct {
    ITF_D_UP,
    ITF_D_DOWN,
    ITF_D_LEFT,
    ITF_D_RIGHT
};

enum itf_preload_idx {
    ITF_IDX_NON_PLAYABLE = 0,
    ITF_IDX_EMPTY = 1,
    ITF_IDX_SELECTABLE_EMPTY = 2,
    ITF_IDX_SELECTED_EMPTY = 3,
    ITF_IDX_LIGHT_PAWN = 4,
    ITF_IDX_LIGHT_JOKEY = 5,
    ITF_IDX_LIGHT_PAWN_SELECTABLE = 6,
    ITF_IDX_LIGHT_PAWN_SELECTED = 7,
    ITF_IDX_LIGHT_PAWN_STRIKABLE = 8,
    ITF_IDX_LIGHT_JOKEY_SELECTABLE = 9,
    ITF_IDX_LIGHT_JOKEY_SELECTED = 10,
    ITF_IDX_LIGHT_JOKEY_STRIKABLE = 11,
    ITF_IDX_DARK_PAWN = 12,
    ITF_IDX_DARK_JOKEY = 13,
    ITF_IDX_DARK_PAWN_SELECTABLE = 14,
    ITF_IDX_DARK_PAWN_SELECTED = 15,
    ITF_IDX_DARK_PAWN_STRIKABLE = 16,
    ITF_IDX_DARK_JOKEY_SELECTABLE = 17,
    ITF_IDX_DARK_JOKEY_SELECTED = 18,
    ITF_IDX_DARK_JOKEY_STRIKABLE = 19
};

enum itf_input_whatami {
    ITF_INPUT_INT,
    ITF_INPUT_STRING,
    ITF_INPUT_CHAR,
    ITF_INPUT_ERROR
};

enum itf_inrange_type {
    ITF_RANGE_FROM_TO,
    ITF_RANGE_BEYOND,
    ITF_RANGE_IS_IN,
    ITF_RANGE_IS_NOT_IN
};

template<typename input_type>
struct itf_input_range
{
    input_type* args;
    int args_len;
    itf_inrange_type args_type;
};



#define ITF_COUNT_IDX 20

#define ITF_FG_LOW "3"
#define ITF_FG_HIGH "9"
#define ITF_BG_LOW "4"
#define ITF_BG_HIGH "10"

#define ITF_LOW_INTEN false
#define ITF_HIGH_INTEN true

#define ITF_MOVE_PEN true

#define ITF_RCT_FULL false
#define ITF_RCT_HLOW true

struct itf_pixels {
    itf_colors color;
    bool intensity;
    bool used;
};

struct itf_text_pallete {
    itf_colors fg_color;
    itf_colors bg_color;
    bool fg_inten;
    bool bg_inten;
};

struct itf_pencil {
    int on_hght;
    int on_wdth;
    int on_layer;
};

//used to create bash color string
std::string itf_give_color(const std::string& to_color, const itf_text_pallete& of_color);

class itf_tile {
public:
    itf_tile(const int& h, const int& w) {
        if(h % 2 != 0 && w % 2 != 0) {
            this->height = -1;
            this->width = -1;
        } else {
            this->height = h;
            this->width = w;

            const int buf_cap = h / 2;
            for(int add_buffer = 0; add_buffer < buf_cap; add_buffer++) {
                this->tile_buffer.push_back("");
            }
        }

        this->draw_pencil.on_hght = this->draw_pencil.on_wdth = this->draw_pencil.on_layer = 0;
    };

    ~itf_tile() {
        if(this->height != -1 && this->width != -1) {
            for(int cln_rws = 0; cln_rws < this->height; cln_rws++) delete[] this->tile_build[cln_rws];
            delete[] this->tile_build;
        }

        //if layers contain anything really
        if(this->draw_layers.size() > 0) {
            for(int dst_layer = 0; dst_layer < this->draw_layers.size(); dst_layer++) {
                itf_pixels** rnd_layer; //rnd stands for read and destroy
                rnd_layer = this->draw_layers[dst_layer];

                for(int cln_rws = 0; cln_rws < this->height; cln_rws++) delete[] rnd_layer[cln_rws];
                delete[] rnd_layer;
            }
        }
    };

    void init(); // reads what output did validation make and creates needed data
    void create_new_layer(bool move_pen);

    //as name suggest, these lil fellas are responsible for creating a final product
    void create_build();
    void create_buffer();

    void paint_fill(const itf_colors color, const bool intensity);
    void paint_pixel(const itf_colors color, const bool intensity);
    void paint_line(const itf_colors color, const bool intensity, const itf_lines_drct direction, const int size);
    void paint_rect(const itf_colors color, const bool intensity, const bool is_hollow, const int hght, const int wdth);

    std::vector<std::string> tile_buffer;
    itf_pencil draw_pencil;
private:
    itf_pixels** tile_build;
    std::vector<itf_pixels**> draw_layers;

    int height, width;
};

void itf_show_pallette();

void itf_preload_content(std::vector<itf_tile*>& container);

void itf_clean_content(std::vector<itf_tile*>& container)
{
    for(int clean = 0; clean < ITF_COUNT_IDX; clean++) delete container[clean];
}


class itf_board {
public:
    itf_board(const int& height, const int& width) {
        if(height % 2 != 0 || width % 2 != 0) {
            this->board_height = -1;
            this->board_width = -1;
        } else {
            this->board_height = height;
            this->board_width = width;
        }
    }

    ~itf_board() {
        if(this->board_height != -1 && this->board_width != -1) {
            itf_clean_content(this->pre_gen_content);

            for(int clean_vs = 0; clean_vs < this->board_height; clean_vs++) delete[] this->state_visual[clean_vs];
            delete[] this->state_visual;
        }
    }

    void init();
    void test();
    void show_visual_state();
private:
    int board_height, board_width;
    int buffer_size;
    const int tile_width = 8;
    std::vector<itf_tile*> pre_gen_content;
    itf_preload_idx** state_visual;

    void top_numeric_indexies();
};

class itf_query_master {
public:
    itf_query_master() {}

    virtual ~itf_query_master() {};

    itf_input_whatami identity;

    virtual void assign_val(void*& val) = 0;
    virtual void set_range(void*& range) = 0;
    virtual bool validate() = 0;

    virtual void give_val(void*& caller) = 0;
    virtual void give_range(void*& caller) = 0;
};

template<typename input_type>
class itf_query_element : public itf_query_master {
public:
    itf_query_element() {
        input_type tested;

        std::string test_str;
        char test_chr;
        int test_int;

        if(typeid(tested) == typeid(test_str)) {
            this->identity = ITF_INPUT_STRING;
        } else if(typeid(tested) == typeid(test_chr)) {
            this->identity = ITF_INPUT_CHAR;
        } else if(typeid(tested) == typeid(test_int)) {
            this->identity = ITF_INPUT_INT;
        } else {
            this->identity = ITF_INPUT_ERROR;
        }

        this->local_range = nullptr;
    };

    itf_query_element(itf_query_master* other) {
        input_type tested;

        std::string test_str;
        char test_chr;
        int test_int;

        if(typeid(tested) == typeid(test_str)) {
            this->identity = ITF_INPUT_STRING;
        } else if(typeid(tested) == typeid(test_chr)) {
            this->identity = ITF_INPUT_CHAR;
        } else if(typeid(tested) == typeid(test_int)) {
            this->identity = ITF_INPUT_INT;
        } else {
            this->identity = ITF_INPUT_ERROR;
        }

        if(other->identity == this->identity) {
            void* our_object = (void*)this;
            other->give_val(our_object);
            other->give_range(our_object);
        }
    }

    ~itf_query_element() override {
        if(this->local_range != nullptr) {
            delete[] this->local_range->args;
            delete this->local_range;
        }
    };

    void assign_val(void*& val) override;
    void set_range(void*& range) override;
    bool validate() override;

    void give_val(void*& caller) override;
    void give_range(void*& caller) override;
private:
    input_type local_val;
    itf_input_range<input_type>* local_range;

    void ntv_assign_val(const input_type& val); // native implementation of assign_val
    void ntv_set_range(const itf_input_range<input_type>& range);

    bool range_from_to();
    bool range_beyond();
    bool range_is_in();
    bool range_not_in();
};

class itf_question {
public:
    itf_question() {
        this->question_form = nullptr;
    };
    
    ~itf_question() {
        this->cleanup_question();
    };

    void start_new_question(const int& size);
    void build_into_question(const itf_input_whatami& what_kind, const int& what_posiiton);
    template<typename input_type> void give_element_range(const itf_input_range<input_type>& range, const int& position);
private:
    itf_query_master** question_form;
    int question_length;
    void cleanup_question();
    template <typename compared, typename input_type> bool verify_type(const input_type& to_check);
};

#endif