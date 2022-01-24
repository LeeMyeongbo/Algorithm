#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

struct Node {
	int cur, flag;
};
int T, K, visited[201], vertice;
map<string, int> v;
string str1, str2;
vector<int> graph[201];
queue<Node> q;

bool BFS(int start)					// ���������κ��� ������ ������ BFS �����ϸ� 1, -1 ������ ���� ��ŷ
{
	q.push({ start, 1 });
	visited[start] = 1;

	while (!q.empty()) {
		Node node = q.front();
		q.pop();

		for (int i : graph[node.cur]) {
			if (!visited[i]) {
				q.push({ i, -node.flag });
				visited[i] = -node.flag;
			}
			else if (visited[i] == node.flag)	// ���� ������ ���� ���� ��ġ�� ���� ������ ��ŷ�Ǿ� �ִ�? -> �� �� ����
				return false;
		}
	}
	return true;
}

string solve() 
{
	for (int i = 1; i <= vertice; i++) {
		if (!visited[i] && !BFS(i))
			return "No\n";
	}
	return "Yes\n";
}

int main(int argc, char** argv)
{
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {

		cin >> K;
		for (int i = 0; i < K; i++) {			// ���ڿ����� Ư�� ���� ������ �����Ͽ� �׷��� ���� (A->1, B->2, ...)
			cin >> str1 >> str2;
			if (!v.count(str1))
				v[str1] = ++vertice;
			if (!v.count(str2))
				v[str2] = ++vertice;

			graph[v[str1]].push_back(v[str2]);
			graph[v[str2]].push_back(v[str1]);
		}
		cout << '#' << test_case << ' ' << solve();

		fill(visited, visited + 201, 0);
		vertice = 0;

		for (int i = 0; i < 201; i++)
			graph[i].clear();
		v.clear();
		while (!q.empty())
			q.pop();
	}
	return 0;
}