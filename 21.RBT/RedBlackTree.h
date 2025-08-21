#pragma once
#include "Node.h"
#include <iostream>

class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	//검색
	bool Find(int data, Node*& outNode);

	//추가
	bool Insert(int data);

private:
	//노드 생성함수.
	Node* CreateNode(int data, Color color);

	//검색 재귀 함수.
	bool FindRecursive(int data, Node* currentNode, Node*& outNode);
	
	//노드 삽입 재귀함수,.
	void InsertRecusive(Node* currentNode, Node* newNode);

	//노드 삽입 후 재정렬 함수.
	void RestructeAfterInsert(Node* newNode);

	//좌회전 함수,
	void RotateToLeft(Node* node);

	//우회전 함수.
	void RotateToRight(Node* node);
private:
	//루트 노드
	Node* root = nullptr;

	//NilNode
	static Node* nil;
};