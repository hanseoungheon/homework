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
//	while (low <= high) //�����Ҷ� ���� �ݺ�!
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
//		if (low > high) //������ ���� ����
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
//	return high; //high�� ���� �ǹ��� ��.
//}
//
//void QuickSort(int* array, int left, int right)
//{
//	if (left >= right) //������ �����ʺ��� ŭ = ������ �������� �ǰ� �������� ������ ��. ����!
//	{
//		return;
//	}
//
//	int pivot = Partition(array, left, right);
//
//	//���� ���
//	QuickSort(array, left, pivot - 1);
//
//	//������ ���
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
//	//������ ���
//	PrintArray(array, length);
//
//	//����
//	QuickSort(array, 0, length - 1);
//
//	//���� �� ���
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




//�켱 ���ڿ����� ���� ���𰡰� �ʿ��� a,b,c...z,aa,ab...az �̷���.
//���� �����迭�� �ؾ��ϳ�? ��.. �ؾ��ҵ� �Ƹ�? �ƴϴ� �Ѵ� ���°ɷ�
//a���� z���� 26�� �̰� �� 11���ڱ��� ���
//��Ȯ���� �� �ϳ��� ��Ҹ��� a���� z���� ���Ǵ� �ִ� 11������ ���ڿ��ΰ�.
string solution(long long n, vector<string> bans) {
        char book[12] = { }; //�ִ� 11���ڱ������� �ڿ� NULL���ڸ� ���� �Ѱ� �߰��ϱ�.
    //['a'] [] [] [] [] [] [] [] [] [] [], ['\0'] 
    //char[12] = '\0'; //���� �Ƚᵵ ������ ������.

    vector<string> words; //�������� �ܾ ���� ����Ʈ.

    int length = sizeof(book) / sizeof(book[0]); //ũ�� ���ϱ�.

    //���� �ݺ��� ����Ұž� -> �������δ� �ȴ��? ����?
    //�ϴ� i�� �ڸ����� ���� �ɵ�?
    for (int i = 0; i < length - 1; ++i) //������ �迭�� '\0'�ִµ� ������ 
    {
        book[i] = 'a'; //�� i �ݺ����� ����ĭ ���ĺ� �ο�

        for (int t = 0; t < i; ++t)
        {
            if (book[t] == ('z' + 1))
                book[t] = 'a';
        } //���� ���� ��ҵ��� z + 1�� �Ǿ��ִٸ� ���� a�� �ʱ�ȭ.


        while (book[0] != ('z' + 1)) //���� �ݺ������� z�λ��·� ++ �Ǹ� ����
        {
            for (int k = 1; k < i + 1; ++k)
            {
                if (book[k] == ('z' + 1))
                {
                    book[k] = book[k] - 26;

                    if (i == 1)
                        book[0]++; //���� i = 1�̸� 0��°�� b������
                    else
                    {
                        for (int u = 1; u < i + 1; ++u)
                        {
                            if (k - u >= 0)
                                book[k - u]++;
                            //�ƴϸ� �ڿ��ź��� �ϳ��� ���������� ����
                        }

                    }
                }
            }

            for (int l = 0; l <= (int)('z') - (int)('a'); ++l)
            {
                std::string temp = book; //string�� ��Ƽ�
                bool banned = false;
                for (int m = 0; m < bans.size(); ++m) //��ȸ for��
                {
                    if (bans[m] == temp) //�ȿ� �� �ݱ��ֹ��ϰ� ������ ���Ľ�Ű��.
                    {//words vector�� �߰�����ȯ�ϱ� �Ⱦ�
                        banned = true;
                        break;
                    }
                }

                if (!banned) {
                    words.emplace_back(temp);
                }
                book[i]++; //�� ������ ���� ���ĺ����� ����

            }
        }

        //for (int j = 0; j < i + 1; ++j) //j�� ���� �ݺ����� �ܾ��ڸ���?
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
        //        std::string temp = book; //string�� ��Ƽ�
        //
        //        for (int m = 0; m < bans.size(); ++m) //��ȸ for��
        //        {
        //            if (bans[m] != temp) //�ȿ� �� �ݱ��ֹ��ϰ� ������ ���Ľ�Ű��.
        //            {//words vector�� �߰�����ȯ�ϱ� �Ⱦ�
        //                words.emplace_back(temp); //�ݱ��ֹ� �ƴѰ͸� �����ž�     
        //            }
        //        }
        //        a[i]++; //�� ������ ���� ���ĺ����� ����
        //    }
        //}

    }

    string answer = words.at(n);

    return answer;
}





