#pragma once

#include "Node.h"

class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    //ù ��忡 ������ �߰�
    //��尡 ��������� Head����
    //��尡 ������ Head ��ü
    void AddToHead(int newData);

    //�� �ڿ� ��� �߰�
    void Insert(int newData);

    //��� ����
    void Delete(int data);

    //��� ���
    void Print();

    int Count() const { return count; }

    //����
    void MyNodeSort();

    int GetCount() const;

    //int operator=(Node* noding)
    //{
    //    if (noding != nullptr)
    //        int a = *noding;
    //}
private:
    // Head ���.
    Node* head = nullptr;

    // ���� ����Ʈ�� ����� ����� ��.
    int count = 0;
};