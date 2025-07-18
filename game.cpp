#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_show_pallette();

    ITF::itf_board* global_board;
    global_board = new itf_board(10,10);
    global_board->init();
    global_board->test();
    global_board->show_visual_state();

    delete global_board;

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}