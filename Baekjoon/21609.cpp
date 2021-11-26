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
				map[R - 1][c] = -2;									// �� �� = -2
				R++;
			}
		}
	}
}

void rotate()
{
	/*for (int k = 0; k < N / 2; k++) {
		for (int rotate = 0; rotate < N - 2 * k - 1; rotate++) {	// �� ĭ�� �ݽð� �������� �ű�� �� (�� ����-1)�� �ݺ�
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

	// �ξ� �� ���� ����� �ִ� �̸��̾�
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
		bool visited[20][20] = { false, };							// ��ü ��� Ž���� �� �湮 üũ
		bool is_blockgroup = false;
		vector<vector<pair<int, int>>> block_groups;
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				if (visited[r][c] || map[r][c] <= 0)				// �̹� Ž���� ����̰ų� �Ϲ� ����� �ƴ϶�� skip
					continue;

				// ������ ����� �ߺ� �湮������ BFS�� �� ��ϱ׷� ã�� �� �� ������ �湮
				bool visited_rainbow[20][20] = { false, };			// ��ϱ׷� �ϳ��� Ž���� �� ������ ��� �湮 üũ
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
							if (map[new_R][new_C] == map[r][c] && !visited[new_R][new_C]) {		// ������ ���� ����� ���
								visited[new_R][new_C] = true;
								q.push({ new_R, new_C });
							}
							else if (!map[new_R][new_C] && !visited_rainbow[new_R][new_C]) {	// ������ ����� ���
								visited_rainbow[new_R][new_C] = true;
								q.push({ new_R, new_C });
							}
						}
					}
				}
				if (block_group.size() > 1)
					is_blockgroup = true;
				else continue;

				if (block_groups.empty() || block_groups[0].size() == block_group.size())	// ũ�Ⱑ ���� ū ��ϱ׷� ����
					block_groups.push_back(block_group);
				else if (block_groups[0].size() < block_group.size()) {
					block_groups.clear();
					block_groups.push_back(block_group);
				}
			}
		}
		if (!is_blockgroup)
			break;

		// block_groups���� ũ�Ⱑ ���� ū ��ϱ׷���� ����Ǿ� ����
		vector<pair<int, int>> rainbow_blocks;									// (������ ��� ����, �ش� ��ϱ׷��� index)
		for (int i = 0; i < (int)block_groups.size(); i++) {					// ������ ��� ���� ���� ���� ��ϱ׷� ����
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

		// rainbow_blocks���� ũ�Ⱑ ���� ũ�鼭 ������ ��� ������ ���� ���� ��ϱ׷���� index�� ����Ǿ� ����
		pair<int, int> p = { -1, -1 };
		int chosen = 0;
		for (int i = 0; i < (int)rainbow_blocks.size(); i++) {
			int cur = rainbow_blocks[i].second;
			sort(block_groups[cur].begin(), block_groups[cur].end());	// ��ǥ�� ������������ �����ϰ�
			for (int j = 0; j < (int)block_groups[cur].size(); j++) {	// �� ��ϱ׷츶�� ���� ��� Ž��
				if (map[block_groups[cur][j].first][block_groups[cur][j].second] > 0 && block_groups[cur][j] > p) {
					p = block_groups[cur][j];							// ��ϱ׷� �� ���� ��� ��ġ�� �ִ� ����
					chosen = cur;										// �� ��° ��ϱ׷� �����ߴ����� ����
					break;
				}
			}
		}

		Score += block_groups[chosen].size() * block_groups[chosen].size();
		for (int i = 0; i < (int)block_groups[chosen].size(); i++)
			map[block_groups[chosen][i].first][block_groups[chosen][i].second] = -2;	// �� ���� -2�� ó��

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