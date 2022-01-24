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

bool BFS(int start)					// 시작점으로부터 인접한 곳으로 BFS 진행하며 1, -1 번갈아 가며 마킹
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
			else if (visited[i] == node.flag)	// 만약 인접한 곳이 현재 위치와 같은 값으로 마킹되어 있다? -> 팀 못 만듬
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
		for (int i = 0; i < K; i++) {			// 문자열마다 특정 정수 값으로 매핑하여 그래프 형성 (A->1, B->2, ...)
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