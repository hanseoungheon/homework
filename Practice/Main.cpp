//#include <iostream>
//
//#define ArraySize(array) sizeof(array) / sizeof(array[0])
//
//void PrintArray(int array[], int length)
//{
//	for (int ix = 0; ix < length; ++ix)
//	{
//		std::cout << array[ix];
//		if (ix < length - 1)
//		{
//			std::cout << ", ";
//		}
//	}
//
//	std::cout << "\n";
//
//}
//template<typename T>
//void Swap(T& a, T& b)
//{
//	T temp = a;
//	a = b;
//	b = temp;
//}
//int Partition(int* array, int left, int right)
//{
//	int pivot = array[left];
//	int low = left + 1;
//	int high = right;
//
//	while (low <= high) //교차할때 까지 반복!
//	{
//		while (low <= right && array[low] <= pivot)
//		{
//			++low;
//		}
//
//		while (high > left && array[high] >= pivot)
//		{
//			--high;
//		}
//
//		if (low > high) //교차시 루프 종료
//		{
//			break;
//		}
//
//		Swap<int>(array[low], array[high]);
//
//	}
//
//	Swap<int>(array[left], array[high]);
//
//	return high; //high이 차후 피벗이 됨.
//}
//
//void QuickSort(int* array, int left, int right)
//{
//	if (left >= right) //왼쪽이 오른쪽보다 큼 = 왼쪽이 오른쪽이 되고 오른쪽이 왼쪽이 됨. 교차!
//	{
//		return;
//	}
//
//	int pivot = Partition(array, left, right);
//
//	//왼쪽 재귀
//	QuickSort(array, left, pivot - 1);
//
//	//오른쪽 재귀
//	QuickSort(array, pivot + 1, right);
//}
//
//int main()
//{
//	int array[] =
//	{
//		1, 58, 10, 20, 56, 63, 73, 5, 28, 37,
//		80, 61, 82, 45, 11, 66, 83, 59, 22, 64,
//		52, 89, 94, 76, 44, 40, 75, 2, 23, 57,
//		92, 8, 41, 96, 15, 84, 35, 69, 54, 47,
//		90, 24, 43, 74, 34, 85, 72, 95, 18, 17,
//		98, 9, 29, 53, 27, 79, 39, 51, 31, 16,
//		6, 97, 26, 100, 21, 48, 33, 60, 91, 19,
//		30, 13, 71, 78, 87, 25, 81, 4, 42, 93,
//		49, 12, 14, 7, 62, 77, 38, 99, 88, 50,
//		32, 46, 70, 3, 86, 68, 36, 67, 55, 65
//	};
//
//	int length = (int)ArraySize(array);
//
//	//정렬전 출력
//	PrintArray(array, length);
//
//	//정렬
//	QuickSort(array, 0, length - 1);
//
//	//정렬 후 출력
//	std::cout << "\n";
//	PrintArray(array, length);
//
//	std::cin.get();
//}

#include <iostream>
#include <vector>
#include <string>
using namespace std;
string solution(long long n, vector<string> bans);
int main()
{
	//std::vector<char> vt = { 'a','b','c','d' };
	//std::cout << vt.at(2);
    vector<string> bans;

    bans.emplace_back("bans");
    bans.emplace_back("banana");
    bans.emplace_back("vasd");
    //bans.push_back()
    string code = solution(30, bans);

    std::cout << code;

}




//우선 문자열들을 담을 무언가가 필요함 a,b,c...z,aa,ab...az 이런거.
//굳이 동적배열로 해야하나? 음.. 해야할듯 아마? 아니다 둘다 쓰는걸로
//a부터 z까지 26개 이게 총 11글자까지 허용
//정확히는 각 하나의 요소마다 a부터 z까지 허용되는 최대 11글자의 문자열인것.
string solution(long long n, vector<string> bans) {
        char book[12] = { }; //최대 11글자까지지만 뒤에 NULL문자를 위해 한개 추가하기.
    //['a'] [] [] [] [] [] [] [] [] [] [], ['\0'] 
    //char[12] = '\0'; //굳이 안써도 되지만 찜찜해.

    vector<string> words; //개별적인 단어를 담을 리스트.

    int length = sizeof(book) / sizeof(book[0]); //크기 구하기.

    //다중 반복문 사용할거양 -> 이중으로는 안댈듯? 삼중?
    //일단 i는 자릿수로 쓰면 될듯?
    for (int i = 0; i < length - 1; ++i) //마지막 배열은 '\0'넣는데 쓸거임 
    {
        book[i] = 'a'; //매 i 반복마다 다음칸 알파벳 부여

        for (int t = 0; t < i; ++t)
        {
            if (book[t] == ('z' + 1))
                book[t] = 'a';
        } //만약 이전 요소들이 z + 1로 되어있다면 전부 a로 초기화.


        while (book[0] != ('z' + 1)) //만약 반복문에서 z인상태로 ++ 되면 종료
        {
            for (int k = 1; k < i + 1; ++k)
            {
                if (book[k] == ('z' + 1))
                {
                    book[k] = book[k] - 26;

                    if (i == 1)
                        book[0]++; //만약 i = 1이면 0번째만 b로증가
                    else
                    {
                        for (int u = 1; u < i + 1; ++u)
                        {
                            if (k - u >= 0)
                                book[k - u]++;
                            //아니면 뒤에거부터 하나씩 순차적으로 증가
                        }

                    }
                }
            }

            for (int l = 0; l <= (int)('z') - (int)('a'); ++l)
            {
                std::string temp = book; //string에 담아서
                bool banned = false;
                for (int m = 0; m < bans.size(); ++m) //순회 for문
                {
                    if (bans[m] == temp) //안에 든 금기주문하고 같으면 폭파시키기.
                    {//words vector에 추가형변환하기 싫엉
                        banned = true;
                        break;
                    }
                }

                if (!banned) {
                    words.emplace_back(temp);
                }
                book[i]++; //다 끝나고 다음 알파벳으로 가기

            }
        }

        //for (int j = 0; j < i + 1; ++j) //j는 현재 반복중인 단어자릿수?
        /*{*/
        //    for (int k = 0; k < j + 1 ++k)
        //    {
        //        if (a[k] == 'z')
        //        {
        //            a[k] = a[k] - 25;
        //
        //            if (k - 1 >= 0)
        //            {
        //                a[k - 1]++;
        //            }
        //        }
        //
        //    }
        //
        //    for (int l = 0; l < (int)('z') - (int)('a'); ++l)
        //    {
        //        std::string temp = book; //string에 담아서
        //
        //        for (int m = 0; m < bans.size(); ++m) //순회 for문
        //        {
        //            if (bans[m] != temp) //안에 든 금기주문하고 같으면 폭파시키기.
        //            {//words vector에 추가형변환하기 싫엉
        //                words.emplace_back(temp); //금기주문 아닌것만 넣을거야     
        //            }
        //        }
        //        a[i]++; //다 끝나고 다음 알파벳으로 가기
        //    }
        //}

    }

    string answer = words.at(n);

    return answer;
}





