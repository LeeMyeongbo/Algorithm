#include <iostream>
using namespace std;

int N, map[100][100], cnt, Case;

int Solve()
{
	for (int r = N - 1; r >= 0; r--) {			// S극으로 이동하는 것은 맨 밑 자성체에서부터 시작해서 밑으로 최대한 내려가며 탐색
		for (int c = 0; c < N; c++) {
			if (map[r][c] == 1) {
				map[r][c] = 0;
				int R = r + 1;
				while (R < N && !map[R][c])		// 맵을 벗어나게 되거나 다른 자성체 만날 때까지 반복
					R++;
				if (R < N)
					map[R - 1][c] = 1;			// 다른 자성체 만났을 경우에는 바로 위에 위치시킴
			}
		}
	}
	for (int r = 0; r < N; r++) {				// N극으로 이동하는 것은 맨 위 자성체에서부터 시작해서 위로 최대한 올라가며 탐색
		for (int c = 0; c < N; c++) {
			if (map[r][c] == 2) {
				map[r][c] = 0;
				int R = r - 1;
				while (R >= 0 && !map[R][c])	// 맵을 벗어나게 되거나 다른 자성체 만날 때까지 반복
					R--;
				if (R >= 0)
					map[R + 1][c] = 2;			// 다른 자성체 만났을 경우에는 바로 아래에 위치시킴
			}
		}
	}
	int cur = 1;
	for (int c = 0; c < N; c++)
		for (int r = 0; r < N; r++) {			// ↓ 방향으로 탐색
			if (!map[r][c])
				continue;
			if (map[r][c] == 2 && cur == 1)		// 자성체가 N -> S로 바뀔 때만 교착상태 개수 증가
				cnt++;
			cur = map[r][c];
		}
	return cnt;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	while (true) {
		cin >> N;
		if (cin.eof())
			return 0;

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> map[i][j];

		cout << "#" << ++Case << " " << Solve() << endl;
		cnt = 0;
	}
}