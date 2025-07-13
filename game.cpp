#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    std::cout << std::endl;

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}