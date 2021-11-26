#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int A[5][5] = {
	0, 1, 1, 1, 0,
	0, 0, 1, 0, 0,
	0, 1, 0, 1, 0,
	1, 0, 0, 1, 0,
	0, 1, 0, 1, 0
};
int B[4][5][5], N = 5;

void rotation_test()
{
	cout << "anticlock_wise\n\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {					// ↙ : N-1에서 빼기, ↘ : 그대로
			B[0][i][j] = A[i][j];
			B[1][N - 1 - j][i] = A[i][j];
			B[2][N - 1 - i][N - 1 - j] = A[i][j];
			B[3][j][N - 1 - i] = A[i][j];
		}
	}
	for (int k = 0; k < 4; k++) {
		cout << k * 90 << "도 회전\n";
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++)
				cout << B[k][r][c] << " ";
			cout << "\n";
		}
		cout << "\n";
	}

	cout << "clock_wise\n\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {					// ↙ : 그대로, ↘ : N-1에서 빼기
			B[0][i][j] = A[i][j];
			B[1][j][N - 1 - i] = A[i][j];
			B[2][N - 1 - i][N - 1 - j] = A[i][j];
			B[3][N - 1 - j][i] = A[i][j];
		}
	}
	for (int k = 0; k < 4; k++) {
		cout << k * 90 << "도 회전\n";
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++)
				cout << B[k][r][c] << " ";
			cout << "\n";
		}
		cout << "\n";
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	rotation_test();
	return 0;
}