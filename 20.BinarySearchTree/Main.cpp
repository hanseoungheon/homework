#include "BinarySearchTree.h"

int main()
{
	BinarySearchTree<int> tree;

	tree.Insert(10);
	tree.Insert(20);
	tree.Insert(30);
	tree.Insert(5);
	tree.Insert(1);
	tree.Insert(15);

	//����.
	tree.Delete(5);
	//tree.Delete(15);

	//�˻�.

	std::cin.get();
}