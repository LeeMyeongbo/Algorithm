#include <iostream>
using namespace std;

int N;
char map[50][51];

int Find_rowMax(int r)						// r행에 해당하는 가로줄 내에서 똑같은 색깔의 최대 길이 구함
{
	int n = 1, ans = 1;
	for (int c = 1; c < N; c++) {
		if (map[r][c - 1] == map[r][c])
			ans = max(ans, ++n);
		else
			n = 1;
	}
	return ans;
}

int Find_colMax(int c)						// c열에 해당하는 세로줄 내에서 똑같은 색깔의 최대 길이 구함
{
	int n = 1, ans = 1;
	for (int r = 1; r < N; r++) {
		if (map[r - 1][c] == map[r][c])
			ans = max(ans, ++n);
		else
			n = 1;
	}
	return ans;
}

int Solve()
{
	int M = 0, M1 = 0, M2 = 0;
	for (int i = 0; i < N; i++) {			// 사탕 위치 교환 전 똑같은 색깔의 최대 길이 구해놓음
		M1 = max(M1, Find_rowMax(i));
		M2 = max(M2, Find_colMax(i));
		M = max(M1, M2);
	}

	M1 = M2 = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - 1; j++) {
			swap(map[i][j], map[i][j + 1]);		// i행 내에서 가로로 인접한 2개 교환하고 최대 길이 갱신
			M1 = max(Find_rowMax(i), max(Find_colMax(j), Find_colMax(j + 1)));
			swap(map[i][j], map[i][j + 1]);

			swap(map[j][i], map[j + 1][i]);		// i열 내에서 세로로 인접한 2개 교환하고 최대 길이 갱신
			M2 = max(Find_colMax(i), max(Find_rowMax(j), Find_rowMax(j + 1)));
			swap(map[j][i], map[j + 1][i]);

			int tmp = max(M1, M2);
			M = max(tmp, M);
		}
	}
	return M;
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> map[i];
	printf("%d", Solve());
	return 0;
}