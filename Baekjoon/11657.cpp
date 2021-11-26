#include <iostream>
#include <algorithm>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define MAX 1000000000
using namespace std;

int N, M, A, B, C, map[501][501];
long long nodes[501];
bool visited[501];

void BFS()					// 1�� ���ÿ������� ����� ������ �� �ִ� ���õ��� üũ (������ �� ���� ���õ� ���� �����ϹǷ�)
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
				if (map[start][end] != MAX && nodes[start] != MAX)		// ���� ������ ���� ���Ѵ밡 �ƴϰ� ������ ������ ���
					nodes[end] = min(nodes[end], nodes[start] + map[start][end]);		// ��� ������ edge relaxation (N - 1�� ����)

	for (int start = 1; start <= N; start++)
		for (int end = 1; end <= N; end++)
			if (map[start][end] != MAX) {
				long long Min = min(nodes[end], nodes[start] + map[start][end]);		// ���������� ��� ������ edge relaxation ����
				if (Min != nodes[end] && visited[end]) {				// �ּڰ��� �� ���� ������ ���� -> ���� ����Ŭ �����Ѵٴ� �ǹ�
					cout << -1;											// �� ���� ����Ŭ�� ������(1)���κ��� ���� ������ ��� -1
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
		map[A][B] = min(map[A][B], C);		// ���� (A, B) �մ� ������ ���� �� �־��� ���� �����Ƿ� �� ���� ����ġ�� ���� ���� ������ ����
	}

	BFS();
	Bellman();
	return 0;
}