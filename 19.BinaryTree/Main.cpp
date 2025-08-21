#include <iostream>
#include "BinaryTree.h"
#include "String.h"


//������.
int main()
{
	// Ʈ�� ����.
	//     A
	//    / \
	//   B   C
	//  / \
	// D   E
	BinaryTree<String> tree("A");
	tree.AddLeftChild("A","B"); //A���� �ؿ� B�߰�
	tree.AddRightChild("A","C"); //A������ �ؿ� B�߰�
	tree.AddLeftChild("B", "D"); 
	tree.AddRightChild("B", "E");

	std::cout << "���� ��ȸ\n";
	tree.PreorderTraverse();

	std::cout << "\n E��� ����.\n";
	tree.DeleteNode("E");

	std::cout << "\n���� ��ȸ\n";
	tree.PreorderTraverse();

	std::cin.get();
}