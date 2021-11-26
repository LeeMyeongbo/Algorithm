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
vector<int> graph[2551], new_graph[2551];		// new_graph : scc 밝혀낸 뒤 형성하는 새로운 그래프
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
			if (scc_index[i] != scc_index[v]) {		// i와 v가 다른 scc에 속할 경우에만 연결 + 진입차수 증가
				new_graph[i].push_back(v);			// (사이클이 형성된 정점끼리는 더하면 안되니까 같은 scc의 정점끼리는 연결 끊어줌)
				indegree[v]++;
			}

	for (int i = 1; i <= n; i++)
		if (!indegree[i])
			q.push(i);

	while (!q.empty()) {			// 위상 정렬 시전 (같은 scc내 정점이라도 점수가 달라질 수 있다는 것에 유의)
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
	for (int i = 1; i <= N; i++) {			// 웹사이트가 문자열 형태로 주어지므로 입력된 순서대로 해시 형성하고 그래프 형성
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