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
	dp[0] = dp[1] = 1;						// ���� �Ǻ���ġ ������ long long ���� ��ƾ� �� (���� int�� �����ϱ� �׷� ��)
	for (int i = 2; i <= 40; i++)			// ���� �¼��� 1���� �þ ������
		dp[i] = dp[i - 1] + dp[i - 2];		// ���ο� ����� �ڱ� �ڸ��� �ɴ� ��� : dp[i - 1]����, �ڱ� �ڸ� x : dp[i - 2]����

	int n = 0, ans = 1;
	for (int i = 1; i <= N; i++) {			// VIP �¼����� �ڸ� ���� ������ dp���� �����ָ� �� (�����)
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