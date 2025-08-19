#include <iostream>
#include "Tree.h"
#include "String.h"
int main()
{
	//트리 생성
	Tree<String> tree("A");
	tree.AddChild("A", "B");	// A의 자손으로 B 추가.
	tree.AddChild("A", "C");	// A의 자손으로 C 추가.
	tree.AddChild("B", "D");	// B의 자손으로 D 추가.
	tree.AddChild("B", "E");	// B의 자손으로 E 추가.
	tree.AddChild("C", "F");	// C의 자손으로 F 추가.

	std::cin.get();
}