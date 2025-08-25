#pragma once

#include <vector>
#include "Bounds.h"

class Node;

class QuadTree
{
public:
	QuadTree(const Bounds& bounds);
	~QuadTree();

	//Ʈ���� ��带 �߰��ϴ� �Լ�.
	void Insert(Node* node);

	//������ ���� ��ġ�� ��带��ȯ�ϴ� �Լ�(����-Query)
	std::vector<Node*> Query(Node* queryNode);

public:
	//���� �� �ִ� Ʈ���� �ִ� ���� ��.
	static const int maxDepth = 3;

private:
	Node* root = nullptr;
};