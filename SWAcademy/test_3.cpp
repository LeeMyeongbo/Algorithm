#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int T, N, M, a, b, n1, n2;
bool confront[1001];
vector<int> graph[1001];
struct Node {
	char country;
	int time, index;
};
queue<Node> q;
Node occupy[1001];

void BFS()
{
	while (!q.empty()) {
		Node node = q.front();
		q.pop();

		if (confront[node.index])
			continue;

		for (int i : graph[node.index]) {
			if (confront[i])
				continue;
			if (!occupy[i].index) {
				occupy[i] = { node.country, node.time + 1, i };
				q.push(occupy[i]);
			}
			else if (occupy[i].time == node.time + 1 && occupy[i].country != node.country) {
				confront[i] = true;
			}
		}
	}
}

int main()
{
	cin >> T;

	for (int t = 1; t <= T; t++) {
		cin >> N >> M >> a >> b;

		for (int m = 0; m < M; m++) {
			cin >> n1 >> n2;
			graph[n1].push_back(n2);
			graph[n2].push_back(n1);
		}
		occupy[a] = { 'a', 1, a };
		occupy[b] = { 'b', 1, b };
		q.push(occupy[a]);
		q.push(occupy[b]);

		BFS();
		
		int A = 0, C = 0, P = 0;
		for (int i = 1; i <= N; i++) {
			if (confront[i])
				C++;
			else if (!occupy[i].time)
				P++;
			else if (occupy[i].country == 'a')
				A++;
		}

		int need = N % 2 == 0 ? N / 2 : N / 2 + 1;
		if (A + C + P < need)
			cout << '#' << t << ' ' << C << ' ' << - 1 << endl;
		else
			cout << '#' << t << ' ' << C << ' ' << need - A << endl;

		for (int i = 1; i <= N; i++) {
			confront[i] = false;
			graph[i].clear();
			occupy[i] = { 0, 0, 0 };
		}
	}
	return 0;
}