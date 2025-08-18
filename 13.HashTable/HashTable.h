#pragma once

#include <iostream>
#include <string>
#include "Pair.h"
#include "LinkedList.h"


class HashTable
{
	//Ÿ�� ������
	using Entry = TPair<std::string, std::string>;
	//Tpair�ε� ���ڿ��� ����ϴ°� Entry�� ������
public:
	HashTable();
	~HashTable();

	//�߰�.
	void Add(const std::string& key, const std::string& value);

	//����.
	void Delete(const std::string& key);

	//�˻�.
	bool Find(const std::string& key, Entry& outValue);

	//���.
	void Print();

	//������� Ȯ��.
	bool IsEmpty() const;
private:
	//��Ŷ ����
	static const int buckedCount = 19;

	//2�� �ڷᱸ�� Ȱ�� (ü�̴�)
	LinkedList<Entry> table[buckedCount] = {};
};





