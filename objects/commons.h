#include <iostream>
#include <locale>
#include <vector>
#include <sstream>

template<typename FROM, typename TO> TO common_translate_value(FROM to_translate);
void common_create_void_arr(void **&arr, const int& size);
template<typename CAST>CAST common_get_elm_void_arr(void **&arr, const int& idx);

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

void common_create_void_arr(void **&arr, const int& size) {
    arr = (void **)malloc(sizeof(void*) * size);
}

template<typename CAST>CAST common_get_elm_void_arr(void **&arr, const int& idx) {
    void* ptr = arr[idx];
    CAST* casted = (CAST*)ptr;
    CAST to_return = *casted;

    return to_return;
}