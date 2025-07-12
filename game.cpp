#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_text_pallete test;
    test.bg_color = ITF_C_BLACK;
    test.fg_color = ITF_C_RED;
    test.bg_inten = ITF_HIGH_INTEN;
    test.fg_inten = ITF_LOW_INTEN;

    std::string view = ITF::itf_give_color("Hello world", test);
    std::cout << view << std::endl;

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}