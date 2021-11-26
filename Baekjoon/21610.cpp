#include <iostream>
using namespace std;

int N, M, A[50][50], sd[100][2], Sum;		// sd[n][0] : ����, sd[n][1] : �����̴� Ƚ��
const int dr[] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 }, dc[] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
bool pre_move[50][50], post_move[50][50];	// pre_move : ���� �̵� ��, post_move : ���� �̵� ��

int Solve()
{
	pre_move[N - 1][0] = pre_move[N - 1][1] = pre_move[N - 2][0] = pre_move[N - 2][1] = true;

	for (int i = 0; i < M; i++) {
		for (int r = 0; r < N; r++)
			for (int c = 0; c < N; c++)
				post_move[r][c] = false;		// �ϴ� ���� �̵� �� ���¸� false�� �� �ʱ�ȭ����

		for (int r = 0; r < N; r++) {			// ���� �̵�
			for (int c = 0; c < N; c++) {
				if (!pre_move[r][c])
					continue;
				int R = r, C = c;
				for (int m = 0; m < sd[i][1]; m++) {
					R += dr[sd[i][0]];
					C += dc[sd[i][0]];
					if (R < 0) R += N;
					else if (R >= N) R -= N;
					if (C < 0) C += N;
					else if (C >= N) C -= N;
				}
				post_move[R][C] = true;
				A[R][C]++;
			}
		}

		for (int r = 0; r < N; r++) {			// �� ���� ��1��
			for (int c = 0; c < N; c++) {
				if (!post_move[r][c])
					continue;
				for (int d = 2; d <= 8; d = d + 2) {
					int R = r + dr[d];
					int C = c + dc[d];
					if (R >= 0 && R < N && C >= 0 && C < N && A[R][C])
						A[r][c]++;
				}
			}
		}

		for (int r = 0; r < N; r++) {			// ���� ����(pre_move�� ����� �ؾ� ��)
			for (int c = 0; c < N; c++) {
				if (!post_move[r][c] && A[r][c] > 1) {	// ���� �ִ� �ڸ��� �ƴϰ� �� ���� 2 �̻��� ��
					A[r][c] -= 2;
					pre_move[r][c] = true;
				}
				else
					pre_move[r][c] = false;
			}
		}
	}
	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
			Sum += A[r][c];

	return Sum;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
			cin >> A[r][c];

	for (int i = 0; i < M; i++)
		cin >> sd[i][0] >> sd[i][1];

	cout << Solve();
	return 0;
}