#include "AStar.h"
#include "Node.h"

AStar::AStar()
{
}

AStar::~AStar()
{
	//메모리 해제.
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

void AStar::DisplayGridWithPath(std::vector<std::vector<int>>& grid, const std::vector<Node*>& path)
{
	for (const Node* node : path)
	{
		// 경로는 '2'로 표시.
		grid[node->position.y][node->position.x] = 2;
	}

	for (int y = 0; y < grid.size(); ++y)
	{
		for (int x = 0; x < grid[0].size(); ++x)
		{
			// 장애물.
			if (grid[y][x] == 1)
			{
				std::cout << "1 ";
			}

			// 경로.
			else if (grid[y][x] == 2)
			{
				std::cout << "* ";
			}

			// 빈 공간.
			else if (grid[y][x] == 0)
			{
				std::cout << "0 ";
			}
		}

		std::cout << "\n";
	}
}

std::vector<Node*> AStar::FindPath(Node* startNode, Node* goalNode, const std::vector<std::vector<int>>& grid)
{
	//시작 노드 / 목표 노드 저장.
	this->startNode = startNode;
	this->goalNode = goalNode;

	//시작 노드를 열린 목록(openList)에 저장.
	openList.emplace_back(startNode);

	//상하좌우. 대각선 방향 및 비용.
	std::vector<Direction> directions =
	{
		//하 상 우 좌 순서로 이동.
		{0, 1, 1.0f}, {0, -1, 1.0f}, {1, 0, 1.0f}, {-1, 0, 1.0f},


		//대각선 이동.
		{ 1, 1, 1.414f } ,{ 1, -1, 1.414f } ,{ -1, 1, 1.414f } ,{ -1, -1, 1.414f }
	};

	//방문.
	while (!openList.empty()) //비어있지않으면 계속 방문.
	{
		//가장 비용이 작은 노드 선택.
		Node* lowestNode = openList[0];

		for (Node* node : openList)
		{
			if (node->fCost < lowestNode->fCost)
			{
				lowestNode = node;
			}
		}

		//fcost가 가장 낮은 노드를 현재 노드로 설정.
		Node* currentNode = lowestNode;

		//현재 노드가 목표 노드인지 확인.

		if (IsDestination(currentNode) == true)
		{
			//목표 노드라면, 지금까지의 경로를 계산해서 반환.
			return ConstructPath(currentNode);
		}

		//닫힌 목록에 추가 (열린 목록에서는 제거).
		for (int ix = 0; ix < (int)openList.size(); ++ix)
		{
			if (*openList[ix] == *currentNode)
			{
				//이터레이터를 사용해서 배열에서 노드 동적으로 제거.
				openList.erase(openList.begin() + ix);
				break;
			}
		}

		//현재 노드를 닫힌 노드에 추가.
		//먼저 이미있는지확인.
		bool isNodeInList = false;
		for (Node* node : closedList)
		{
			if (*node == *currentNode)
			{
				isNodeInList == true;
				break;
			}
		}

		//방문 했으면 아래 단계 건너뛰기.
		if (isNodeInList == true)
		{
			continue;
		}

		//닫힌 목록에 현재 위치 추가.
		closedList.emplace_back(currentNode);

		//이웃 노드 방문하기.
		for (const Direction& direction : directions)
		{
			//다음에 이동할 위치 설정.
			int newX = currentNode->position.x + direction.x;
			int newY = currentNode->position.y + direction.y;

			if (IsInRange(newX, newY, grid) == false)
			{
				continue;
			}

			//옵션. 장애물인지 확인하기.
			//값이 1이면 장애물이라고 약속.
			if (grid[newY][newX] == 1)
			{
				continue;
			}

			//이미 방문했어도 무시.
			//이미 방문했는지 확인하는 함수 작성 후 호출.
			float gCost = currentNode->gCost + direction.cost;
			if (HasVisited(newX, newY, gCost))
			{
				continue;
			}

			Node* neighborNode = new Node(newX, newY, currentNode);
			neighborNode->gCost = currentNode->gCost + direction.cost;
			//Todo: 휴리스틱 비용 계산 함수 작성 후 호출
			neighborNode->hCost = CalilateHeuristic(neighborNode, goalNode);
			neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;

			//넣을지 말지 판단.

			Node* openListNode = nullptr;
			for (Node* node : openList)
			{
				if (*node == *neighborNode)
				{
					openListNode = node;
					break;
				}
			}

			//노드가 목록에 없거나 비용이 저렴하면 새 노드 추가.
			if (openListNode == nullptr
				|| openListNode->gCost > neighborNode->gCost
				|| openListNode->fCost > neighborNode->fCost
				)
			{
				openList.emplace_back(neighborNode);
			}
			else
			{
				SafeDelete(neighborNode);

			}
		}
	}

	return std::vector<Node*>();
}

std::vector<Node*> AStar::ConstructPath(Node* goalNode)
{
	//출력용 경로배열
	std::vector<Node*> path;
	Node* currentNode = goalNode;

	while(currentNode != nullptr)
	{
		path.emplace_back(currentNode);
		currentNode = currentNode->parent;
	}

	//이제 이 순서 뒤집어야됨.
	std::reverse(path.begin(), path.end());

	return path;
}

bool AStar::IsDestination(const Node* node)
{
	//노드가 목표 노드와 위치가 같은지 비교.
	return *node == *goalNode;
}

bool AStar::IsInRange(int x, int y, const std::vector<std::vector<int>>& grid)
{
	//x,y 범위가 벗어나면 실패
	if (x < 0 || y < 0 || x >= int(grid[0].size()) || y >= (int)grid.size())
	{
		//grid[0]은 x좌표의 한 줄이므로 이 줄의 크기는 x좌표의 크기와 동일함.
		return false;
	}

	return true;
}

bool AStar::HasVisited(int x, int y, float gCost)
{
	//열린 리스트나 닫힌 리스트에 이미 해당 노드가 있으면 방문한 것으로 판정.
	for (int ix = 0; ix < (int)openList.size(); ++ix)
	{
		Node* node = openList[ix];

		if (node->position.x == x && node->position.y == y)
		{
			//위치가 같고, 비용도 더 크면 방문할 이유가 없음.
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
			//위치가 같고, 비용도 높으면 방문할 이유 없음.
			if (node->gCost < gCost)
			{
				return true;
			}

			//위치는 같으나 비용이 작다면, 기존 노드 제거.
			else if(node->gCost > gCost)
			{
				closedList.erase(closedList.begin() + ix);
				SafeDelete(node);
			}
		}
	}

	//목록에 없다고 판단되면 방문하지 않은것으로 간주. false반환.
	return false;
}

float AStar::CalilateHeuristic(Node* currentNode, Node* goalNode)
{
	//단순 거리 계산으로 휴리스틱 비용으로 활용.
	Position diff = *currentNode - *goalNode;

	//대각선 길이 구하기.
	return (float)std::sqrt( (diff.x * diff.x) + (diff.y * diff.y) );
}
