#include <iostream>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int n, drink[10001], dp[3][10001];		// dp[0][i] : i번째 포도주를 안 마셨을 때 최대 양
										// dp[1][i] : i - 1번째는 마시지 않고 i번째만 마셨을 때 최대 양
int main()								// dp[2][i] : i - 1번째와 i번째 모두 마셨을 때 최대 양
{
	FAST;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> drink[i];
	
	dp[1][1] = dp[2][1] = drink[1];
	for (int i = 2; i <= n; i++) {
		dp[0][i] = max(max(dp[0][i - 1], dp[1][i - 1]), dp[2][i - 1]);	// dp[0][i - 1] ~ dp[2][i - 1] 3개 중 최댓값
		dp[1][i] = dp[0][i - 1] + drink[i];						// i - 1번째 포도주를 마시지 않았을 때 최대 양 + drink[i]
		dp[2][i] = dp[1][i - 1] + drink[i];						// i - 2번째는 마시지 않고 i - 1번째를 마신 상태에서의 최대 양 + drink[i]
	}
	cout << max(max(dp[0][n], dp[1][n]), dp[2][n]);
	return 0;
}