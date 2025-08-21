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

String::String(const String& other) //복사 생성자
	:length(other.length)
{
	data = new char[other.length + 1];

	strcpy_s(data, length + 1, other.data);
}

String::String(String&& other) //이동 생성자
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
	// 문자열 비교 함수 활용.
	return strcmp(data, other.data) == 0;
}

String String::operator+(const String& other)
{
	// 내 문자열과 파라미터로 전달된 문자열 합치기.

	// 두 문자열을 합친 문자 수 구하기.
	size_t newLength = length + other.length;

	// 저장 공간 확보.
	char* newString = new char[newLength + 1];

	// 내 문자열 복사.
	//strcpy_s(newString, length, data);
	memcpy(newString, data, length);

	// 파라미터로 전달된 문자열을 이어서 복사.
	//strcpy_s(newString + length, other.length + 1, other.data);
	//strcat_s(newString, newLength + 2, other.data);
	memcpy(newString + length, other.data, other.length);
	newString[newLength] = '\0';

	// 문자열 객체 생성.
	String temp(newString);
	delete[] newString;

	return temp;
}

std::ostream& operator<<(std::ostream& os, const String& string)
{
	return os << string.data;
}
