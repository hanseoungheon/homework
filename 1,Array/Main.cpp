#include <iostream>
#include <array>
//배열 클래스
template<typename T,int size>
class Array
{
public:
    Array()
    {
        // 메모리 0으로 초기화.
        memset(data, 0, sizeof(T) * size);
    }

    T GetSize() const { return size; }

    // 연산자 오버로딩.
    T& operator[](int index)
    {
        if (index < 0 || index > size - 1)
        {
            //Silent is violent
            return data[0];
        }

        return data[index];
    }

private:
    T data[size];
};

//진입점
//실행용이면 진입점이 있어야함
//dll이면 진입점이 없어도 됨
int main()
{
	//int arrayCount = 10;
    std::array<int, 10> testArray;
	////배열 Stack
	//int array[5];
	//memset(array, 0, sizeof(int) * 5);

	////동적배열 Heap
	//int* heapArray = new int[arrayCount];

	//delete[] heapArray;

    const int count = 20;

	Array<int,count> array;

    for (int ix = 0; ix < array.GetSize(); ++ix)
    {
        array[ix] = ix + 1;
    }
    
	std::cin.get();
}