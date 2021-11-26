#include <iostream>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int n, drink[10001], dp[3][10001];		// dp[0][i] : i��° �����ָ� �� ������ �� �ִ� ��
										// dp[1][i] : i - 1��°�� ������ �ʰ� i��°�� ������ �� �ִ� ��
int main()								// dp[2][i] : i - 1��°�� i��° ��� ������ �� �ִ� ��
{
	FAST;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> drink[i];
	
	dp[1][1] = dp[2][1] = drink[1];
	for (int i = 2; i <= n; i++) {
		dp[0][i] = max(max(dp[0][i - 1], dp[1][i - 1]), dp[2][i - 1]);	// dp[0][i - 1] ~ dp[2][i - 1] 3�� �� �ִ�
		dp[1][i] = dp[0][i - 1] + drink[i];						// i - 1��° �����ָ� ������ �ʾ��� �� �ִ� �� + drink[i]
		dp[2][i] = dp[1][i - 1] + drink[i];						// i - 2��°�� ������ �ʰ� i - 1��°�� ���� ���¿����� �ִ� �� + drink[i]
	}
	cout << max(max(dp[0][n], dp[1][n]), dp[2][n]);
	return 0;
}