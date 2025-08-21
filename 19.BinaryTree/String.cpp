#include "String.h"


String::String(const char* value)
{
	length = value == nullptr ? 0 : (int)strlen(value);

	if (value == nullptr)
	{
		return;
	}

	data = new char[length + 1];
	strcpy_s(data, length + 1, value);
}

String::String(const String& other) //���� ������
	:length(other.length)
{
	data = new char[other.length + 1];

	strcpy_s(data, length + 1, other.data);
}

String::String(String&& other) //�̵� ������
	: length(other.length)
{
	data = other.data;
	other.data = nullptr;
}

String::~String()
{
	if (data != nullptr)
	{
		delete[] data;
		data = nullptr;
	}
}

String& String::operator=(const String& other)
{
	length = other.length;

	data = new char[other.length + 1];

	strcpy_s(data, length + 1, other.data);

	return *this;
}

String& String::operator=(String&& other)
{
	length = other.length;
	data = other.data;
	other.data = nullptr;

	return *this;
}

bool String::operator==(const String& other)
{
	// ���ڿ� �� �Լ� Ȱ��.
	return strcmp(data, other.data) == 0;
}

String String::operator+(const String& other)
{
	// �� ���ڿ��� �Ķ���ͷ� ���޵� ���ڿ� ��ġ��.

	// �� ���ڿ��� ��ģ ���� �� ���ϱ�.
	size_t newLength = length + other.length;

	// ���� ���� Ȯ��.
	char* newString = new char[newLength + 1];

	// �� ���ڿ� ����.
	//strcpy_s(newString, length, data);
	memcpy(newString, data, length);

	// �Ķ���ͷ� ���޵� ���ڿ��� �̾ ����.
	//strcpy_s(newString + length, other.length + 1, other.data);
	//strcat_s(newString, newLength + 2, other.data);
	memcpy(newString + length, other.data, other.length);
	newString[newLength] = '\0';

	// ���ڿ� ��ü ����.
	String temp(newString);
	delete[] newString;

	return temp;
}

std::ostream& operator<<(std::ostream& os, const String& string)
{
	return os << string.data;
}
