#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    std::vector<std::string> question;
    std::string word;

    while (std::cin >> word)
    {
        question.push_back(word);
        if(std::cin.peek() == '\n') break;
    }

    for(int i = 0; i < question.size(); i++) {
        std::cout << question[i].length() << std::endl;
    }
    

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}