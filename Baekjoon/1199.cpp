#include <iostream>
#include <stack>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

stack<pair<int, int>> graph[1000];
int N, idx, e;
bool possible = true, used[10000000];			// 사용한 간선 번호 저장용

void DFS(int i)
{
	while (true) {
		while (!graph[i].empty() && used[graph[i].top().second])
			graph[i].pop();							// 이미 사용한 간선 제외하는 과정

		if (graph[i].empty())						// 현재 정점에서 더 이상 사용할 간선 없으면 재귀 빠져나감
			break;

		pair<int, int> p = graph[i].top();
		graph[i].pop();

		used[p.second] = true;						// 간선 사용했다는 표시
		DFS(p.first);
	}
	cout << i + 1 << " ";
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			cin >> e;
			if (i < j) {
				while (e--) {
					graph[i].push({ j, idx });
					graph[j].push({ i, idx++ });
				}
			}
		}
	for (int i = 0; i < N; i++)
		if (graph[i].size() % 2)
			possible = false;						// 정점 하나라도 차수가 홀수면 오일러 회로 x

	if (possible)
		DFS(0);
	else
		cout << -1;

	return 0;
}