//#include <iostream>
//
//int Binary_Search(int* array, int start, int end, int targetIndex)
//{
//	int middle = (start + end) / 2;
//
//	if (targetIndex = array[middle])
//	{
//		std::cout << "Ã£¾Ò´Ù";
//		return middle;
//	}
//
//	if (targetIndex > array[middle])
//	{
//		start = middle + 1;
//		return Binary_Search(array, start, end, targetIndex);
//	}
//	else if (targetIndex < array[middle])
//	{
//		end = middle - 1;
//		return Binary_Search(array, start, end, targetIndex);
//	}
//}
//
//int main()
//{
//	int array[] = { 1,2,3,4,5,6,7,8,9,10 };
//
//	int start = *array;
//	std::cout << start;
//	//int FindIndex = Binary_Search(array,array)
//}

#include <iostream>
using namespace std;

class Base
{
public:
    virtual void Show() { cout << "Base\n"; }
};

class Derived : public Base
{
public:
    virtual void Show() override { cout << "Derived\n"; }
};

int main()
{
    Base* b = new Derived();
    b->Show();
    delete b;
}
