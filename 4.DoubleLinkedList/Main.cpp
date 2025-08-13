
#include "PreCompiledHeader.h"

#include <iostream>
#include "LinkedList.h"

int main()
{
	LinkedList<int> list;

	//������ �Է� ����
	char input[50] = {};

	//�߰�? -> �����о�ͼ� �߰�
	FILE* file = nullptr;

	fopen_s(&file, "Input.txt", "rt");
	//fseek(file,)
	if (file == nullptr)
	{
		//cerr ���� ���
		std::cerr << "������ ���� ���߽��ϴ�.\n";
		return -1;
	}

	fseek(file, 0, SEEK_END);
	int fileSize = ftell(file);
	rewind(file);

	char* buffer = new char[fileSize + 1];
	memset(buffer, 0, sizeof(char) * (fileSize + 1));
	size_t sizeRead = fread(buffer, sizeof(char), fileSize + 1, file);

	char* context = nullptr;
	char* data = strtok_s(buffer, " ", &context);

	while (data)
	{
		if (data && atoi(data))
		{
			list.PushLast(atoi(data));
		}

		data = strtok_s(nullptr, " ", &context);
	}
	delete[] buffer;

	
	fclose(file);

	list.Print();
	//	while (true)
	//	{
	//		std::cout << "�߰��� �����͸� �Է��ϼ���";
	//		std::cin >> input;
	//
	//		if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
	//		{
	//			break;
	//		}
	//
	//		if (atoi(input) == false)
	//		{
	//			std::cout << "���ڸ� �Է� �����մϴ�.";
	//			continue;
	//		}
	//
	//		list.PushLast(atoi(input));
	//		list.Print();
	//	}
	//}

	return 0;
}