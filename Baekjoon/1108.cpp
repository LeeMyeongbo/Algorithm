#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

int N, link, n, order, seq[2551], scc_num, scc_index[2551], indegree[2551];
long long score[2551];
bool complete[2551];
string page, linked, want;
vector<int> graph[2551], new_graph[2551];		// new_graph : scc ������ �� �����ϴ� ���ο� �׷���
map<string, int> Hashed;
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
			if (cur == v)
				break;
		}
	}
	return par;
}

long long solve()
{
	queue<int> q;
	fill(score, score + 2551, 1);

	for (int i = 1; i <= n; i++)
		for (int& v : graph[i])
			if (scc_index[i] != scc_index[v]) {		// i�� v�� �ٸ� scc�� ���� ��쿡�� ���� + �������� ����
				new_graph[i].push_back(v);			// (����Ŭ�� ������ ���������� ���ϸ� �ȵǴϱ� ���� scc�� ���������� ���� ������)
				indegree[v]++;
			}

	for (int i = 1; i <= n; i++)
		if (!indegree[i])
			q.push(i);

	while (!q.empty()) {			// ���� ���� ���� (���� scc�� �����̶� ������ �޶��� �� �ִٴ� �Ϳ� ����)
		int cur = q.front();
		q.pop();

		for (int i : new_graph[cur]) {
			indegree[i]--;
			score[i] += score[cur];
			if (!indegree[i])
				q.push(i);
		}
	}
	return score[Hashed[want]];
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N;
	for (int i = 1; i <= N; i++) {			// ������Ʈ�� ���ڿ� ���·� �־����Ƿ� �Էµ� ������� �ؽ� �����ϰ� �׷��� ����
		cin >> page >> link;
		if (!Hashed.count(page))
			Hashed.insert({ page, ++n });
		for (int j = 0; j < link; j++) {
			cin >> linked;
			if (!Hashed.count(linked))
				Hashed.insert({ linked, ++n });
			graph[Hashed[linked]].push_back(Hashed[page]);
		}
	}
	for (int i = 1; i <= n; i++)
		if (!complete[i])
			dfs(i);
	cin >> want;

	cout << solve();
	return 0;
}