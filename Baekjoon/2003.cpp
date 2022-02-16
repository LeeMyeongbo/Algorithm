#include <iostream>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, A[10000];

int Solve()
{
	int left = 0, right = 1, sum = A[left], ans = 0;

	while (right < N && left < N) {		// left = right 인 지점 -> sum이 0인 상태
		if (sum < M)
			sum += A[right++];
		else {
			if (sum == M)
				ans++;
			sum -= A[left++];
		}
	}
	while (left < N) {					// 남은 left 오른쪽으로 마저 이동하며 확인
		if (sum == M)
			ans++;
		sum -= A[left++];
	}

	return ans;
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