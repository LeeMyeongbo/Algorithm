#include <iostream>
#include <time.h>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, map[100][100], dp[101][100][100];		// [0][i][j]�� ���� �ڸ� ����, [1][i][j]�� ���� �ڸ� ����... �̷� ������ ����
bool chk[100][100];								// ������ ������ �湮 ó��

void Add(int n1_r, int n1_c, int n2_r, int n2_c)	// ������ ���ϴ� ����
{
	int carry = 0;

	for (int r = 0; r <= 100; r++) {
		dp[r][n1_r][n1_c] += dp[r][n2_r][n2_c] + carry;
		if (dp[r][n1_r][n1_c] > 9) {
			dp[r][n1_r][n1_c] -= 10;
			carry = 1;
		}
		else
			carry = 0;
	}
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];

	dp[0][0][0] = 1, chk[0][0] = true;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!chk[i][j] || !map[i][j])
				continue;

			int R = i, C = j + map[i][j];
			if (C < N) {
				Add(R, C, i, j);		// ������ �� �ִ� ���� ���� (���� ��ġ�� ����� �� + ������ ��ġ�� ����� �� ���� ������ ��ġ�� ����)
				chk[R][C] = true;
			}

			R = i + map[i][j], C = j;
			if (R < N) {
				Add(R, C, i, j);
				chk[R][C] = true;
			}
		}
	}
	int s = 100;
	while (s > -1 && !dp[s][N - 1][N - 1])		// �� ���������� �����ؼ� ���ʷ� 0�� �ƴ� ���ڰ� ���� ������ �ݺ�
		s--;
	if (s == -1)								// ��� 0�̶�� 0 ���
		cout << 0;

	while (s > -1)
		cout << dp[s--][N - 1][N - 1];			// �׷��� ���� ��쿣 ������ ���

	return 0;
}