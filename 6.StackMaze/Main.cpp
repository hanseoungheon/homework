#include <iostream>
#include "Stack.h"

//좌표를 나타내는 클래스
class Vector2
{
public:
	Vector2(int x = 0, int y = 0) 
		: x(x), y(y)
	{

	}
	int x, y;

	//연산자 오버로딩
	friend std::ostream& operator<<(std::ostream& os, const Vector2& position)
	{
		return os << "(" << position.x << ", " << position.y << ")";
	}
};

//작은 맵
const size_t MAZE_SIZE = 6;

//map[y][x]
//s: 시작지점 g: 목표지점
//1: 이동 불가
//0: 이동 가능
char map[MAZE_SIZE][MAZE_SIZE] =
{
	{'1','1','1','1','1','1'},
	{'s','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','g'},
	{'1','1','1','1','1','1'}
};
// 가려는 위치가 이동 가능한지 확인하는 함수
// 입력은 행(y) 열(x) 순서
bool IsValidLocation(int y, int x)
{
	if (y < 0 || y >= MAZE_SIZE || x < 0 || x >= MAZE_SIZE)
		return false;

	return map[y][x] == '0' || map[y][x] == 'g';
}

int main()
{
	//시작 위치 검색
	int startY = 0;
	int startX = 0;

	for (int y = 0; y < MAZE_SIZE; ++y)
	{
		for (int x = 0; x < MAZE_SIZE; ++x)
		{
			std::cout << map[y][x] << " ";

			//시작 위치인지 확인
			if (map[y][x] == 's')
			{
				startX = x;
				startY = y;
			}
		}
		std::cout << "\n";
	}

	//시작 위치부터 탐색
	//스택에 삽입

	Stack<Vector2> locationStack;
	locationStack.Push(Vector2(startX, startY));

	while (!locationStack.IsEmpty())
	{
		//현재 위치 반환
		Vector2 current = locationStack.Pop();
		std::cout << current << " ";

		if (map[current.y][current.x] == 'g')
		{
			std::cout << "\n미로 탐색 성공\n";

			std::cin.get();
			return 0;
		}
		//탐색 이어가기
		map[current.y][current.x] = '.';

		//앞으로 이동할 위치를 스택에 삽입
		//이때 방향 우선순위는 정하기 나름
		// 상.하.좌.우로 삽입
		//상
		if (IsValidLocation(current.y - 1, current.x))
		{
			locationStack.Push(Vector2(current.x, current.y-1));
		}
		//하
		if (IsValidLocation(current.y + 1, current.x))
		{
			locationStack.Push(Vector2(current.x, current.y+1));
		}
		//좌
		if (IsValidLocation(current.y, current.x + 1))
		{
			locationStack.Push(Vector2(current.x + 1, current.y));
		}
		//우
		if (IsValidLocation(current.y, current.x - 1))
		{
			locationStack.Push(Vector2(current.x - 1, current.y));
		}
	}

	//여기 도달 시 탐색 실패
	std::cout << "\n미로 탐색 실패\n";
	std::cin.get();
}