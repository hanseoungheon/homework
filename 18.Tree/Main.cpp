#include <iostream>
#include "Tree.h"
#include "String.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//Ʈ�� ����
	Tree<String> tree("A");
	tree.AddChild("A", "B");	// A�� �ڼ����� B �߰�.
	tree.AddChild("A", "C");	// A�� �ڼ����� C �߰�.
	tree.AddChild("B", "D");	// B�� �ڼ����� D �߰�.
	tree.AddChild("B", "E");	// B�� �ڼ����� E �߰�.
	tree.AddChild("C", "F");	// C�� �ڼ����� F �߰�.

	// ��ȸ.
	std::cout << "Ʈ�� ���� ��ȸ\n";
	tree.PreOrderTraverse();

	// ����.
	std::cout << "\n\n";
	tree.ReMove("C");

	//std::cout << "\n��� ���� �� ���� ��ȸ\n";

	tree.PreOrderTraverse();
	std::cin.get();
}