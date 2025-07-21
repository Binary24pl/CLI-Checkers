#include <iostream>
#include <locale>
#include <vector>
#include <sstream>

template<typename FROM, typename TO> TO common_translate_value(FROM to_translate);
template<typename PASS> void common_passer(PASS to_pass, void(*func_ptr)(void*&));

#include "itf_values.h"

#include "itf_funcs.h"
#include "itf_tile.h"
#include "itf_board.h"

template<typename FROM, typename TO> TO common_translate_value(FROM to_translate)
{
    std::stringstream translator;
    TO to_return;

    translator << to_translate;
    translator >> to_return;

    return to_return;
}

template<typename PASS> void common_passer(PASS to_pass, void(*func_ptr)(void*&))
{
    PASS* to_cast = new PASS;
    *to_cast = to_pass;

    void* to_send;
    to_send = (void*)to_cast;

    func_ptr(to_send);

    delete to_cast;
}