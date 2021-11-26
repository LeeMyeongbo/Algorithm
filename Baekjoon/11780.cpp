#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int n, m, map[101][101], ans[101][101], pre[101][101], a, b, c;
priority_queue<pair<int, int>> pq;
bool is_path = true;

void backtrack(int Start, int Cur, int depth)
{
	if (Start == Cur && depth > 1) {
		cout << depth << " " << Cur << " ";
		return;
	}
	if (!Cur) {
		is_path = false;
		cout << 0;
		return;
	}
	backtrack(Start, pre[Start][Cur], depth + 1);
	if (is_path)
		cout << Cur << " ";
}

void Solve()
{
	for (int start = 1; start <= n; start++) {
		pq.push({ 0, start });

		while (!pq.empty()) {
			int num = -pq.top().first;
			int cur = pq.top().second;
			pq.pop();

			if (ans[start][cur] != num)
				continue;

			for (int i = 1; i <= n; i++) {
				if (start != i && map[cur][i] != -1 && (!ans[start][i] || ans[start][i] > num + map[cur][i])) {
					pre[start][i] = cur;
					ans[start][i] = num + map[cur][i];
					pq.push({ -ans[start][i], i });
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			cout << ans[i][j] << " ";
		cout << "\n";
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			backtrack(i, j, 1);
			cout << "\n";
			is_path = true;
		}
	}
}

int main()
{
	FAST;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		fill(map[i], map[i] + n + 1, -1);

	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		if (map[a][b] == -1)
			map[a][b] = c;
		map[a][b] = min(map[a][b], c);
	}

	Solve();
	return 0;
}