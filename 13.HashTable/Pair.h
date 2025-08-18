#pragma once

//Ű Ÿ�԰� ��� Ÿ���� ���ø����� ����
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

	//�� ������ �����ε�. TPair������ �񱳸� ���� �۾� �ܼ�ȭ
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
	//Ű
	Key key;

	//����(��)
	Value value;
};