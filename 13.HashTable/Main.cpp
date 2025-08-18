#include "HashTable.h"
#include <iostream>

int main()
{
	//해시테이블 객체 생성
	HashTable TABLE;

	//의도적으로 같은거 추가해서 충돌 일으키기
	TABLE.Add("HSH", "010-4584-7880");
	TABLE.Add("HSH", "010-4584-7880");

	TABLE.Add("MSK", "010-7854-4986");
	TABLE.Add("SDS", "010-4986-8514");
	TABLE.Add("KTW", "010-2464-7374");
	TABLE.Add("ITH", "010-9487-9464");

	//출력
	TABLE.Print();

	//검색
	TPair<std::string, std::string> find;

	if (TABLE.Find("HSH", find)) // 검색 성공
	{
		std::cout << "검색결과 : " << find.key << ", " << find.value << "\n";
	}
	
	//삭제
	TABLE.Delete("MSK");
	TABLE.Delete("SDS");
	TABLE.Delete("KTW");
	TABLE.Delete("KSD");

	TABLE.Print();

	std::cin.get();
}