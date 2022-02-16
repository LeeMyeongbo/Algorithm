#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define MAX 5000
using namespace std;

int k, n, lamp[MAX * 2 + 1], num, seq[MAX * 2 + 1], scc_num, scc_index[MAX * 2 + 1];
char color;
bool complete[MAX * 2 + 1];
vector<int> graph[MAX * 2 + 1];		// 빨간색일 때 MAX보다 크고 파란색일 때 MAX보다 작음
stack<int> s;

int dfs(int cur)
{
	seq[cur] = ++num;
	int par = num;
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
	for (int i = 1; i <= k; i++)
		if (scc_index[MAX - i] && scc_index[MAX + i] && scc_index[MAX - i] == scc_index[MAX + i])
			return false;
	return true;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int predict[3];

	cin >> k >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> predict[j] >> color;
			if (color == 'B')
				predict[j] *= -1;
		}
		for (int j = 0; j < 3; j++) {			// 하나가 만족하지 못할 경우 나머지 2개가 무적권 만족해야 함을 이용
			graph[MAX - predict[j]].push_back(MAX + predict[(j + 1) % 3]);
			graph[MAX - predict[j]].push_back(MAX + predict[(j + 2) % 3]);
		}
	}
	for (int i = MAX - k; i <= MAX + k; i++)
		if (i != MAX && !complete[i])
			dfs(i);

	if (!chk())
		cout << -1;
	else {
		for (int i = 1; i <= k; i++) {
			if (scc_index[MAX - i] < scc_index[MAX + i])
				cout << 'B';
			else
				cout << 'R';
		}
	}
	return 0;
}