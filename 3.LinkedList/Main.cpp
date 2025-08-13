#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "LinkedList.h"
int main()
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	LinkedList list;

	char input[50] = {};

	//������ �߰� ����
	while (true)
	{
		std::cout << "�߰��� �����͸� �Է����ּ���(����� q)\n";
		std::cin >> input;

		if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
		{
			break;
		}

		//������ ����
		//����ó��.
		if (!atoi(input))
		{
			std::cout << "���ڸ� �Է°����մϴ�.\n";
			continue;
		}

		//������ ����
		list.Insert(atoi(input));

		//���
		list.Print();
	}

	while (true)
	{
		std::cout << "���� ī��Ʈ �� : " << list.Count() << "\n";	
		std::cout << "������������ ������ ���Ͻø� s, �ƴϸ� q�� �Է����ּ���.";
		std::cin >> input;
		if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
		{
			break;
		}

		if (strcmp(input, "s") == 0 || strcmp(input, "S") == 0)
		{
			list.MyNodeSort();
		}

		//list.Print();
	}
	
	//������ ���� ����
	while (true)
	{
		std::cout << "������ �����͸� �Է����ּ���(����� q)\n";
		std::cin >> input;



		if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
		{
			break;
		}

		//������ ����
		//����ó��.
		else if (!atoi(input))
		{
			std::cout << "���ڸ� �Է°����մϴ�.\n";
			continue;
		}

		//������ ����
		list.Delete(atoi(input));
		//���
		list.Print();
	}

	int a = 3;
	int b = 4;
	int& ref = a;
	ref = b;
	
	std::cin.get();
}