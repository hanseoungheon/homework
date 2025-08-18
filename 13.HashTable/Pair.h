#pragma once

//키 타입과 밸류 타입을 템플릿으로 선언
template<typename Key, typename Value>
class TPair
{
public:
	TPair()
		: key(), value()
	{

	}

	TPair(const Key& key, const Value& value)
		:key(key), value(value)
	{

	}

	//비교 연산자 오버로딩. TPair끼리의 비교를 위한 작업 단순화
	bool operator==(const TPair<Key, Value>& other)
	{
		return (key == other.key) && (value == other.value);
	}

	bool operator!=(const TPair<Key, Value>& other)
	{
		return !(*this == other);
		//return (key != other.key) || (value != other.value);
	}

	bool operator>(const TPair<Key, Value>& other)
	{
		return key > other.key;
	}

	bool operator<(const TPair<Key, Value>& other)
	{
		return key < other.key;
	}

	bool operator>=(const TPair<Key, Value>& other)
	{
		return key >= other.key;
	}

	bool operator<=(const TPair<Key, Value>& other)
	{
		return key <= other.key;
	}


public:
	//키
	Key key;

	//벨류(값)
	Value value;
};