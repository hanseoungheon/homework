#include <iostream>
#include <array>
//�迭 Ŭ����
template<typename T,int size>
class Array
{
public:
    Array()
    {
        // �޸� 0���� �ʱ�ȭ.
        memset(data, 0, sizeof(T) * size);
    }

    T GetSize() const { return size; }

    // ������ �����ε�.
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

//������
//������̸� �������� �־����
//dll�̸� �������� ��� ��
int main()
{
	//int arrayCount = 10;
    std::array<int, 10> testArray;
	////�迭 Stack
	//int array[5];
	//memset(array, 0, sizeof(int) * 5);

	////�����迭 Heap
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