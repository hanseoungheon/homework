#include <iostream>
#include "Vector.h"

int main()
{
	const int count = 30;
	Vector<int> vector;
	for (int ix = 0; ix < count; ++ix)
	{
		vector.PushBack(ix + 1);
	}

	for (auto& item : vector)
	{
		std::cout << item << " ";
	}

	

	std::cin.get();

}