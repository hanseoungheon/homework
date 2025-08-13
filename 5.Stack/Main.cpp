#include <iostream>
#include "Stack.h"
#include <stack>
int main(void)
{
	std::stack<float> expStack;

	expStack.emplace(100.0f);

	Stack<float> stack;

	stack.Push(15.0f);
	stack.Push(30.0f);

	while (!stack.IsEmpty())
	{
		std::cout << "°æÇèÄ¡ : " << stack.Pop() << "\n";
	}

	std::cin.get();
}