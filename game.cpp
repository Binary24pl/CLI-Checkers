#include "objects/commons.h"

int main() {
    std::locale::global(std::locale("")); //making special characters work
    

    std::locale::global(std::locale::classic());

    return 0;
}