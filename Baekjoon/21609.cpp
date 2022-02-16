#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N, M, map[20][20], Score;
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
queue<pair<int, int>> q;

void gravity()
{
	for (int r = N - 2; r >= 0; r--) {
		for (int c = 0; c < N; c++) {
			if (map[r][c] < 0)
				continue;
			int R = r + 1;
			while (R < N && map[R][c] == -2) {
				map[R][c] = map[R - 1][c];
				map[R - 1][c] = -2;									// 빈 곳 = -2
				R++;
			}
		}
	}
}

void rotate()
{
	/*for (int k = 0; k < N / 2; k++) {
		for (int rotate = 0; rotate < N - 2 * k - 1; rotate++) {	// 한 칸씩 반시계 방향으로 옮기는 걸 (변 길이-1)번 반복
			int tmp = map[k][k];
			for (int c = k; c < N - k - 1; c++)
				map[k][c] = map[k][c + 1];
			for (int r = k; r < N - k - 1; r++)
				map[r][N - k - 1] = map[r + 1][N - k - 1];
			for (int c = N - k - 1; c > k; c--)
				map[N - k - 1][c] = map[N - k - 1][c - 1];
			for (int r = N - k - 1; r > k + 1; r--)
				map[r][k] = map[r - 1][k];
			map[k + 1][k] = tmp;
		}
	} */

	// 훨씬 더 쉬운 방법이 있다 이말이야
	int tmp[20][20];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			tmp[N - 1 - j][i] = map[i][j];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			map[i][j] = tmp[i][j];
}

int solve()
{
	while (true) {
		bool visited[20][20] = { false, };							// 전체 블록 탐색할 때 방문 체크
		bool is_blockgroup = false;
		vector<vector<pair<int, int>>> block_groups;
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				if (visited[r][c] || map[r][c] <= 0)				// 이미 탐색한 블록이거나 일반 블록이 아니라면 skip
					continue;

				// 무지개 블록은 중복 방문하지만 BFS로 한 블록그룹 찾을 땐 한 번씩만 방문
				bool visited_rainbow[20][20] = { false, };			// 블록그룹 하나를 탐색할 때 무지개 블록 방문 체크
				vector<pair<int, int>> block_group;
				q.push({ r, c });
				visited[r][c] = true;

				while (!q.empty()) {
					block_group.push_back(q.front());
					int R = q.front().first, C = q.front().second;
					q.pop();

					for (int d = 0; d < 4; d++) {
						int new_R = R + dr[d];
						int new_C = C + dc[d];
						if (new_R >= 0 && new_R < N && new_C >= 0 && new_C < N) {
							if (map[new_R][new_C] == map[r][c] && !visited[new_R][new_C]) {		// 색깔이 같은 블록일 경우
								visited[new_R][new_C] = true;
								q.push({ new_R, new_C });
							}
							else if (!map[new_R][new_C] && !visited_rainbow[new_R][new_C]) {	// 무지개 블록일 경우
								visited_rainbow[new_R][new_C] = true;
								q.push({ new_R, new_C });
							}
						}
					}
				}
				if (block_group.size() > 1)
					is_blockgroup = true;
				else continue;

				if (block_groups.empty() || block_groups[0].size() == block_group.size())	// 크기가 가장 큰 블록그룹 저장
					block_groups.push_back(block_group);
				else if (block_groups[0].size() < block_group.size()) {
					block_groups.clear();
					block_groups.push_back(block_group);
				}
			}
		}
		if (!is_blockgroup)
			break;

		// block_groups에는 크기가 가장 큰 블록그룹들이 저장되어 있음
		vector<pair<int, int>> rainbow_blocks;									// (무지개 블록 개수, 해당 블록그룹의 index)
		for (int i = 0; i < (int)block_groups.size(); i++) {					// 무지개 블록 수가 가장 많은 블록그룹 저장
			int n_rainbow = 0;
			for (int j = 0; j < (int)block_groups[i].size(); j++) {
				if (!map[block_groups[i][j].first][block_groups[i][j].second])
					n_rainbow++;
			}
			if (rainbow_blocks.empty() || rainbow_blocks[0].first == n_rainbow)
				rainbow_blocks.push_back({ n_rainbow, i });
			else if (rainbow_blocks[0].first < n_rainbow) {
				rainbow_blocks.clear();
				rainbow_blocks.push_back({ n_rainbow, i });
			}
		}

		// rainbow_blocks에는 크기가 가장 크면서 무지개 블록 개수가 가장 많은 블록그룹들의 index가 저장되어 있음
		pair<int, int> p = { -1, -1 };
		int chosen = 0;
		for (int i = 0; i < (int)rainbow_blocks.size(); i++) {
			int cur = rainbow_blocks[i].second;
			sort(block_groups[cur].begin(), block_groups[cur].end());	// 좌표를 오름차순으로 정렬하고
			for (int j = 0; j < (int)block_groups[cur].size(); j++) {	// 각 블록그룹마다 기준 블록 탐색
				if (map[block_groups[cur][j].first][block_groups[cur][j].second] > 0 && block_groups[cur][j] > p) {
					p = block_groups[cur][j];							// 블록그룹 별 기준 블록 위치의 최댓값 갱신
					chosen = cur;										// 몇 번째 블록그룹 선택했는지도 저장
					break;
				}
			}
		}

		Score += block_groups[chosen].size() * block_groups[chosen].size();
		for (int i = 0; i < (int)block_groups[chosen].size(); i++)
			map[block_groups[chosen][i].first][block_groups[chosen][i].second] = -2;	// 빈 곳은 -2로 처리

		gravity();
		rotate();
		gravity();
	}
	return Score;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
			cin >> map[r][c];

	cout << solve();
	return 0;
}