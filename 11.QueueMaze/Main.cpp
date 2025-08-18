#include <iostream>
#include <Windows.h>
#include "Queue.h"

// ��ǥ�� ��Ÿ���� Ŭ����.
class Vector2
{
public:
	Vector2(int x = 0, int y = 0)
		: x(x), y(y)
	{
	}

	// ��� ���Ǹ� ���� ������ �����ε�.
	friend std::ostream& operator<<(
		std::ostream& os,
		const Vector2& position)
	{
		return os << "(" << position.x << "," << position.y << ")";
	}

	int x = 0;
	int y = 0;
};

//// ���� ��.
//const size_t MAZE_SIZE = 6;
//
//// map[y][x];
//// s: ��������.
//// g: ��ǥ����.
//// 1: �̵��Ұ�.
//// 0: �̵�����.
//char map[MAZE_SIZE][MAZE_SIZE] =
//{
//	{'1','1','1','1','1','1'},
//	{'s','0','1','0','0','1'},
//	{'1','0','0','0','1','1'},
//	{'1','0','1','0','1','1'},
//	{'1','0','1','0','0','g'},
//	{'1','1','1','1','1','1'}
//};

const size_t MAZE_SIZE = 20;
char map[MAZE_SIZE][MAZE_SIZE] =
{
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1'},
	{'1', '0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
	{'1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1'},
	{'s', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '1', '1', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', 'g'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
};

// ������ ��ġ�� �̵� �������� Ȯ���ϴ� �Լ�.
// �Է��� ��(y), ��(x) ������.
bool IsValidLocation(int y, int  x)
{
	// ���� ó��.
	if (y < 0 || y >= MAZE_SIZE || x < 0 || x >= MAZE_SIZE)
	{
		return false;
	}

	// Ȯ��.
	return map[y][x] == '0' || map[y][x] == 'g';
}

// ȭ�� ����� �Լ�.
void ClearScreen()
{
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Ŀ�� ���߱�.
	CONSOLE_CURSOR_INFO info = {};
	info.dwSize = 1;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &info);

	// �ܼ� ��ġ ó������ �̵�.
	SetConsoleCursorPosition(handle, { 0, 0 });

	// ����/���� ��ο� ��ĭ ä���.
	for (int y = 0; y < MAZE_SIZE; ++y)
	{
		for (int x = 0; x < MAZE_SIZE; ++x)
		{
			std::cout << " ";
		}

		std::cout << "\n";
	}

	// �ܼ� ��ġ ó������ �̵�.
	SetConsoleCursorPosition(handle, { 0, 0 });
}

// ��ġ ��� �Լ�.
void PrintLocation(int playerX, int playerY, unsigned long delay)
{
	// �и�������(1/1000��) ������ CPU ����.
	Sleep(delay);

	// �ܼ� ȭ�� �����.
	ClearScreen();

	// �ʰ� �÷��̾� �׸���.
	for (int y = 0; y < MAZE_SIZE; ++y)
	{
		for (int x = 0; x < MAZE_SIZE; ++x)
		{
			// �÷��̾� ��ġ ���.
			if (x == playerX && y == playerY)
			{
				std::cout << "P ";
				continue;
			}

			// �������� �� �׸���.
			std::cout << map[y][x] << " ";
		}

		std::cout << "\n";
	}
}

int main()
{
	// ������ġ �˻�.
	int startX = 0;
	int startY = 0;

	for (int y = 0; y < MAZE_SIZE; ++y)
	{
		for (int x = 0; x < MAZE_SIZE; ++x)
		{
			std::cout << map[y][x] << " ";

			// ������ġ���� Ȯ��.
			if (map[y][x] == 's')
			{
				startX = x;
				startY = y;
			}
		}

		std::cout << "\n";
	}

	// ���� ��ġ���� Ž��.
	// ť�� ����.
	//Stack<Vector2> locationStack;
	Queue<Vector2> locationQueue;
	locationQueue.Enqueue(Vector2(startX, startY));

	// �̷� Ž��.
	while (!locationQueue.IsEmpty())
	{
		// ���� ��ġ ��ȯ(����� ����).
		Vector2 current;
		locationQueue.Dequeue(current);
		//std::cout << current << " ";

		// �ʰ� �÷��̾� ��ġ ���.
		PrintLocation(current.x, current.y, 500);

		// �����ߴ��� Ȯ��.
		if (map[current.y][current.x] == 'g')
		{
			std::cout << "\n�̷� Ž�� ����\n";

			std::cin.get();
			return 0;
		}

		// Ž�� �̾��.
		map[current.y][current.x] = '.';

		// ������ �̵��� ��ġ�� ���ÿ� ����.
		// �� �� ���� �켱������ ���ϱ� ����.
		// ��/��/��/�� ������ ť�� ����.
		// Ž�� ����: ��/��/��/�� ������ Ž��.

		// ��.
		if (IsValidLocation(current.y - 1, current.x))
		{
			locationQueue.Enqueue(Vector2(current.x, current.y - 1));
		}

		// ��.
		if (IsValidLocation(current.y + 1, current.x))
		{
			locationQueue.Enqueue(Vector2(current.x, current.y + 1));
		}

		// ��.
		if (IsValidLocation(current.y, current.x - 1))
		{
			locationQueue.Enqueue(Vector2(current.x - 1, current.y));
		}

		// ��.
		if (IsValidLocation(current.y, current.x + 1))
		{
			locationQueue.Enqueue(Vector2(current.x + 1, current.y));
		}
	}

	// ���� �����ϸ� Ž�� ����.
	std::cout << "\n�̷� Ž�� ����\n";
	std::cin.get();
}