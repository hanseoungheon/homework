#pragma once
#include<vector>

template<typename T>
void SafeDelete(T*& pointer)
{
	if (pointer)
	{
		delete pointer;
		pointer = nullptr;
	}
}

class Node;//���漱��
class AStar
{
	//���� ó���� ���� ����ü.
	struct Direction
	{
		int x = 0;
		int y = 0;

		float cost;
		float dir;
	};


public:
	AStar();
	~AStar();

	//��� Ž�� �Լ�.
	std::vector<Node*> FindPath(
		Node* startNode,
		Node* goalNode,
		std::vector <std::vector<int>>& grid
	);

	//��� ��� �Լ�.
	// �׸��� ��� �Լ�.
	void DisplayGridWithPath(
		std::vector<std::vector<int>>& grid,
		const std::vector<Node*>& path
	);

private:

	//Todo: Ž���� ��ģ �Ŀ� ��θ� ������ ��ȯ�ϴ� �Լ�.
	//��ǥ ��忡�� �θ� ��带 ������ ���� ������ ������ �ϸ鼭 ��θ� ����.
	std::vector<Node*> ConstructPath(Node* goalNode);

	//Ž���Ϸ��� ��尡 ��ǥ ������� Ȯ��.
	bool IsDestination(const Node* node);

	//�׸��� �ȿ� �ִ� �� Ȯ��.
	bool IsInRange(int x, int y, const std::vector<std::vector<int>>& grid);

	//�̹� �湮�ߴ��� Ȯ���ϴ� �Լ��Դϴ�.
	bool HasVisited(int x, int y, float gCost);

	//���� �������� ��ǥ ���������� ���� ����� �Լ�.
	float CalilateHeuristic(Node* currentNode, Node* goalNode);

	void DisplayGrid(std::vector<std::vector<int>>& grid);

	void End(std::vector<std::vector<int>>& grid);

private:
	//���� ����Ʈ.(�湮�� ����� ���)
	std::vector<Node*> openList;

	//���� ����Ʈ.(�湮�� ����� ���)
	std::vector<Node*> closedList;
	//���� ���.
	Node* startNode = nullptr;

	//��ǥ ���.
	Node* goalNode = nullptr;
};