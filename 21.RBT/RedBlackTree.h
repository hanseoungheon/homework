#pragma once
#include "Node.h"
#include <iostream>
#include <Windows.h>
enum class TextColor
{
	// �ܼ� ���� ����.
	Red = FOREGROUND_RED,
	Green = FOREGROUND_GREEN,
	Blue = FOREGROUND_BLUE,
	White = Red | Green | Blue,
};

class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	//�˻�
	bool Find(int data, Node*& outNode);

	//�߰�
	bool Insert(int data);

	//��¿�
	void Print(int depth = 0, int blackCount = 0);

	//void Destroy();

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

	//��� ����Լ�.
	void PrintRecursive(Node* node, int depth, int blackCount);

	// Ʈ�� �ı� ��� �Լ�.
	void DestroyRecursive(Node* node);
private:
	//��Ʈ ���
	Node* root = nullptr;

	//NilNode
	Node* nil = nullptr;

};

//�ܼ� ���� ���� �Լ�.
void SetTextColor(TextColor color);