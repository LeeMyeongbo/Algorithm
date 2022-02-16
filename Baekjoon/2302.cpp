#include <iostream>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, f, dp[41];
bool fix[41];

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> f;
		fix[f] = true;
	}
	dp[0] = dp[1] = 1;						// 원래 피보나치 수열은 long long 으로 잡아야 됨 (답이 int형 범위니까 그런 거)
	for (int i = 2; i <= 40; i++)			// 극장 좌석이 1개씩 늘어날 때마다
		dp[i] = dp[i - 1] + dp[i - 2];		// 새로운 사람이 자기 자리에 앉는 경우 : dp[i - 1]가지, 자기 자리 x : dp[i - 2]가지

	int n = 0, ans = 1;
	for (int i = 1; i <= N; i++) {			// VIP 좌석마다 자른 다음 각각의 dp값을 곱해주면 됨 (곱사건)
		if (!fix[i])
			n++;
		else {
			ans *= dp[n];
			n = 0;
		}
	}
	ans *= dp[n];

	cout << ans;
	return 0;
}