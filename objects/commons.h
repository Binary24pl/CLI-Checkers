#include <iostream>
#include <locale>
#include <vector>
#include <sstream>

template<typename FROM, typename TO> TO common_translate_value(FROM to_translate);
template<typename PASS, typename CLASS> void common_passer(const PASS& to_pass, CLASS* of_obj, void(CLASS::*method)(void*&));

#include "sgl_values.h"
#include "itf_values.h"

#include "sgl_funcs.h"
#include "sgl_signal.h"

#include "itf_funcs.h"
#include "itf_tile.h"
#include "itf_board.h"
#include "itf_query_element.h"
#include "itf_question.h"

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