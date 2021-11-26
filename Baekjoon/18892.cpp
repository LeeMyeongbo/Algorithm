#include <iostream>
#include <vector>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, A[1000], index[1000], reversed_index[1000], ans;
vector<int> lis, re_lis;

int Solve()
{
	lis.push_back(A[0]);
	for (int i = 1; i < N; i++) {			// A�� ���ʿ��� ���������� ���Ǹ� lis ���� �� �ε��� ����
		if (lis.back() < A[i]) {
			lis.push_back(A[i]);
			index[i] = lis.size() - 1;
		}
		else {
			int p = lower_bound(lis.begin(), lis.end(), A[i]) - lis.begin();
			lis[p] = A[i];
			index[i] = p;
		}
	}
	re_lis.push_back(A[N - 1]);
	for (int i = N - 2; i >= 0; i--) {		// A�� �����ʿ��� �������� ���Ǹ� lis ���� �� �ε��� ����
		if (re_lis.back() < A[i]) {
			re_lis.push_back(A[i]);
			reversed_index[i] = re_lis.size() - 1;
		}
		else {
			int p = lower_bound(re_lis.begin(), re_lis.end(), A[i]) - re_lis.begin();
			re_lis[p] = A[i];
			reversed_index[i] = p;
		}
	}
	for (int i = 0; i < N; i++)				// index + reversed_index�� �ִ� + 1�� ���� ������� ������ ����
		ans = max(ans, index[i] + reversed_index[i] + 1);
	return ans;
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