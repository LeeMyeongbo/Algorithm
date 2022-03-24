#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cstring>
using namespace std;

int N, M, K, S, D, a, b, w, p[30000], dij[1000][1001];  // dij[i][j] : i개의 간선을 지나 j번 정점에 도달하는 최단 거리 저장
vector<pair<int, int>> graph[1001], dest;               // graph : (연결된 정점, 거리 합), dest : (D까지의 최소 거리, D에 도달하기까지 거친 간선 수)

void dijkstra()
{
    priority_queue<tuple<int, int, int>> pq;  // (-거리 합, 현재 정점, 거친 간선 수)로 저장
    memset(dij, -1, sizeof(dij));
    dij[0][S] = 0;
    pq.push({ 0, S, 0 });

    while (!pq.empty()) {
        int sum , cur, cnt;
        tie(sum, cur, cnt) = pq.top();
        sum = -sum;
        pq.pop();

        if ((dij[cnt][cur] != -1 && sum > dij[cnt][cur]) || cur == D)
            continue;

        for (auto& e : graph[cur]) {
            if (cnt + 1 < 1000 && (dij[cnt + 1][e.first] == -1 || dij[cnt + 1][e.first] > sum + e.second)) {
                dij[cnt + 1][e.first] = sum + e.second;
                pq.push({ -dij[cnt + 1][e.first], e.first, cnt + 1 });
            }
        }
    }

    int Max = (int)1e9;
    for (int i = 1; i < 1000; i++) {                // 거친 간선 수가 많지만 전체 통행료가 더 적으면 저장
        if (dij[i][D] != -1 && dij[i][D] < Max) {
            dest.push_back({ dij[i][D], i });
            Max = dij[i][D];
        }
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N >> M >> K >> S >> D;
    while (M--) {
        cin >> a >> b >> w;
        graph[a].push_back({ b, w });
        graph[b].push_back({ a, w });
    }
    for (int i = 0; i < K; i++)
        cin >> p[i];
    for (int i = 1; i < K; i++)
        p[i] += p[i - 1];

    dijkstra();

    cout << dest.back().first << '\n';

    int start = dest.size() - 1;
    for (int i = 0; i < K; i++) {
        int result = (int)1e9;
        for (int j = start; j >= 0; j--) {          // 세금 인상이 누적될수록 굳이 모든 경로들 살필 필요 없이 특정 간선 개수의 경로부터 비교 ㄱㄱ
            if (result > dest[j].first + dest[j].second * p[i]) {
                result = dest[j].first + dest[j].second * p[i];
                start = j;
            }
        }
        cout << result << '\n';
    }

    return 0;
}
