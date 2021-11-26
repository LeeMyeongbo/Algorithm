#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

const int dr[] = { 0, 0, 1, 0, -1 }, dc[] = { 0, 1, 0, -1, 0 };		// ��(1) ��(2) ��(3) ��(4) ������
int n, map[51][51], start_r, start_c, end_r, end_c, k, num, circuit, pre_r, pre_c, cur_r, cur_c;
int pre[51][51], dij[51][51];					// pre[r][c] : r�� c���� ������ ���� ����, dij[r][c] : ����� �ּڰ�
priority_queue<pair<int, pair<int, int>>> q;
vector<pair<int, int>> ans;

void trace_back(int r, int c, int pre_dir)		// ���� ���� ��, ��, ���� ��ġ�� ����
{
	if (r == start_r && c == start_c) {
		ans.push_back({ r, c });
		return;
	}
	int dir = pre[r][c];
	if (dir != pre_dir)
		ans.push_back({ r, c });
	int d = dir + 2 > 4 ? dir - 2 : dir + 2;	// ���� ��ġ�� ����� ������ �ݴ� ������ �����ְ� �ش� �ݴ� ������ ��ġ�� ����
	trace_back(r + dr[d], c + dc[d], dir);
}

void solve()
{
	q.push({ -map[start_r][start_c], {start_r, start_c} });
	dij[start_r][start_c] = map[start_r][start_c];
	
	while (!q.empty()) {
		int cost = -q.top().first;
		int r = q.top().second.first;
		int c = q.top().second.second;
		q.pop();

		if (cost > dij[r][c])
			continue;

		for (int d = 1; d <= 4; d++) {
			int R = r + dr[d];
			int C = c + dc[d];
			if (R >= 1 && R <= n && C >= 1 && C <= n && (dij[R][C] == -1 || dij[R][C] > cost + map[R][C])) {
				dij[R][C] = cost + map[R][C];
				pre[R][C] = d;
				q.push({ -dij[R][C], {R, C} });
			}
		}
	}
	cout << dij[end_r][end_c] << "\n";
	trace_back(end_r, end_c, 0);
	cout << ans.size() << " ";
	while (!ans.empty()) {
		cout << ans.back().first << " " << ans.back().second << " ";
		ans.pop_back();
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n >> start_r >> start_c >> end_r >> end_c >> k >> num;
	for (int i = 1; i <= n; i++) {
		fill(map[i], map[i] + n + 1, 1);
		fill(dij[i], dij[i] + n + 1, -1);
	}

	for (int i = 0; i < num; i++) {
		cin >> circuit >> pre_r >> pre_c;
		for (int j = 0; j < circuit - 1; j++) {
			cin >> cur_r >> cur_c;
			if (pre_r == cur_r) {
				int Min = min(pre_c, cur_c);
				int Max = max(pre_c, cur_c);
				for (int m = Min; m <= Max; m++)
					map[cur_r][m] = k;
			}
			else {
				int Min = min(pre_r, cur_r);
				int Max = max(pre_r, cur_r);
				for (int m = Min; m <= Max; m++)
					map[m][cur_c] = k;
			}
			pre_r = cur_r, pre_c = cur_c;
		}
	}
	
	solve();
	return 0;
}