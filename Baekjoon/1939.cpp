#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define MAX 1000000000
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, A, B, C, Start, End, Left = MAX, Right, ans;
vector<pair<int, int>> graph[10001];			// (�߷�, ����� ����)���� ����

bool BFS(int weight)
{
	queue<int> q;
	bool visited[10001] = { false, };
	q.push(Start);
	visited[Start] = true;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		if (cur == End)
			return true;

		for (auto& p : graph[cur]) {
			if (p.first >= weight && !visited[p.second]) {
				visited[p.second] = true;
				q.push(p.second);
			}
		}
	}
	return false;
}

int Solve()
{
	while (Left <= Right) {
		int middle = (Left + Right) / 2;
		if (BFS(middle)) {					// middle ��ŭ�� �߷����� ���������� �ٸ��� �ǳ� �� �ִٸ� left�� �� ũ�� ����
			ans = middle;
			Left = middle + 1;
		}
		else								// �ǳ� �� ���ٸ� right�� �۰� ����
			Right = middle - 1;
	}
	return ans;
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> A >> B >> C;
		Left = min(Left, C);
		Right = max(Right, C);
		graph[A].push_back({ C, B });
		graph[B].push_back({ C, A });
	}
	cin >> Start >> End;

	cout << Solve();
	return 0;
}