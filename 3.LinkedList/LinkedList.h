#pragma once

#include "Node.h"

class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    //첫 노드에 데이터 추가
    //노드가 비어있으면 Head생성
    //노드가 있으면 Head 교체
    void AddToHead(int newData);

    //맨 뒤에 노드 추가
    void Insert(int newData);

    //노드 삭제
    void Delete(int data);

    //노드 출력
    void Print();

    int Count() const { return count; }

    //과제
    void MyNodeSort();

    int GetCount() const;

    //int operator=(Node* noding)
    //{
    //    if (noding != nullptr)
    //        int a = *noding;
    //}
private:
    // Head 노드.
    Node* head = nullptr;

    // 연결 리스트에 저장된 요소의 수.
    int count = 0;
};