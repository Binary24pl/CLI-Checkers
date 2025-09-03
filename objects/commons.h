#include <iostream>
#include <locale>
#include <vector>
#include <sstream>

template<typename FROM, typename TO> TO common_translate_value(FROM to_translate);
template<typename PASS, typename CLASS> void common_passer(const PASS& to_pass, CLASS* of_obj, void(CLASS::*method)(void*&));

enum common_board_pawns_types
{
    CMN_PAWN_DARK,
    CMN_PAWN_LIGHT,
    CMN_JOKEY_DARK,
    CMN_JOKEY_LIGHT   
};

enum common_states
{
    CMN_STAT_NEITHER,
    CMN_STAT_SELECTABLE,
    CMN_STAT_STRIKABLE,
    CMN_STAT_SELECTED
};

struct common_position
{
    int on_height;
    int on_width;
};

struct common_board_pawns
{
    common_board_pawns_types type;
    common_position position;
    common_states current_state;
};

struct common_board_playable
{
    common_position position;
    common_states current_state;
};

struct common_board_interface
{
    std::vector<common_board_pawns> pawns;
    std::vector<common_board_playable> playable;
};

//debug function
void common_define_playable(std::vector<common_board_playable>& to_write, int width, int height);
void common_define_showcase(std::vector<common_board_pawns>& to_write, int width, int height);;


#include "itf_values.h"

#include "itf_funcs.h"
#include "itf_tile.h"
#include "itf_board.h"
#include "itf_query_element.h"
#include "itf_question.h"

#include "gam_values.h"

#include "gam_board.h"
#include "gam_board_mov.h"
#include "gam_board_slt.h"
#include "gam_board_chain.h"
#include "gam_board_think.h"
#include "gam_board_scenario.h"
#include "gam_mainloop.h"

void common_board_setter(int height, int width, ITF::itf_board*& interface, GAM::gam_board*& logic);

template<typename FROM, typename TO> TO common_translate_value(FROM to_translate)
{
    std::stringstream translator;
    TO to_return;

    translator << to_translate;
    translator >> to_return;

    return to_return;
}

template<typename PASS, typename CLASS> void common_passer(const PASS& to_pass, CLASS* of_obj, void(CLASS::*method)(void*&))
{
    PASS* to_cast = new PASS; //alloc id: 4, 6
    *to_cast = to_pass;

    void* arg;
    arg = (void*)to_cast;

    (of_obj->*method)(arg);

    delete to_cast; //de_alloc id: 4, 6
}

void common_define_playable(std::vector<common_board_playable>& to_write, int width, int height)
{
    for(int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {
            if(h % 2 == w % 2) {
                common_board_playable temp;
                temp.position.on_height = h;
                temp.position.on_width = w;
                temp.current_state = CMN_STAT_NEITHER;

                to_write.push_back(temp);
            }
        }
    }
}

void common_define_showcase(std::vector<common_board_pawns>& to_write, int width, int height)
{
    int vrt_x, vrt_y;

    vrt_x = vrt_y = 0;

    for(int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {
            if(h % 2 == w % 2) {
                common_board_pawns temp;
                temp.position.on_height = h;
                temp.position.on_width = w;

                temp.type = (common_board_pawns_types)(vrt_x % 4);
                temp.current_state = (common_states)(vrt_y % 4);

                vrt_y += 1;
                to_write.push_back(temp);

                std::cout << temp.type << " : our type; " << temp.current_state << " : our state;" << std::endl;
            }
        }
        vrt_y = 0;
        vrt_x += 1;
    }
}

void common_board_setter(int height, int width, ITF::itf_board*& interface, GAM::gam_board*& logic) {
    interface = new ITF::itf_board(height, width);
    logic = new ITF::gam_board(height, width);

    interface->init();
    logic->init();
}