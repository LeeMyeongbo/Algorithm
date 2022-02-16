#include <iostream>
#include <queue>
using namespace std;

struct Node {
	bool sua;		// 현재 움직이는 게 수아인지 해적인지
	int r, c;
};
int N, M, start_r, start_c, pirate_r, pirate_c, visited[700][700];	// visited[r][c] : 수아는 1로, 해적 및 해적이 바라보는 칸은 2로 저장
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
char map[700][701];
bool pirate_visited[700][700];		// 해적도 이동하므로 해적용 방문 체크용 배열 선언
queue<Node> q;

bool Solve()
{
	q.push({ true, start_r, start_c });
	visited[start_r][start_c] = 1;
	q.push({ false, pirate_r, pirate_c });
	visited[pirate_r][pirate_c] = 2;
	pirate_visited[pirate_r][pirate_c] = true;

	while (!q.empty()) {
		Node node = q.front();
		q.pop();

		if (node.sua) {
			if (visited[node.r][node.c] == 2)			// 수아의 현재 위치가 2라면 이미 죽은 거
				continue;
			else if (map[node.r][node.c] == 'T')		// 죽지 않고 T에 도달했다면 성공
				return true;
		}

		for (int d = 0; d < 4; d++) {
			int R = node.r + dr[d];
			int C = node.c + dc[d];
			if (node.sua && R >= 0 && R < N && C >= 0 && C < M && !visited[R][C] && map[R][C] != 'I') {
				q.push({ true, R, C });
				visited[R][C] = 1;
			}
			else if (!node.sua && R >= 0 && R < N && C >= 0 && C < M && !pirate_visited[R][C] && map[R][C] != 'I') {
				q.push({ false, R, C });
				pirate_visited[R][C] = true;
				visited[R][C] = 2;
				for (int di = 0; di < 4; di++) {		// 현 해적 위치에서 동서남북으로 살피며 섬 만날 때까지 혹은 맵 끝까지 2로 처리
					int R_l = R + dr[di];
					int C_l = C + dc[di];
					while (R_l >= 0 && R_l < N && C_l >= 0 && C_l < M && map[R_l][C_l] != 'I') {
						visited[R_l][C_l] = 2;
						R_l += dr[di], C_l += dc[di];
					}
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
	for (int i = 0; i < N; i++) {
		cin >> map[i];
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 'Y')
				start_r = i, start_c = j;
			else if (map[i][j] == 'V')
				pirate_r = i, pirate_c = j;
		}
	}
	if (Solve())
		cout << "YES";
	else
		cout << "NO";

	return 0;
}