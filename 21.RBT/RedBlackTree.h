#pragma once
#include "Node.h"
#include <iostream>
#include <Windows.h>
enum class TextColor
{
	// 콘솔 색상 정의.
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

	//검색
	bool Find(int data, Node*& outNode);

	//추가
	bool Insert(int data);

	//출력용
	void Print(int depth = 0, int blackCount = 0);

	//void Destroy();

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

	//출력 재귀함수.
	void PrintRecursive(Node* node, int depth, int blackCount);

	// 트리 파괴 재귀 함수.
	void DestroyRecursive(Node* node);
private:
	//루트 노드
	Node* root = nullptr;

	//NilNode
	Node* nil = nullptr;

};

//콘솔 색상 변경 함수.
void SetTextColor(TextColor color);