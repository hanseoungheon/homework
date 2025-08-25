#include <iostream>
#include "QuadTree.h"
#include "Node.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//Ʈ�� ����.
	QuadTree tree(Bounds(0, 0, 100, 100));

	
	//����
	tree.Insert(new Node(Bounds(40.0f, 40.0f, 20.0f, 20.0f)));
	tree.Insert(new Node(Bounds(20.0f, 20.0f, 2.0f, 2.0f)));

	//Bounds bound = Bounds(50, 50, 5, 5); ��� ��������ڷ� ȣ���ؼ� �޸� ��뷮 �þ
	//���� �����Ϸ��� �˾Ƽ� ����ȭ�ϱ��ϴµ� Ȥ�� ���� �����ؼ� �����.

	//����.(����).
	Node testNode(Bounds(50, 50, 5, 5));
	std::vector<Node*> intersects = tree.Query(&testNode);

	if (intersects.size() == 0)
	{
		std::cout << "��ġ�� ��带 ã�� ���߽��ϴ�.\n";
	}
	else
	{
		std::cout << "��ġ�� ��带 " << intersects.size() << "�� ã�ҽ��ϴ�.\n";
	}

	std::cin.get();
}

