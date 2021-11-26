#include <iostream>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int K, N;
long long Lan[10000], sum, Left = 1, Right;

long long Solve()
{
	long long Result = 0;
	while (Left <= Right) {
		int n = 0;
		long long mid = (Left + Right) / 2;
		for (int i = 0; i < K; i++)
			n += Lan[i] / mid;
		if (n < N)
			Right = mid - 1;		// 필요한 개수보다 적게 나올 경우 길이를 좀 더 줄임
		else {						// 필요한 개수 이상이라면
			if (Result < mid)
				Result = mid;		// mid 최댓값 갱신
			Left = mid + 1;			// 길이를 늘임
		}
	}
	return Result;
}

int main()
{
	FAST;
	cin >> K >> N;
	for (int i = 0; i < K; i++) {
		cin >> Lan[i];
		sum += Lan[i];
		if (Right < Lan[i])
			Right = Lan[i];
	}
	cout << Solve();
	return 0;
}