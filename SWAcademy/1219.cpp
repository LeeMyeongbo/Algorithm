#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int t, route, v1, v2;

bool bfs(vector<int> graph[])
{
	queue<int> q;
	bool visited[100] = { false, };
	q.push(0);
	visited[0] = true;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		if (cur == 99)
			return true;

		for (int i : graph[cur]) {
			if (!visited[i]) {
				q.push(i);
				visited[i] = true;
			}
		}
	}
	
	return false;
}

int main(int argc, char** argv)
{
	while (true) {
		cin >> t >> route;
		if (cin.eof())
			return 0;

		vector<int> graph[100];
		for (int i = 0; i < route; i++) {
			cin >> v1 >> v2;
			graph[v1].push_back(v2);
		}

		cout << "#" << t << " ";
		if (bfs(graph))
			cout << 1 << endl;
		else
			cout << 0 << endl;
	}
}