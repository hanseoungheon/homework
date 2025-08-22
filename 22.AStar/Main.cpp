#include <iostream>
#include <vector>

#include "Node.h"
#include "AStar.h"

int main()
{
    // �׸��� ����.
    // 0: �̵� ����.
    // 1: �̵� �Ұ�(��ֹ�).
    // 2: ���� ��ġ.
    // 3: ��ǥ ��ġ.
    std::vector<std::vector<int>> grid =
    {
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 1 },
        { 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
        { 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
        { 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
        { 1, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    };

    // �ʿ��� ���� ��ġ�� ��ǥ��ġ �˻� �� ��� ����.
    Node* startNode = nullptr;
    Node* goalNode = nullptr;

    bool hasInitialized = false;
    for (int x = 0; x < grid[0].size(); ++x)
    {
        if (startNode != nullptr && goalNode != nullptr)
        {
            hasInitialized = true;
            break;
        }

        for (int y = 0; y < grid.size(); ++y)
        {
            if (startNode != nullptr && goalNode != nullptr)
            {
                hasInitialized = true;
                break;
            }

            if (grid[y][x] == 2)
            {
                startNode = new Node(x, y);
                grid[y][x] = 0;
                continue;
            }

            if (grid[y][x] == 3)
            {
                goalNode = new Node(x, y);
                grid[y][x] = 0;
                continue;
            }
        }

        if (hasInitialized)
        {
            break;
        }
    }

    // ��ü ����.
    AStar aStar;

    // ��� Ž��.
    std::vector<Node*> path = aStar.FindPath(startNode, goalNode, grid);

    // ��� Ž���� ������ ��� ���� ���� ���.
    if (!path.empty())
    {
        std::cout << "��θ� ã�ҽ��ϴ�. �ִ� ���:\n";
        for (Node* node : path)
        {
            std::cout <<
                "(" << 
                node->position.x << ", " 
                << node->position.y 
                << ") -> ";
        }
        std::cout << "��ǥ ����\n";

        // ��� Ž�� ��� 2���� �� ���.
        std::cout << "��θ� �ʿ� ǥ���� ���:\n";
        aStar.DisplayGridWithPath(grid, path);
    }

    // ��� Ž���� ����.
    else
    {
        std::cout << "��θ� ã�� ���߽��ϴ�.\n";
    }

    // �޸� ����.
    SafeDelete(goalNode);
}