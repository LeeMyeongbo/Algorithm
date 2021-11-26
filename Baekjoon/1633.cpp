#include <iostream>
#include <vector>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, A[1000];
vector<int> lds;

int Solve()								// A[i]�� �������� ������ �� ���� ���� �κ� ������ ���� ����
{
	lds.push_back(A[0]);
	for (int i = 1; i < N; i++) {
		if (A[i] <= lds.back()) {		// lower_bound�� �̿��� Ǯ�̹� ���!
			int index = lower_bound(lds.begin(), lds.end(), A[i]) - lds.begin();
			lds[index] = A[i];			// A �迭 �� ���� ���� lds�� ������ ������ ���� ��쿣 lower_bound ���ؼ� �� ��ġ�� ���� �� ����
		}
		else
			lds.push_back(A[i]);		// A �迭 �� ���� ���� lds�� ������ ������ ū ��쿣 �߰�
	}
	return lds.size();
}

int main()
{
	FAST;
	cin >> N;
	for (int i = N - 1; i >= 0; i--)
		cin >> A[i];

	cout << Solve();
	return 0;
}