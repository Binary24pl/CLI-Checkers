#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_show_pallette();

    std::vector<ITF::itf_tile*> preload_content;
    ITF::itf_preload_content(preload_content);

    ITF::itf_clean_content(preload_content);
    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}