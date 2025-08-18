#include <iostream>
#include "Queue.h"
int main()
{
	Queue queue;

	for (int ix = 0; ix < 10; ++ix)
	{
		queue.Enqueue(ix + 1);
	}

	queue.Print();

	int value = 0;

	queue.Dequeue(value);
	queue.Dequeue(value);
	queue.Dequeue(value);

	queue.Print();

	std::cin.get();
}