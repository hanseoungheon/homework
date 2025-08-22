#include <iostream>
#include <vector>
#include <Windows.h>

#include "Node.h"
#include "AStar.h"

// �ʿ��� ����/��ǥ ��带 �˻��� �����ϴ� �Լ�.
void FindStartAndGoalNode(std::vector<std::vector<int>>& grid, Node** outStartNode, Node** outGoalNode);

int main()
{
    // �ܼ� ���߱�.
    CONSOLE_CURSOR_INFO info = { };
    info.dwSize = 1;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

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

    // ���� ��ġ�� ��ǥ��ġ ���.
    Node* startNode = nullptr;
    Node* goalNode = nullptr;

    // �ʿ��� ���� ��ġ�� ��ǥ��ġ �˻� �� ��� ����.
    FindStartAndGoalNode(grid, &startNode, &goalNode);

    // A* ��ü ����.
    AStar aStar;

    // ��� Ž��.
    std::vector<Node*> path = aStar.FindPath(startNode, goalNode, grid);

    // ��� Ž���� ������ ��� ���� ���� ���.
    if (!path.empty())
    {
        std::cout << "\n��θ� ã�ҽ��ϴ�.\n�ִ� ���:\n";
        for (const Node* node : path)
        {
            std::cout << "(" << node->position.x << ", " << node->position.y << ") -> ";
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

    // �ܼ� ���̱�.
    info.bVisible = true;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    // �ܼ� Ŀ�� �̵� (���� �� ��¿� ���ص��� �ʵ���).
    COORD position{ 0, 30 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
    std::cin.get();
}

void FindStartAndGoalNode(std::vector<std::vector<int>>& grid, Node** outStartNode, Node** outGoalNode)
{
    bool hasInitialized = false;
    for (int x = 0; x < grid[0].size(); ++x)
    {
        if (*outStartNode != nullptr && *outGoalNode != nullptr)
        {
            hasInitialized = true;
            break;
        }

        for (int y = 0; y < grid.size(); ++y)
        {
            if (*outStartNode != nullptr && *outGoalNode != nullptr)
            {
                hasInitialized = true;
                break;
            }

            if (grid[y][x] == 2)
            {
                *outStartNode = new Node(x, y);
                continue;
            }

            if (grid[y][x] == 3)
            {
                *outGoalNode = new Node(x, y);
                continue;
            }
        }
    }
}