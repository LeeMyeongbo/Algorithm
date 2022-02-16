#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define MAX 100000
using namespace std;

int N, M, room[MAX + 1], K, r, order, seq[2 * MAX + 1], scc_num, scc_index[2 * MAX + 1];
bool complete[2 * MAX + 1];
vector<int> room_switch[MAX + 1], graph[2 * MAX + 1];
stack<int> s;

int dfs(int cur)
{
	seq[cur] = ++order;
	int par = order;
	s.push(cur);

	for (int& i : graph[cur]) {
		if (!seq[i])
			par = min(par, dfs(i));
		else if (!complete[i])
			par = min(par, seq[i]);
	}
	if (par == seq[cur]) {
		scc_num++;
		while (!s.empty()) {
			int v = s.top();
			s.pop();

			complete[v] = true;
			scc_index[v] = scc_num;
			if (v == cur)
				break;
		}
	}
	return par;
}

bool chk()
{
	for (int i = 1; i <= M; i++)		// 스위치 수에 따라서 되는지 안되는지 체크 (실수주의)
		if (scc_index[MAX - i] && scc_index[MAX + i] && scc_index[MAX - i] == scc_index[MAX + i])
			return false;
	return true;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
		cin >> room[i];
	for (int i = 1; i <= M; i++) {
		cin >> K;
		while (K--) {
			cin >> r;
			room_switch[r].push_back(i);
		}
	}
	for (int i = 1; i <= N; i++) {
		if (room[i]) {			// 열려있을 경우 : (!p▽q)△(p△!q)임을 이용 => p→q, q→p, !p→!q, !q→!p
			for (int j = 0; j < 2; j++) {
				graph[MAX - room_switch[i][j]].push_back(MAX - room_switch[i][(j + 1) % 2]);
				graph[MAX + room_switch[i][j]].push_back(MAX + room_switch[i][(j + 1) % 2]);
			}
		}
		else {					// 닫혀있을 경우 : (p▽q)△(!p△!q)임을 이용 => p→!q, q→!p, !p→q, !q→p
			for (int j = 0; j < 2; j++) {
				graph[MAX - room_switch[i][j]].push_back(MAX + room_switch[i][(j + 1) % 2]);
				graph[MAX + room_switch[i][j]].push_back(MAX - room_switch[i][(j + 1) % 2]);
			}
		}
	}
	for (int i = MAX - M; i <= MAX + M; i++)		// 스위치 수에 따라서 되는지 안되는지 체크해야 함! (실수주의)
		if (i != MAX && !complete[i])
			dfs(i);

	chk() ? cout << 1 : cout << 0;
	return 0;
}