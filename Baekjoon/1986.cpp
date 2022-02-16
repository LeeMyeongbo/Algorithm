#include <iostream>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int n, m, queen, q[2][100], knight, k[2][100], pawn, p[2][100], ans;
const int dr[][4] = { 0, 1, 0, -1, -1, 1, 1, -1 }, dc[][4] = { 1, 0, -1, 0, 1, 1, -1, -1 };
char map[1000][1001];			// 퀸, 나이트, 폰 위치 체크
bool danger[1000][1000];		// 위험한 곳 체크

void Solve()
{
	for (int i = 0; i < queen; i++) {
		danger[q[0][i]][q[1][i]] = true;
		for (int c = 0; c < 2; c++) {
			for (int d = 0; d < 4; d++) {
				int R = q[0][i] + dr[c][d];
				int C = q[1][i] + dc[c][d];
				while (R >= 0 && R < n && C >= 0 && C < m && !map[R][C]) {		// 8방향으로 움직이며 빈 칸 있으면 최대한 표시
					danger[R][C] = true;
					R += dr[c][d], C += dc[c][d];
				}
			}
		}
	}
	for (int i = 0; i < knight; i++) {
		danger[k[0][i]][k[1][i]] = true;
		for (int c = 0; c < 4; c++) {
			for (int d = c; d < c + 2; d++) {
				int R = k[0][i] + dr[0][c] + dr[1][d % 4];
				int C = k[1][i] + dc[0][c] + dc[1][d % 4];
				if (R >= 0 && R < n && C >= 0 && C < m && !map[R][C])			// 장애물 건너뛸 수 있다고 했으니 뭐
					danger[R][C] = true;
			}
		}
	}
	for (int i = 0; i < pawn; i++)
		danger[p[0][i]][p[1][i]] = true;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (!danger[i][j])
				ans++;
}

int main()
{
	FAST;
	cin >> n >> m;
	cin >> queen;
	for (int i = 0; i < queen; i++) {
		cin >> q[0][i] >> q[1][i];
		map[--q[0][i]][--q[1][i]] = 'q';
	}
	cin >> knight;
	for (int i = 0; i < knight; i++) {
		cin >> k[0][i] >> k[1][i];
		map[--k[0][i]][--k[1][i]] = 'k';
	}
	cin >> pawn;
	for (int i = 0; i < pawn; i++) {
		cin >> p[0][i] >> p[1][i];
		map[--p[0][i]][--p[1][i]] = 'p';
	}

	Solve();
	cout << ans;
	return 0;
}