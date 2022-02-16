#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int T, N, way[100001], dest;
bool visited[100001];
struct Node {
	int cur, time, camping_move;
};
struct compare {
	bool operator()(Node n1, Node n2)
	{
		return n1.cur < n2.cur;
	}
};
priority_queue<Node, vector<Node>, compare> q;

int BFS()
{
	q.push({ 0, 0, 0 });
	visited[0] = true;

	while (!q.empty()) {
		Node node = q.top();
		q.pop();

		if (node.camping_move > 15)
			continue;
		if (node.cur == dest)
			return node.time;

		for (int i = node.cur + 1; i <= node.cur + 6; i++) {
			if (i < N && way[i] != 1 && !visited[i]) {
				if (way[i] == 2) {
					q.push({ i, node.time + i - node.cur + 1, node.camping_move + i - node.cur });
					visited[i] = true;
				}
				else if (way[i] == 3) {
					q.push({ i, node.time + i - node.cur, 0 });
					visited[i] = true;
				}
			}
		}
	}
	return -1;
}

int main()
{
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> way[i];
		}
		for (int i = N - 1; i >= 0; i--)
			if (way[i] == 3) {
				dest = i;
				break;
			}

		cout << '#' << t << ' ' << BFS() << endl;

		fill(visited, visited + N, false);
		while (!q.empty())
			q.pop();
	}
	return 0;
}