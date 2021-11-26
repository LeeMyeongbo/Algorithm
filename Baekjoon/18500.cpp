#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int R, C, N, stick[100], dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 }, visited[100][100];
char map[100][101];
queue<pair<int, int>> q;
vector<pair<int, int>> minerals;

bool falling_cluster(int r, int c, int n)		// ���� Ŭ������ ���ϰ� �װ� �������� Ŭ���������� �Ǵ�
{
	bool can_fall = true;
	visited[r][c] = true;
	q.push({ r, c });

	while (!q.empty()) {
		int cur_r = q.front().first;
		int cur_c = q.front().second;
		q.pop();

		if (cur_r == R - 1)						// �ٴڿ� �ִ� �̳׶� ���� �� ���� Ŭ�����ʹ� �������� Ŭ�����Ͱ� �ƴ�
			can_fall = false;
		minerals.push_back({ cur_r, cur_c });

		for (int d = 0; d < 4; d++) {
			int new_r = cur_r + dr[d];
			int new_c = cur_c + dc[d];
			if (new_r >= 0 && new_r < R && new_c >= 0 && new_c < C && !visited[new_r][new_c] && map[new_r][new_c] == 'x') {
				visited[new_r][new_c] = n;
				q.push({ new_r, new_c });
			}
		}
	}
	return can_fall;
}

void Solve()
{
	for (int n = 0; n < N; n++) {
		if (n % 2) {
			for (int c = C - 1; c >= 0; c--)			// ����� �����ʿ��� �������� ������ ���� ó�� ���� �̳׶� �ı�
				if (map[stick[n]][c] == 'x') {
					map[stick[n]][c] = '.';
					break;
				}
		}
		else {
			for (int c = 0; c < C; c++)
				if (map[stick[n]][c] == 'x') {			// ���ʿ��� ���������� ������ ó�� ���� �̳׶� �ı�
					map[stick[n]][c] = '.';
					break;
				}
		}
		int cluster = 1;
		bool fallen = false;
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (visited[i][j] || map[i][j] == '.')	// �� �� �Ǵ� �湮�� ĭ�̶�� skip
					continue;
				if (falling_cluster(i, j, cluster)) {
					int min_fall = 10001;
					sort(minerals.begin(), minerals.end());		// �� Ŭ�������� ���� ���ʿ� �ִ� �̳׶����� ������� ����

					for (auto& p : minerals) {
						int cur_r = p.first, cur_c = p.second, fall = 0;

						while (cur_r + 1 < R && (map[cur_r + 1][cur_c] == '.' || map[cur_r + 1][cur_c] == 'x' && visited[cur_r + 1][cur_c] == cluster)) {
							cur_r++;
							fall++;
						}
						if (fall)
							min_fall = min(min_fall, fall);		// Ŭ�������� �� �̳׶����� �������� ������ �ּڰ� ����
					}
					while (!minerals.empty()) {					// ���� �Ʒ��ʿ� �ִ� �̳׶����� ���ʷ� ����߸�
						pair<int, int> p = minerals.back();
						int cur_r = p.first, cur_c = p.second;

						map[cur_r][cur_c] = '.';
						map[cur_r + min_fall][cur_c] = 'x';
						minerals.pop_back();
					}
					fallen = true;
					break;
				}
				cluster++;
				minerals.clear();
			}
			if (fallen)
				break;
		}
		for (int i = 0; i < R; i++)
			fill(visited[i], visited[i] + C, 0);
	}
	for (int r = 0; r < R; r++)
		cout << map[r] << "\n";
}

int main()
{
	FAST;
	cin >> R >> C;
	for (int r = 0; r < R; r++)
		cin >> map[r];
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> stick[i];
		stick[i] = R - stick[i];
	}

	Solve();
	return 0;
}