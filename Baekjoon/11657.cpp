#include <iostream>
#include <algorithm>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define MAX 1000000000
using namespace std;

int N, M, A, B, C, map[501][501];
long long nodes[501];
bool visited[501];

void BFS()					// 1번 도시에서부터 출발해 도달할 수 있는 도시들을 체크 (도달할 수 없는 도시들 존재 가능하므로)
{
	queue<int> q;
	q.push(1);
	visited[1] = true;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for(int i = 1; i <= N; i++)
			if (map[cur][i] != MAX && !visited[i]) {
				q.push(i);
				visited[i] = true;
			}
	}
}

void Bellman()
{
	nodes[1] = 0;
	for (int i = 0; i < N - 1; i++)
		for (int start = 1; start <= N; start++)
			for (int end = 1; end <= N; end++)
				if (map[start][end] != MAX && nodes[start] != MAX)		// 시작 정점의 값이 무한대가 아니고 간선이 존재할 경우
					nodes[end] = min(nodes[end], nodes[start] + map[start][end]);		// 모든 간선들 edge relaxation (N - 1번 수행)

	for (int start = 1; start <= N; start++)
		for (int end = 1; end <= N; end++)
			if (map[start][end] != MAX) {
				long long Min = min(nodes[end], nodes[start] + map[start][end]);		// 마지막으로 모든 간선들 edge relaxation 수행
				if (Min != nodes[end] && visited[end]) {				// 최솟값이 더 작은 값으로 갱신 -> 음수 사이클 존재한다는 의미
					cout << -1;											// 그 음수 사이클에 시작점(1)으로부터 도달 가능할 경우 -1
					return;
				}
			}

	for (int i = 2; i <= N; i++) {
		if (visited[i])
			cout << nodes[i] << "\n";
		else
			cout << -1 << "\n";
	}
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
		fill(map[i], map[i] + N + 1, MAX);
	fill(nodes, nodes + N + 1, MAX);
	
	for (int i = 0; i < M; i++) {
		cin >> A >> B >> C;
		map[A][B] = min(map[A][B], C);		// 같은 (A, B) 잇는 간선이 여러 개 주어질 수도 있으므로 그 때는 가중치가 제일 작은 것으로 저장
	}

	BFS();
	Bellman();
	return 0;
}