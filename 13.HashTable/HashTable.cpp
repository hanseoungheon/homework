#include "HashTable.h"

//해시 함수(Hash Function)
//파라미터로 전달받은 키를 활용해서 해시(숫자)를 생성하는 함수.
int GenerateKey(const std::string& keyString)
{
	//생성될 키 변수
	int key = 0;

	for (int ix = 0; ix < (int)keyString.length(); ++ix)
	{
		//skey += keyString[ix] * (ix + 1);
		key = 31 * key + keyString[ix];

	}


	//절대값으로 반환
	//인덱스로 써야하는데 인덱스로 변환되어야하므로 음수면 안됨
	//최상위 비트가 1로 설정되면 음수로 판단하기 때문.
	return key < 0 ? -key : key; //std::abs(key) <= 절대값 함수.
}

HashTable::HashTable()
{

}
HashTable::~HashTable()
{

}

//추가.
void HashTable::Add(const std::string& key, const std::string& value)
{
	//키 생성
	int keyValue = GenerateKey(key);

	//버킷 인덱스로 변환
	int bucketIndex = keyValue % buckedCount;

	//저장할 연결 리스트 가져오기
	LinkedList<Entry>& list = table[bucketIndex];

	//키가 같은 걸 허용할지? 허용하지 않을지?
	for (int ix = 0; ix < (int)list.Count(); ++ix)
	{
		if (list[ix]->data.key == key)
		{
			std::cout << "이미 동일한 키를 가진 데이터가 저장되어 있습니다.\n";
			return;
		}
	}

	//해시테이블에 값 추가
	list.PushLast(Entry(key, value));
}

//삭제.
void HashTable::Delete(const std::string& key)
{
	// 삭제 연산은 2단계의 복합 과정.
	// 1. 찾기.
	int keyValue = GenerateKey(key);

	int bucketIndex = keyValue % buckedCount;

	//리스트 가져오기
	LinkedList<Entry>& list = table[bucketIndex];

	//동일한 키값을 가진 데티어 검색
	for (int ix = 0; ix < (int)list.Count(); ++ix)
	{
		// 2. 삭제.
		if (list[ix]->data.key == key)
		{
			list.Delete(list[ix]->data);
			std::cout << "항목을 삭제했습니다.\n";
			return;
		}
	}

	//삭제 실패
	std::cout << "삭제할 데이터를 찾지 못했습니다.\n";
}

//검색.
bool HashTable::Find(const std::string& key, Entry& outValue)
{
	int keyValue = GenerateKey(key);

	int bucketIndex = keyValue % buckedCount;

	//리스트 가져오기
	LinkedList<Entry>& list = table[bucketIndex];

	//검색할 필요가 있는지 확인
	if (list.Count() == 0)
	{
		std::cout << "해당 키로 데이터를 검색하지 못했습니다.\n";
		return false;
	}

	//검색
	for (int ix = 0; ix < (int)list.Count(); ++ix)
	{
		//같은 키를 가진 데이터를 찾았으면, 
		if (list[ix]->data.key == key)
		{
			//출력할 파라미터에 값 저장 후 true반환(검색 성공 판정)
			outValue= list[ix]->data;
			return true;
		}
	}

	std::cout << "해당 키로 데이터를 검색하지 못했습니다.\n";
	return false;
}

//출력.
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
				<< "키 : " << table[ix][jx]->data.key
				<< " 값 : " << table[ix][jx]->data.value
				<< "\n";
		}
	}
}

//비었는지 확인.
bool HashTable::IsEmpty() const
{
	//누적 데이터 수 계산 후 모두 0이면 비어있음.
	int totalCount = 0;

	//태이블 안의 연결 리스트를 순회하면서 각 리스트의 요수의 수를 합산.
	for (int ix = 0; ix < buckedCount; ++ix)
	{
		totalCount += (int)table[ix].Count();
	}

	//합산한 결과가 0이면 빈 상태 맞음
	return totalCount == 0;
}