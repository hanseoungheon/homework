#include <iostream>
#include "Deque.h"

int main()
{
	Deque<int> deque;

	for (int ix = 0; ix < 10; ++ix)
	{
		if (ix % 2 == 0)
		{
			deque.AddFront(ix);
		}
		else
		{
			deque.AddRear(ix);
		}
	}

	deque.Print();
}