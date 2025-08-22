#pragma once
#include <iostream>

//좌표 다루기 위한 구조체.
//C++ 원칙상 Struct/Class는 차이강 없음.
//굳이 있다면 접근한정자가 struct는 public/class는 private가 기본인것?
//물론 코딩표준상 구조체는 데이터전용, 클래스는 객체용으로 쓰인다.
struct Position
{
	Position(int x = 0, int y = 0)
		: x(x), y(y)
	{

	}

	~Position()
	{
		
	}

	bool operator==(const Position& other)
	{
		return (x == other.x) && (y == other.y);
	}

	int x = 0;
	int y = 0;
};

class Node
{
public:
	Node(int x, int y, Node* parentNode = nullptr)
		: position(x,y), parent(parentNode)
	{

	}

	Position operator-(const Node& other)
	{
		return Position(
			position.x - other.position.x,
			position.y - other.position.y
		);
	}

	bool operator==(const Node& other) const
	{
		return position.x == other.position.x &&
			position.y == other.position.y;
	}


public:
	Position position;

	float gCost = 0.0f;
	float hCost = 0.0f;
	float fCost = 0.0f;

	Node* parent = nullptr;
};