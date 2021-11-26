#include <iostream>
#include <vector>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, K, L, parent[50000], indegree[50000];	// parent[i] : i�� ���� ����, indegree[i] : ���� i�� ���� ���� ��
bool unions[50000], tp_visited[50000];	// unions[i] : ���� �����ϴ� ���� i�� true��, tp_visited[i] : ���� �����ϸ� �湮�� ���� i true�� üũ
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
		graph[parent[e.first]].push_back(parent[e.second]);	// �������� �����ϴ� ���� graph ����
		indegree[parent[e.second]]++;
	}
	for (int i = 0; i < N; i++)
		if (unions[i] && !indegree[i])						// ���� ������ 0�� ���� ť�� ����
			q.push(i);
	
	while (!q.empty()) {									// ���� ���� �ǽ�
		int cur = q.front();
		q.pop();

		tp_visited[cur] = true;					// ���� �����ϸ� �湮�ϴ� ���յ��� ��� tp_visited�� true�� ó��
		for (int& i : graph[cur]) {
			indegree[i]--;
			if (!indegree[i])
				q.push(i);
		}
	}
	for (int i = 0; i < N; i++)
		if (unions[i] && !tp_visited[i])		// ���� �����ϸ� �湮���� ���� ���� ���� �� �ϰ��� x
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
			edges.push_back({ K, L });		// '>'�� ��� �������� ����
		else
			Union(K, L);					// '='�� ��� �ϳ��� �������� ��ħ
	}
	for (int i = 0; i < N; i++) {
		Find(i);
		unions[parent[i]] = true;			// 0���� N-1���� �� ������ ���� ������ true�� ó��
	}
	if (is_consistent())
		cout << "consistent";
	else
		cout << "inconsistent";

	return 0;
}