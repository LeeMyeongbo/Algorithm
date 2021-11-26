#include <iostream>
using namespace std;

int N, map[50][50], k, ans = -1;

void DFS(int depth, int Max)							// depth :  현재 재귀 깊이, Max : 최대 가능한 깊이
{
	if (depth < Max) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				for (int tile = 0; tile < 6; tile++) {
					if (tile != map[i][j]) {			// k = 1일 때 무조건 타일을 다른 걸로 바꿔야 하므로 이 조건 중요!!
						int tmp = map[i][j];
						map[i][j] = tile;
						DFS(depth + 1, Max);
						map[i][j] = tmp;				// 항상 재귀가 끝나면 타일을 원래대로 복구해야 함
					}
				}
			}
		}
	}
	else {
		if (map[0][0] != 1 && map[0][0] != 5)			// 맨 처음 진입할 때 1 또는 5가 아니면 절대 끝까지 못감 ㅅㄱ
			return;

		int R = 0, C = 0, move = 1, dir = 0;	// move : 움직인 횟수, dir : 현재 바라보고 있는 방향 (0 : 동, 1 : 서, 2 : 남, 3 : 북)
		bool flag = true;

		while (flag) {							// 여기서부턴 빡구현...실수하지 않도록 존나 조심해야함
			if (map[R][C] == 0) {
				if (dir == 3 && C + 1 < N && map[R][C + 1] != 0 && map[R][C + 1] != 2 && map[R][C + 1] != 4)
					dir = 0, C++, move++;
				else if (dir == 1 && R + 1 < N && map[R + 1][C] != 0 && map[R + 1][C] != 1 && map[R + 1][C] != 5)
					dir = 2, R++, move++;
				else
					flag = false;				// 더 이상 진행을 못하게 되면 flag = false
			}
			else if (map[R][C] == 1) {
				if (dir == 0 && R + 1 < N && map[R + 1][C] != 0 && map[R + 1][C] != 1 && map[R + 1][C] != 5)
					dir = 2, R++, move++;
				else if (dir == 3 && C - 1 >= 0 && map[R][C - 1] != 1 && map[R][C - 1] != 3 && map[R][C - 1] != 4)
					dir = 1, C--, move++;
				else
					flag = false;
			}
			else if (map[R][C] == 2) {
				if (dir == 2 && C + 1 < N && map[R][C + 1] != 0 && map[R][C + 1] != 2 && map[R][C + 1] != 4)
					dir = 0, C++, move++;
				else if (dir == 1 && R - 1 >= 0 && map[R - 1][C] != 2 && map[R - 1][C] != 3 && map[R - 1][C] != 5)
					dir = 3, R--, move++;
				else
					flag = false;
			}
			else if (map[R][C] == 3) {
				if (dir == 0 && R - 1 >= 0 && map[R - 1][C] != 2 && map[R - 1][C] != 3 && map[R - 1][C] != 5)
					dir = 3, R--, move++;
				else if (dir == 2 && C - 1 >= 0 && map[R][C - 1] != 1 && map[R][C - 1] != 3 && map[R][C - 1] != 4)
					dir = 1, C--, move++;
				else
					flag = false;
			}
			else if (map[R][C] == 4) {
				if (dir == 3 && R - 1 >= 0 && map[R - 1][C] != 2 && map[R - 1][C] != 3 && map[R - 1][C] != 5)
					R--, move++;
				else if (dir == 2 && R + 1 < N && map[R + 1][C] != 0 && map[R + 1][C] != 1 && map[R + 1][C] != 5)
					R++, move++;
				else
					flag = false;
			}
			else {
				if (dir == 0 && C + 1 < N && map[R][C + 1] != 0 && map[R][C + 1] != 2 && map[R][C + 1] != 4)
					C++, move++;
				else if (dir == 1 && C - 1 >= 0 && map[R][C - 1] != 1 && map[R][C - 1] != 3 && map[R][C - 1] != 4)
					C--, move++;
				else
					flag = false;
			}
		}
		if (R == N - 1 && C == N - 1 && (map[R][C] == 2 || map[R][C] == 5)) {		// 끝에 도달하고 오른쪽으로 나갈 수 있다면
			if (ans == -1)
				ans = move;
			ans = ans > move ? move : ans;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N >> k;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];

	DFS(0, k);			// 문제 정확히 읽기... 최대 k개가 아니라 정확히 k개라 했음
	
	cout << ans;
	return 0;
}