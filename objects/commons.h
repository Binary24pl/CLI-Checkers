#include <iostream>
#include <locale>
#include <vector>
#include <sstream>

template<typename FROM, typename TO> TO common_translate_value(FROM to_translate);

#include "logic_values.h"
#include "itf_values.h"

#include "logic_funcs.h"
#include "logic_node.h"

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