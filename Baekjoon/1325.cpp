#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, chk[10001], A, B, id, scc[10001], Size[10001], n, Max, edge[10001];		// scc[i] : i번 정점이 몇 번 scc인지 저장
bool visit[10001];							// Size[i] : i번 scc를 이루는 정점 개수 저장, edge[i] : i번 scc의 진입 간선 개수 저장
vector<int> graph[10001], new_g[10001];		// new_g : scc를 구한 후 새로 형성한 그래프
stack<int> s;
set<int> visited[10001];
queue<int> q;

int Find_SCC(int cur) {				// 사이클인 부분을 하나의 정점으로 바꿈
	chk[cur] = ++id;
	s.push(cur);

	int parent = chk[cur];
	for (int i : graph[cur]) {
		if (!chk[i])								// 처음 정점을 방문할 경우
			parent = min(parent, Find_SCC(i));
		else if (!scc[i])							// 처리 중인 정점을 만났을 경우
			parent = min(parent, chk[i]);
	}
	if (parent == chk[cur]) {
		n++;
		while (!s.empty()) {
			int v = s.top();
			s.pop();

			scc[v] = n;
			if (v == cur)					// 자기 자신이 나오면 종료
				break;
		}
	}
	return parent;
}

void Solve()
{
	int max_scc = 0;
	for (int i = 1; i <= N; i++) {			// SCC를 하나의 정점으로 보고 그래프 새로 형성
		Size[scc[i]]++;
		max_scc = max(max_scc, scc[i]);
		for (int v : graph[i]) {
			if (scc[i] != scc[v] && !visited[scc[i]].count(scc[v])) {
				new_g[scc[i]].push_back(scc[v]);
				visited[scc[i]].insert(scc[v]);
				edge[scc[v]]++;
			}
		}
	}

	for (int i = 1; i <= max_scc; i++)
		if (!edge[i]) {						// 진입 간선 수가 0인 정점 발견 시 BFS탐색
			q.push(i);
			visit[i] = true;

			while (!q.empty()) {
				int cur = q.front();
				q.pop();

				for (int n : new_g[cur]) {
					if (!visit[n]) {
						q.push(n);
						Size[i] += Size[n];
						visit[n] = true;
					}
				}
			}
			fill(visit, visit + N + 1, false);
		}
	
	for (int i = 1; i <= N; i++)
		Max = max(Max, Size[i]);

	for (int i = 1; i <= N; i++)
		if (Size[scc[i]] == Max)
			cout << i << " ";
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> A >> B;
		graph[B].push_back(A);
	}

	for (int i = 1; i <= N; i++)
		if (!scc[i])
			Find_SCC(i);

	Solve();
	return 0;
}