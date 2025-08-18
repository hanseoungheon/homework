#include "HashTable.h"
#include <iostream>

int main()
{
	//�ؽ����̺� ��ü ����
	HashTable TABLE;

	//�ǵ������� ������ �߰��ؼ� �浹 ����Ű��
	TABLE.Add("HSH", "010-4584-7880");
	TABLE.Add("HSH", "010-4584-7880");

	TABLE.Add("MSK", "010-7854-4986");
	TABLE.Add("SDS", "010-4986-8514");
	TABLE.Add("KTW", "010-2464-7374");
	TABLE.Add("ITH", "010-9487-9464");

	//���
	TABLE.Print();

	//�˻�
	TPair<std::string, std::string> find;

	if (TABLE.Find("HSH", find)) // �˻� ����
	{
		std::cout << "�˻���� : " << find.key << ", " << find.value << "\n";
	}
	
	//����
	TABLE.Delete("MSK");
	TABLE.Delete("SDS");
	TABLE.Delete("KTW");
	TABLE.Delete("KSD");

	TABLE.Print();

	std::cin.get();
}