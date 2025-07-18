#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_show_pallette();

    ITF::itf_board* global_board;
    global_board = new itf_board(4,4);
    global_board->init();

    delete global_board;

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}