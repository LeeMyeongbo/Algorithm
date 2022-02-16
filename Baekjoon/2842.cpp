#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#define MAX 1000005
using namespace std;

int N, altitude[50][50], sr, sc, Ans = MAX;
const int dr[] = { -1, -1, 0, 1, 1, 1, 0, -1 }, dc[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
char map[50][51];
vector<int> al_list;

bool BFS(int low, int high)
{
	if (altitude[sr][sc] < low || altitude[sr][sc] > high)
		return false;

	queue<pair<int, int>> q;
	bool visited[50][50] = { false, };

	q.push({ sr, sc });
	visited[sr][sc] = true;

	while (!q.empty()) {
		int cur_r = q.front().first;
		int cur_c = q.front().second;
		q.pop();

		for (int d = 0; d < 8; d++) {
			int new_r = cur_r + dr[d];
			int new_c = cur_c + dc[d];
			if (new_r >= 0 && new_r < N && new_c >= 0 && new_c < N && !visited[new_r][new_c]) {
				if (altitude[new_r][new_c] >= low && altitude[new_r][new_c] <= high) {
					visited[new_r][new_c] = true;
					q.push({ new_r, new_c });
				}
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!visited[i][j] && map[i][j] == 'K')
				return false;
		}
	}
	return true;
}

int solve()
{
	int left = 0, right = 0, size = (int)al_list.size();

	while (left < size && right < size) {
		if (BFS(al_list[left], al_list[right])) {
			Ans = min(Ans, al_list[right] - al_list[left]);
			if (left == right)
				return Ans;
			left++;
		}
		else
			right++;
	}
	while (left < size) {
		if (BFS(al_list[left], al_list[size - 1]))
			Ans = min(Ans, al_list[size - 1] - al_list[left]);
		left++;
	}

	return Ans;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> map[i];
		for (int j = 0; j < N; j++) {
			if (map[i][j] == 'P')
				sr = i, sc = j;
		}
	}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			cin >> altitude[i][j];
			al_list.push_back(altitude[i][j]);
		}

	sort(al_list.begin(), al_list.end());

	cout << solve();
	return 0;
}