#pragma once
#include <iostream>
class Node
{

	//����� ���ϰ� ó���ϱ� ���� ������ �����ε�
	friend std::ostream& operator<<(std::ostream& os, const Node& node);
	friend class LinkedList;
private:
	Node();
	Node(int data);

	int GetData() const;
	void SetData(const int data);
private:
	//������ �ʵ�
	int data = 0;

	//��ũ �ʵ�
	Node* next = nullptr;

};

inline std::ostream& operator<<(std::ostream& os, const Node& node)
{
	return os << "Data: " << node.data;
}