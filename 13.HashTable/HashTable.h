#pragma once

#include <iostream>
#include <string>
#include "Pair.h"
#include "LinkedList.h"


class HashTable
{
	//타입 재정의
	using Entry = TPair<std::string, std::string>;
	//Tpair인데 문자열을 사용하는걸 Entry로 재정의
public:
	HashTable();
	~HashTable();

	//추가.
	void Add(const std::string& key, const std::string& value);

	//삭제.
	void Delete(const std::string& key);

	//검색.
	bool Find(const std::string& key, Entry& outValue);

	//출력.
	void Print();

	//비었는지 확인.
	bool IsEmpty() const;
private:
	//버킷 정의
	static const int buckedCount = 19;

	//2차 자료구조 활용 (체이닝)
	LinkedList<Entry> table[buckedCount] = {};
};





