#include <iostream>
#include <time.h>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, map[100][100], dp[101][100][100];		// [0][i][j]에 일의 자리 숫자, [1][i][j]에 십의 자리 숫자... 이런 식으로 저장
bool chk[100][100];								// 점프한 곳에는 방문 처리

void Add(int n1_r, int n1_c, int n2_r, int n2_c)	// 실제로 더하는 연산
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
				Add(R, C, i, j);		// 점프할 수 있는 곳은 더함 (현재 위치의 경로의 수 + 점프한 위치의 경로의 수 값을 점프한 위치에 저장)
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
	while (s > -1 && !dp[s][N - 1][N - 1])		// 맨 끝에서부터 시작해서 최초로 0이 아닌 숫자가 나올 때까지 반복
		s--;
	if (s == -1)								// 모두 0이라면 0 출력
		cout << 0;

	while (s > -1)
		cout << dp[s--][N - 1][N - 1];			// 그렇지 않은 경우엔 역으로 출력

	return 0;
}