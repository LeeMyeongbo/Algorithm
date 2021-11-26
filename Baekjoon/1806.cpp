#include <iostream>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, S, arr[100000];

int Solve()
{
	int ans = N + 1, left = 0, right = 1, sum = arr[left];
	while (left < N && right < N) {
		if (sum < S)
			sum += arr[right++];
		else {
			ans = min(ans, right - left);
			sum -= arr[left++];
		}
	}
	while (left < N) {
		if (sum >= S)
			ans = min(ans, right - left);
		sum -= arr[left++];
	}
	return ans;
}

int main()
{
	FAST;
	cin >> N >> S;
	for (int i = 0; i < N; i++)
		cin >> arr[i];

	int a = Solve();
	if (a == N + 1)
		cout << 0;
	else
		cout << a;
	return 0;
}