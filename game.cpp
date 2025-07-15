#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_show_pallette();

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}