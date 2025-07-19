#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    std::cout << (char)((int)'A' + 1) << " " << (int)'a' << " " << (int)'A' << std::endl;
    std::cout << common_translate_value<int, std::string>(123).length() << " " << common_translate_value<std::string, int>("222") << std::endl;

    ITF::itf_board* global_board;
    global_board = new itf_board(10,10);
    global_board->init();
    global_board->test();
    global_board->show_visual_state();

    delete global_board;

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}