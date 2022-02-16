#include <iostream>
#include <queue>
using namespace std;

int N, M, start_r, start_c, end_r, end_c, dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
char map[500][501];
queue<pair<int, int>> q;

bool BFS()
{
	q.push({ start_r, start_c });

	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();

		for (int d = 0; d < 4; d++) {
			int R = cur.first + dr[d];
			int C = cur.second + dc[d];
			if (R < 0 || R >= N || C < 0 || C >= M)
				continue;

			if (R == end_r && C == end_c) {			// 목표 지점에 도착할 경우
				if (map[R][C] == 'X')				// 'X'라면 바로 종료
					return true;
				else {
					map[R][C] = 'X';				// '.'라면 'X'로 바꾸고 큐 삽입
					q.push({ R, C });
				}
			}
			else if (map[R][C] != 'X') {			// 목표 지점이 아닌 '.'에 도달 시
				map[R][C] = 'X';
				q.push({ R, C });					// 'X'로 바꾸고 큐 삽입
			}
		}
	}
	return false;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> M;

	for (int i = 0; i < N; i++)
		cin >> map[i];
	cin >> start_r >> start_c >> end_r >> end_c;
	start_r--, start_c--, end_r--, end_c--;

	if (BFS())
		cout << "YES";
	else
		cout << "NO";

	return 0;
}