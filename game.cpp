#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_board* our_board = new ITF::itf_board(10, 10);
    our_board->init();
    our_board->test();
    our_board->show_visual_state();


    ITF::itf_question* test = new ITF::itf_question;
    test->start_new_question(3);
    test->build_into_question(ITF_INPUT_STRING, 0);
    test->build_into_question(ITF_INPUT_CHAR, 1);
    test->build_into_question(ITF_INPUT_INT, 2);

    ITF::itf_input_range<std::string> str_range;
    ITF::itf_input_range<char> chr_range;
    ITF::itf_input_range<int> num_range;

    str_range.args_len = 2;
    str_range.args_type = ITF_RANGE_IS_IN;
    str_range.args = new std::string[2];

    str_range.args[0] = "select";
    str_range.args[1] = "unselect";

    chr_range.args_len = 2;
    chr_range.args_type = ITF_RANGE_FROM_TO;
    chr_range.args = new char[2];

    chr_range.args[0] = 'A';
    chr_range.args[1] = (char)((int)'A' + 9);

    num_range.args_len = 2;
    num_range.args_type = ITF_RANGE_FROM_TO;
    num_range.args = new int[2];

    num_range.args[0] = 1;
    num_range.args[1] = 10;

    test->give_element_range<std::string>(str_range, 0);
    test->give_element_range<char>(chr_range, 1);
    test->give_element_range<int>(num_range, 2);

    test->ask_question();
    
    delete our_board;
    delete test;
    delete[] str_range.args;
    delete[] chr_range.args;
    delete[] num_range.args;
    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}