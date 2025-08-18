#include "HashTable.h"

//�ؽ� �Լ�(Hash Function)
//�Ķ���ͷ� ���޹��� Ű�� Ȱ���ؼ� �ؽ�(����)�� �����ϴ� �Լ�.
int GenerateKey(const std::string& keyString)
{
	//������ Ű ����
	int key = 0;

	for (int ix = 0; ix < (int)keyString.length(); ++ix)
	{
		//skey += keyString[ix] * (ix + 1);
		key = 31 * key + keyString[ix];

	}


	//���밪���� ��ȯ
	//�ε����� ����ϴµ� �ε����� ��ȯ�Ǿ���ϹǷ� ������ �ȵ�
	//�ֻ��� ��Ʈ�� 1�� �����Ǹ� ������ �Ǵ��ϱ� ����.
	return key < 0 ? -key : key; //std::abs(key) <= ���밪 �Լ�.
}

HashTable::HashTable()
{

}
HashTable::~HashTable()
{

}

//�߰�.
void HashTable::Add(const std::string& key, const std::string& value)
{
	//Ű ����
	int keyValue = GenerateKey(key);

	//��Ŷ �ε����� ��ȯ
	int bucketIndex = keyValue % buckedCount;

	//������ ���� ����Ʈ ��������
	LinkedList<Entry>& list = table[bucketIndex];

	//Ű�� ���� �� �������? ������� ������?
	for (int ix = 0; ix < (int)list.Count(); ++ix)
	{
		if (list[ix]->data.key == key)
		{
			std::cout << "�̹� ������ Ű�� ���� �����Ͱ� ����Ǿ� �ֽ��ϴ�.\n";
			return;
		}
	}

	//�ؽ����̺� �� �߰�
	list.PushLast(Entry(key, value));
}

//����.
void HashTable::Delete(const std::string& key)
{
	// ���� ������ 2�ܰ��� ���� ����.
	// 1. ã��.
	int keyValue = GenerateKey(key);

	int bucketIndex = keyValue % buckedCount;

	//����Ʈ ��������
	LinkedList<Entry>& list = table[bucketIndex];

	//������ Ű���� ���� ��Ƽ�� �˻�
	for (int ix = 0; ix < (int)list.Count(); ++ix)
	{
		// 2. ����.
		if (list[ix]->data.key == key)
		{
			list.Delete(list[ix]->data);
			std::cout << "�׸��� �����߽��ϴ�.\n";
			return;
		}
	}

	//���� ����
	std::cout << "������ �����͸� ã�� ���߽��ϴ�.\n";
}

//�˻�.
bool HashTable::Find(const std::string& key, Entry& outValue)
{
	int keyValue = GenerateKey(key);

	int bucketIndex = keyValue % buckedCount;

	//����Ʈ ��������
	LinkedList<Entry>& list = table[bucketIndex];

	//�˻��� �ʿ䰡 �ִ��� Ȯ��
	if (list.Count() == 0)
	{
		std::cout << "�ش� Ű�� �����͸� �˻����� ���߽��ϴ�.\n";
		return false;
	}

	//�˻�
	for (int ix = 0; ix < (int)list.Count(); ++ix)
	{
		//���� Ű�� ���� �����͸� ã������, 
		if (list[ix]->data.key == key)
		{
			//����� �Ķ���Ϳ� �� ���� �� true��ȯ(�˻� ���� ����)
			outValue= list[ix]->data;
			return true;
		}
	}

	std::cout << "�ش� Ű�� �����͸� �˻����� ���߽��ϴ�.\n";
	return false;
}

//���.
void HashTable::Print()
{
	for (int ix = 0; ix < buckedCount; ++ix)
	{
		if (table[ix].Count() == 0)
		{
			continue;
		}

		for (int jx = 0; jx < (int)table[ix].Count(); ++jx)
		{
			std::cout
				<< "Ű : " << table[ix][jx]->data.key
				<< " �� : " << table[ix][jx]->data.value
				<< "\n";
		}
	}
}

//������� Ȯ��.
bool HashTable::IsEmpty() const
{
	//���� ������ �� ��� �� ��� 0�̸� �������.
	int totalCount = 0;

	//���̺� ���� ���� ����Ʈ�� ��ȸ�ϸ鼭 �� ����Ʈ�� ����� ���� �ջ�.
	for (int ix = 0; ix < buckedCount; ++ix)
	{
		totalCount += (int)table[ix].Count();
	}

	//�ջ��� ����� 0�̸� �� ���� ����
	return totalCount == 0;
}