#include <iostream>
#include "MergeSort.h"

#define ArraySize(array) sizeof(array) / sizeof(array[0])

// 배열 출력 함수.
void PrintArray(int array[], int length)
{
    for (int ix = 0; ix < length; ++ix)
    {
        std::cout << array[ix] << (ix < length - 1 ? ", " : "");
    }

    std::cout << "\n";
}

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // 배열.
    int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

    int length = (int)ArraySize(array);

    std::cout << "정렬 전 배열 : ";
    PrintArray(array,length);

    //정렬
    MergeSort(array, length);

    std::cout << "정렬 후 배열 : ";
    PrintArray(array, length);

}