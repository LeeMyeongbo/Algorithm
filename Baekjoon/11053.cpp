#include <iostream>
#include <vector>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, A[1000000];
vector<int> lis;

int Solve()
{
	lis.push_back(A[0]);

	for (int i = 1; i < N; i++) {
		if (lis.back() < A[i])
			lis.push_back(A[i]);		// A[i]�� lis�� �� ���� �ִ� ������ ũ�� �߰�
		else {							// �׷��� �ʴٸ� lowerbound �ڸ��� ���ڸ� A[i]�� ��ü
			int index = lower_bound(lis.begin(), lis.end(), A[i]) - lis.begin();
			lis[index] = A[i];
		}
	}
	return lis.size();
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> A[i];

	cout << Solve();
	return 0;
}