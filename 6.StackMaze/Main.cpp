#include <iostream>
#include "Stack.h"

//��ǥ�� ��Ÿ���� Ŭ����
class Vector2
{
public:
	Vector2(int x = 0, int y = 0) 
		: x(x), y(y)
	{

	}
	int x, y;

	//������ �����ε�
	friend std::ostream& operator<<(std::ostream& os, const Vector2& position)
	{
		return os << "(" << position.x << ", " << position.y << ")";
	}
};

//���� ��
const size_t MAZE_SIZE = 6;

//map[y][x]
//s: �������� g: ��ǥ����
//1: �̵� �Ұ�
//0: �̵� ����
char map[MAZE_SIZE][MAZE_SIZE] =
{
	{'1','1','1','1','1','1'},
	{'s','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','g'},
	{'1','1','1','1','1','1'}
};
// ������ ��ġ�� �̵� �������� Ȯ���ϴ� �Լ�
// �Է��� ��(y) ��(x) ����
bool IsValidLocation(int y, int x)
{
	if (y < 0 || y >= MAZE_SIZE || x < 0 || x >= MAZE_SIZE)
		return false;

	return map[y][x] == '0' || map[y][x] == 'g';
}

int main()
{
	//���� ��ġ �˻�
	int startY = 0;
	int startX = 0;

	for (int y = 0; y < MAZE_SIZE; ++y)
	{
		for (int x = 0; x < MAZE_SIZE; ++x)
		{
			std::cout << map[y][x] << " ";

			//���� ��ġ���� Ȯ��
			if (map[y][x] == 's')
			{
				startX = x;
				startY = y;
			}
		}
		std::cout << "\n";
	}

	//���� ��ġ���� Ž��
	//���ÿ� ����

	Stack<Vector2> locationStack;
	locationStack.Push(Vector2(startX, startY));

	while (!locationStack.IsEmpty())
	{
		//���� ��ġ ��ȯ
		Vector2 current = locationStack.Pop();
		std::cout << current << " ";

		if (map[current.y][current.x] == 'g')
		{
			std::cout << "\n�̷� Ž�� ����\n";

			std::cin.get();
			return 0;
		}
		//Ž�� �̾��
		map[current.y][current.x] = '.';

		//������ �̵��� ��ġ�� ���ÿ� ����
		//�̶� ���� �켱������ ���ϱ� ����
		// ��.��.��.��� ����
		//��
		if (IsValidLocation(current.y - 1, current.x))
		{
			locationStack.Push(Vector2(current.x, current.y-1));
		}
		//��
		if (IsValidLocation(current.y + 1, current.x))
		{
			locationStack.Push(Vector2(current.x, current.y+1));
		}
		//��
		if (IsValidLocation(current.y, current.x + 1))
		{
			locationStack.Push(Vector2(current.x + 1, current.y));
		}
		//��
		if (IsValidLocation(current.y, current.x - 1))
		{
			locationStack.Push(Vector2(current.x - 1, current.y));
		}
	}

	//���� ���� �� Ž�� ����
	std::cout << "\n�̷� Ž�� ����\n";
	std::cin.get();
}