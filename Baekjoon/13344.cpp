#include <iostream>
#include <vector>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, K, L, parent[50000], indegree[50000];	// parent[i] : i가 속한 집합, indegree[i] : 집합 i의 진입 간선 수
bool unions[50000], tp_visited[50000];	// unions[i] : 실제 존재하는 집합 i를 true로, tp_visited[i] : 위상 정렬하며 방문한 집합 i true로 체크
char symbol;
vector<pair<int, int>> edges;
vector<int> graph[50000];
queue<int> q;

int Find(int n)
{
	if (parent[n] == n)
		return n;
	return parent[n] = Find(parent[n]);
}

void Union(int n1, int n2)
{
	n1 = Find(n1);
	n2 = Find(n2);
	if (n1 == n2)
		return;

	if (n1 < n2)
		swap(n1, n2);
	parent[n1] = n2;
}

bool is_consistent()
{
	for (auto& e : edges) {
		graph[parent[e.first]].push_back(parent[e.second]);	// 간선들이 연결하는 집합 graph 형성
		indegree[parent[e.second]]++;
	}
	for (int i = 0; i < N; i++)
		if (unions[i] && !indegree[i])						// 진입 차수가 0인 집합 큐에 저장
			q.push(i);
	
	while (!q.empty()) {									// 위상 정렬 실시
		int cur = q.front();
		q.pop();

		tp_visited[cur] = true;					// 위상 정렬하며 방문하는 집합들은 모두 tp_visited에 true로 처리
		for (int& i : graph[cur]) {
			indegree[i]--;
			if (!indegree[i])
				q.push(i);
		}
	}
	for (int i = 0; i < N; i++)
		if (unions[i] && !tp_visited[i])		// 위상 정렬하며 방문하지 못한 집합 존재 시 일관성 x
			return false;
	return true;
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		parent[i] = i;

	for (int i = 0; i < M; i++) {
		cin >> K >> symbol >> L;
		if (symbol == '>')
			edges.push_back({ K, L });		// '>'일 경우 간선으로 연결
		else
			Union(K, L);					// '='일 경우 하나의 집합으로 합침
	}
	for (int i = 0; i < N; i++) {
		Find(i);
		unions[parent[i]] = true;			// 0부터 N-1까지 현 정점이 속한 집합을 true로 처리
	}
	if (is_consistent())
		cout << "consistent";
	else
		cout << "inconsistent";

	return 0;
}