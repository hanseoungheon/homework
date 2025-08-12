#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> ITSA(const std::vector<int>& A, const std::vector<int>& B)
{
	std::vector<int> itsc_A_B;
	for (int i = 0; i < A.size(); ++i)
	{
		if ((i == 0 || A[i] != A[i - 1]) && std::binary_search(B.cbegin(), B.cend(), A[i])
		
	}
}

int main()
{

}