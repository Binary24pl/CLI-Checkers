#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    const int size = 2;
    void **arr;

    common_create_void_arr(arr, size);

    int *x = new int(2);
    char *y = new char('U');

    arr[0] = (void*)x;
    arr[1] = (void*)y;

    std::cout << common_get_elm_void_arr<int>(arr, 0) << std::endl;
    std::cout << common_get_elm_void_arr<char>(arr, 1) << std::endl;

    delete arr[0];
    delete arr[1];
    

    free(arr);

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}