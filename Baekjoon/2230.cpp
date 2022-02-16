#include <iostream>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, A[100000];

int Solve()
{
	sort(A, A + N);
	int left = 0, right = 1, gap = 2100000000;

	while (left < N && right < N) {
		if (A[right] - A[left] >= M)
			gap = min(gap, A[right] - A[left++]);
		else
			right++;
	}
	while (left < N) {
		if (A[right] - A[left] >= M)
			gap = min(gap, A[right] - A[left]);
		left++;
	}
	return gap;
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		cin >> A[i];

	cout << Solve();
	return 0;
}