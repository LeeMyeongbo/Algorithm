#include <iostream>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, map[32][32];
long long dp[3][32][32];		// [0][i][j] : ���� ������ ����, [1][i][j] : ���� ������ ����, [2][i][j] : �밢�� ������ ���·� ������ [i][j]

int main()
{
	FAST;
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];

	dp[0][0][1] = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 2; j < N; j++) {
			if (!map[i][j])												// ������ �ϴ� ������ ���� ���� ���
				dp[0][i][j] += dp[0][i][j - 1] + dp[2][i][j - 1];		// ���� ������ ���� or �밢�����κ��� �̵� ����
			if (i > 0 && !map[i][j])
				dp[1][i][j] += dp[1][i - 1][j] + dp[2][i - 1][j];		// ���� ������ ���� or �밢�����κ��� �̵� ����
			if (i > 0 && j > 0 && !map[i - 1][j] && !map[i][j - 1] && !map[i][j])
				dp[2][i][j] += dp[0][i - 1][j - 1] + dp[1][i - 1][j - 1] + dp[2][i - 1][j - 1];	// �밢�� ������ ��� �������κ��� �̵� ����
		}
	}
	cout << dp[0][N - 1][N - 1] + dp[1][N - 1][N - 1] + dp[2][N - 1][N - 1];
	return 0;
}