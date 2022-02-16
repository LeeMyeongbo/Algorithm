#include <iostream>
#include <vector>
#include <queue>
#define MAX 1000000000
using namespace std;

int V, E, K, u, v, w, visited[20001];
vector<pair<int, int>> graph[20001];                                                    // (도착 정점, 가중치)로 저장
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;     // (가중치 합, 현재 정점)

void dijkstra()
{
    fill(visited, visited + V + 1, MAX);
    visited[K] = 0;
    pq.push({ visited[K], K });

    while (!pq.empty()) {
        pair<int, int> node = pq.top();
        pq.pop();

        for (pair<int, int> p : graph[node.second]) {
            if (visited[p.first] > p.second + node.first) {
                visited[p.first] = p.second + node.first;
                pq.push({ visited[p.first], p.first });
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> V >> E >> K;
    while (E--) {
        cin >> u >> v >> w;
        graph[u].push_back({ v, w });
    }

    dijkstra();
    for (int i = 1; i <= V; i++) {
        if (visited[i] == MAX)
            cout << "INF\n";
        else
            cout << visited[i] << "\n";
    }
    return 0;
}
