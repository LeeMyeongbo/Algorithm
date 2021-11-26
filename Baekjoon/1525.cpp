#include <iostream>
#include <queue>
#include <cmath>
#include <set>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

struct Node {
	int r, c, move, cur;
};
int map[3][3], dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 }, start_r, start_c;
set<int> visited;
queue<Node> q;

int bitmask(int cur_map[][3])			// 맵의 각 자리를 9^0, 9^1...9^8으로 두고 비트마스킹으로 방문여부 판단
{
	int ans = 0;
	for (int i = 0; i < 9; i++)
		ans += cur_map[i / 3][i % 3] * (int)pow(9, i);
	return ans;
}

int BFS(int finish)
{
	int cur = bitmask(map);
	int cur_map[3][3];

	q.push({ start_r, start_c, 0, cur });
	visited.insert(cur);				// set에 담아두면 log 시간에 방문여부 확인 가능

	while (!q.empty()) {
		Node node = q.front();
		q.pop();

		if (node.cur == finish)			// 1 2 3 4 5 6 7 8 0 순서라면 완료!
			return node.move;

		int sum = node.cur;
		for (int i = 0; i < 9; i++) {
			cur_map[i / 3][i % 3] = sum % 9;
			sum /= 9;
		}
		for (int d = 0; d < 4; d++) {
			int R = node.r + dr[d];
			int C = node.c + dc[d];
			if (R >= 0 && R < 3 && C >= 0 && C < 3) {
				swap(cur_map[node.r][node.c], cur_map[R][C]);
				int new_sum = bitmask(cur_map);
				if (!visited.count(new_sum)) {
					visited.insert(new_sum);
					q.push({ R, C, node.move + 1, new_sum });
				}
				swap(cur_map[node.r][node.c], cur_map[R][C]);
			}
		}
	}
	return -1;
}

int main()
{
	FAST;
	for (int i = 0; i < 9; i++) {
		cin >> map[i / 3][i % 3];
		if (!map[i / 3][i % 3])
			start_r = i / 3, start_c = i % 3;
	}
	int finish = 0;
	for (int i = 1; i <= 8; i++)
		finish += i * (int)pow(9, i - 1);

	cout << BFS(finish);
	return 0;
}