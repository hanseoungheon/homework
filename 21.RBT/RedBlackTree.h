#pragma once
#include "Node.h"
#include <iostream>

class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	//�˻�
	bool Find(int data, Node*& outNode);

	//�߰�
	bool Insert(int data);

private:
	//��� �����Լ�.
	Node* CreateNode(int data, Color color);

	//�˻� ��� �Լ�.
	bool FindRecursive(int data, Node* currentNode, Node*& outNode);
	
	//��� ���� ����Լ�,.
	void InsertRecusive(Node* currentNode, Node* newNode);

	//��� ���� �� ������ �Լ�.
	void RestructeAfterInsert(Node* newNode);

	//��ȸ�� �Լ�,
	void RotateToLeft(Node* node);

	//��ȸ�� �Լ�.
	void RotateToRight(Node* node);
private:
	//��Ʈ ���
	Node* root = nullptr;

	//NilNode
	static Node* nil;
};