#include "AStar.h"
#include "Node.h"
#include <Windows.h>

AStar::AStar()
{
}

AStar::~AStar()
{
	//�޸� ����.
	for (Node* node : openList)
	{
		SafeDelete(node);
	}
	openList.clear();

	for (Node* node : closedList)
	{
		SafeDelete(node);
	}
	closedList.clear();
}

void AStar::DisplayGridWithPath(
	std::vector<std::vector<int>>& grid, const std::vector<Node*>& path)
{
	static COORD position = { 0, 0 };
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, position);

	int white = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	int green = FOREGROUND_GREEN;

	// ������ ���� �����ߴ� ������ �ʱ�ȭ.
	for (int y = 0; y < grid.size(); ++y)
	{
		for (int x = 0; x < grid[0].size(); ++x)
		{
			int& value = grid[y][x];
			if (value == 2 || value == 3 || value == 5)
			{
				value = 0;
			}
		}
	}

	// ��θ� ������ �� ���.
	for (int y = 0; y < grid.size(); ++y)
	{
		for (int x = 0; x < grid[0].size(); ++x)
		{
			// ��ֹ�.
			if (grid[y][x] == 1)
			{
				SetConsoleTextAttribute(handle, white);
				std::cout << "1 ";
			}


			// �� ����.
			else if (grid[y][x] == 0)
			{
				SetConsoleTextAttribute(handle, white);
				std::cout << "0 ";
			}
		}

		std::cout << "\n";
	}

	// ��� ���.
	for (const Node* node : path)
	{
		// ��δ� '2'�� ǥ��.
		COORD position{ static_cast<short>(node->position.x * 2), static_cast<short>(node->position.y) };
		SetConsoleCursorPosition(handle, position);
		SetConsoleTextAttribute(handle, green);

		std::cout << "* ";
		int delay = static_cast<int>(0.05f * 1000);
		Sleep(delay);
	}
}

std::vector<Node*> AStar::FindPath(Node* startNode, Node* goalNode, std::vector<std::vector<int>>& grid)
{
	//���� ��� / ��ǥ ��� ����.
	this->startNode = startNode;
	this->goalNode = goalNode;

	//���� ��带 ���� ���(openList)�� ����.
	openList.emplace_back(startNode);

	//�����¿�. �밢�� ���� �� ���.
	std::vector<Direction> directions =
	{
		//�� �� �� �� ������ �̵�.
		{0, 1, 1.0f}, {0, -1, 1.0f}, {1, 0, 1.0f}, {-1, 0, 1.0f},


		//�밢�� �̵�.
		{ 1, 1, 1.414f } ,{ 1, -1, 1.414f } ,{ -1, 1, 1.414f } ,{ -1, -1, 1.414f }
	};

	//�湮.
	while (!openList.empty()) //������������� ��� �湮.
	{
		//���� ����� ���� ��� ����.
		Node* lowestNode = openList[0];

		for (Node* node : openList)
		{
			if (node->fCost < lowestNode->fCost)
			{
				lowestNode = node;
			}
		}

		//fcost�� ���� ���� ��带 ���� ���� ����.
		Node* currentNode = lowestNode;

		//���� ��尡 ��ǥ ������� Ȯ��.

		if (IsDestination(currentNode) == true)
		{
			//��ǥ �����, ���ݱ����� ��θ� ����ؼ� ��ȯ.
			return ConstructPath(currentNode);
		}

		//���� ��Ͽ� �߰� (���� ��Ͽ����� ����).
		for (int ix = 0; ix < (int)openList.size(); ++ix)
		{
			if (*openList[ix] == *currentNode)
			{
				//���ͷ����͸� ����ؼ� �迭���� ��� �������� ����.
				openList.erase(openList.begin() + ix);
				break;
			}
		}

		//���� ��带 ���� ��忡 �߰�.
		//���� �̹��ִ���Ȯ��.
		bool isNodeInList = false;
		for (Node* node : closedList)
		{
			if (*node == *currentNode)
			{
				isNodeInList == true;
				break;
			}
		}

		//�湮 ������ �Ʒ� �ܰ� �ǳʶٱ�.
		if (isNodeInList == true)
		{
			continue;
		}

		//���� ��Ͽ� ���� ��ġ �߰�.
		closedList.emplace_back(currentNode);

		//�̿� ��� �湮�ϱ�.
		for (const Direction& direction : directions)
		{
			//������ �̵��� ��ġ ����.
			int newX = currentNode->position.x + direction.x;
			int newY = currentNode->position.y + direction.y;

			if (IsInRange(newX, newY, grid) == false)
			{
				continue;
			}

			//�ɼ�. ��ֹ����� Ȯ���ϱ�.
			//���� 1�̸� ��ֹ��̶�� ���.
			if (grid[newY][newX] == 1)
			{
				continue;
			}

			//�̹� �湮�߾ ����.
			//�̹� �湮�ߴ��� Ȯ���ϴ� �Լ� �ۼ� �� ȣ��.
			float gCost = currentNode->gCost + direction.cost;
			if (HasVisited(newX, newY, gCost))
			{
				continue;
			}

			Node* neighborNode = new Node(newX, newY, currentNode);
			neighborNode->gCost = currentNode->gCost + direction.cost;
			//Todo: �޸���ƽ ��� ��� �Լ� �ۼ� �� ȣ��
			neighborNode->hCost = CalilateHeuristic(neighborNode, goalNode);
			neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;

			//������ ���� �Ǵ�.

			Node* openListNode = nullptr;
			for (Node* node : openList)
			{
				if (*node == *neighborNode)
				{
					openListNode = node;
					break;
				}
			}

			//��尡 ��Ͽ� ���ų� ����� �����ϸ� �� ��� �߰�.
			if (openListNode == nullptr
				|| openListNode->gCost > neighborNode->gCost
				|| openListNode->fCost > neighborNode->fCost
				)
			{
				//�湮�� ��带 Ư�������� ����.
				grid[newY][newX] = 5;
				openList.emplace_back(neighborNode);
			}
			else
			{
				SafeDelete(neighborNode);

			}

			//������
			DisplayGrid(grid);
			int delay = (int)(0.1f * 1000);
			Sleep(delay);
		}
	}

	return std::vector<Node*>();
}

std::vector<Node*> AStar::ConstructPath(Node* goalNode)
{
	//��¿� ��ι迭
	std::vector<Node*> path;
	Node* currentNode = goalNode;

	while(currentNode != nullptr)
	{
		path.emplace_back(currentNode);
		currentNode = currentNode->parent;
	}

	//���� �� ���� ������ߵ�.
	std::reverse(path.begin(), path.end());

	return path;
}

bool AStar::IsDestination(const Node* node)
{
	//��尡 ��ǥ ���� ��ġ�� ������ ��.
	return *node == *goalNode;
}

bool AStar::IsInRange(int x, int y, const std::vector<std::vector<int>>& grid)
{
	//x,y ������ ����� ����
	if (x < 0 || y < 0 || x >= int(grid[0].size()) || y >= (int)grid.size())
	{
		//grid[0]�� x��ǥ�� �� ���̹Ƿ� �� ���� ũ��� x��ǥ�� ũ��� ������.
		return false;
	}

	return true;
}

bool AStar::HasVisited(int x, int y, float gCost)
{
	//���� ����Ʈ�� ���� ����Ʈ�� �̹� �ش� ��尡 ������ �湮�� ������ ����.
	for (int ix = 0; ix < (int)openList.size(); ++ix)
	{
		Node* node = openList[ix];

		if (node->position.x == x && node->position.y == y)
		{
			//��ġ�� ����, ��뵵 �� ũ�� �湮�� ������ ����.
			if (node->gCost < gCost)
			{
				return true;
			}
			else if (node->gCost > gCost)
			{
				openList.erase(openList.begin() + ix);
				SafeDelete(node);
			}
		}
	}

	for (int ix = 0; ix < (int)closedList.size(); ++ix)
	{
		Node* node = closedList[ix];

		if (node->position.x == x && node->position.y == y)
		{
			//��ġ�� ����, ��뵵 ������ �湮�� ���� ����.
			if (node->gCost < gCost)
			{
				return true;
			}

			//��ġ�� ������ ����� �۴ٸ�, ���� ��� ����.
			else if(node->gCost > gCost)
			{
				closedList.erase(closedList.begin() + ix);
				SafeDelete(node);
			}
		}
	}

	//��Ͽ� ���ٰ� �ǴܵǸ� �湮���� ���������� ����. false��ȯ.
	return false;
}

float AStar::CalilateHeuristic(Node* currentNode, Node* goalNode)
{
	//�ܼ� �Ÿ� ������� �޸���ƽ ������� Ȱ��.
	Position diff = *currentNode - *goalNode;

	//�밢�� ���� ���ϱ�.
	return (float)std::sqrt( (diff.x * diff.x) + (diff.y * diff.y) );
}

void AStar::DisplayGrid(std::vector<std::vector<int>>& grid)
{
	static COORD position = { 0, 0 };
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, position);

	int white = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	int green = FOREGROUND_GREEN;

	for (int y = 0; y < grid.size(); ++y)
	{
		for (int x = 0; x < grid[0].size(); ++x)
		{
			// ���� ��ġ.
			if (grid[y][x] == 2)
			{
				SetConsoleTextAttribute(handle, FOREGROUND_RED);
				std::cout << "S ";
			}

			// ��ǥ ��ġ.
			if (grid[y][x] == 3)
			{
				SetConsoleTextAttribute(handle, FOREGROUND_RED);
				std::cout << "G ";
			}

			// ��ֹ�.
			if (grid[y][x] == 1)
			{
				SetConsoleTextAttribute(handle, white);
				std::cout << "1 ";
			}

			// ���.
			else if (grid[y][x] == 5)
			{
				SetConsoleTextAttribute(handle, green);
				std::cout << "+ ";
			}

			// �� ����.
			else if (grid[y][x] == 0)
			{
				SetConsoleTextAttribute(handle, white);
				std::cout << "0 ";
			}
		}

		std::cout << "\n";
	}
}

void AStar::End(std::vector<std::vector<int>>& grid)
{
	//int x = grid[grid.back()];
}
