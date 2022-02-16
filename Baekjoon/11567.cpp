#include <iostream>
#include <queue>
using namespace std;

int N, M, start_r, start_c, end_r, end_c;
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
char map[500][501];
bool visited[500][500], moved;			// moved : 움직였는지 여부
queue<pair<int, int>> q;

bool BFS()
{
	q.push({ start_r, start_c });
	if (start_r != end_r || start_c != end_c)
		map[start_r][start_c] = '.';			// 출발점과 도착점이 같지 않다면 출발점을 '.'으로 바꾸고 출발!
	visited[start_r][start_c] = true;

	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();

		if (cur.first == end_r && cur.second == end_c && moved) {	// 최소 한 번 이상 움직여야 yes가 나올 수 있음
			if (map[end_r][end_c] == 'X')
				return true;

			int cnt = 0;
			for (int d = 0; d < 4; d++) {
				int R = end_r + dr[d];
				int C = end_c + dc[d];
				if (R >= 0 && R < N && C >= 0 && C < M && map[R][C] == '.')
					cnt++;
			}
			if (cnt >= 2)				// 도착점 주위에 '.'이 2개 이상 있으면 무적권 가능
				return true;

			break;
		}

		for (int d = 0; d < 4; d++) {
			int R = cur.first + dr[d];
			int C = cur.second + dc[d];
			if (R >= 0 && R < N && C >= 0 && C < M) {
				if (R == end_r && C == end_c) {			// 도착점이라면 무조건 큐에 삽입
					moved = true;						// 움직였다는 표시
					q.push({ R, C });
				}
				else if (!visited[R][C] && map[R][C] == '.') {
					visited[R][C] = true;
					moved = true;
					q.push({ R, C });
				}
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