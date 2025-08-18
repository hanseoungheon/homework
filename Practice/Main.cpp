#include <iostream>
#include "BinarySearchTree.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // 이진 탐색 트리 객체를 생성.
    BinarySearchTree<int> tree;

    // 이진 탐색 트리에 요소 삽입.
    tree.InsertNode(50);
    tree.InsertNode(30);
    tree.InsertNode(20);
    tree.InsertNode(40);
    tree.InsertNode(70);
    tree.InsertNode(60);
    tree.InsertNode(80);
    tree.InsertNode(100);
    tree.InsertNode(120);
    tree.InsertNode(130);
    tree.InsertNode(110);
    tree.InsertNode(150);
    tree.InsertNode(170);
    tree.InsertNode(140);

    // 전위 순회로 트리의 모든 요소를 출력.
    tree.PreorderTraverse();

    // 중위 순회로 트리의 모든 요소를 출력.
    tree.InorderTraverse();

    // 이진 탐색 트리에서 특정 키를 검색.
    int keyToSearch = 60;
    if (tree.SearchNode(keyToSearch) == true)
    {
        std::cout << "검색 성공: 트리에 " << keyToSearch << "이 있습니다.\n";
    }
    else
    {
        std::cout << "검색 실패: 트리에 " << keyToSearch << "이 없습니다.\n";
    }

    // 노드 삭제 예시.
    int keyToDelete = 30;
    tree.DeleteNode(keyToDelete);

    std::cout << "노드 " << keyToDelete << "삭제\n";
    tree.InorderTraverse();

    keyToDelete = 50;
    tree.DeleteNode(keyToDelete);
    std::cout << "노드 " << keyToDelete << "삭제\n";
    tree.InorderTraverse();

    keyToDelete = 60;
    tree.DeleteNode(keyToDelete);
    std::cout << "노드 " << keyToDelete << "삭제\n";
    tree.InorderTraverse();

    keyToDelete = 80;
    tree.DeleteNode(keyToDelete);
    std::cout << "노드 " << keyToDelete << "삭제\n";
    tree.InorderTraverse();

    keyToDelete = 20;
    tree.DeleteNode(keyToDelete);
    std::cout << "노드 " << keyToDelete << "삭제\n";
    tree.InorderTraverse();

    std::cin.get();
}