#include <iostream>
#include "BinaryTree.h"
#include "String.h"


//진입점.
int main()
{
	// 트리 생성.
	//     A
	//    / \
	//   B   C
	//  / \
	// D   E
	BinaryTree<String> tree("A");
	tree.AddLeftChild("A","B"); //A왼쪽 밑에 B추가
	tree.AddRightChild("A","C"); //A오른쪽 밑에 B추가
	tree.AddLeftChild("B", "D"); 
	tree.AddRightChild("B", "E");

	std::cout << "전위 순회\n";
	tree.PreorderTraverse();

	std::cout << "\n E노드 삭제.\n";
	tree.DeleteNode("E");

	std::cout << "\n전위 순회\n";
	tree.PreorderTraverse();

	std::cin.get();
}