
#include "PreCompiledHeader.h"

#include <iostream>
#include "LinkedList.h"

int main()
{
	LinkedList<int> list;

	//데이터 입력 루프
	char input[50] = {};

	//추가? -> 파일읽어와서 추가
	FILE* file = nullptr;

	fopen_s(&file, "Input.txt", "rt");
	//fseek(file,)
	if (file == nullptr)
	{
		//cerr 에러 출력
		std::cerr << "파일을 읽지 못했습니다.\n";
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
	//		std::cout << "추가할 데이터를 입력하세요";
	//		std::cin >> input;
	//
	//		if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
	//		{
	//			break;
	//		}
	//
	//		if (atoi(input) == false)
	//		{
	//			std::cout << "숫자만 입력 가능합니다.";
	//			continue;
	//		}
	//
	//		list.PushLast(atoi(input));
	//		list.Print();
	//	}
	//}

	return 0;
}