#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int T, N, M, u, v;
long long len, dij[200001], edge[200001], Ans;      // edge[i] : i번 건물로 도착 시 어떤 가중치의 간선을 이용했는지 저장
vector<pair<int, long long>> graph[200001];         // (도착 건물 번호, 길이)로 저장
priority_queue<pair<long long, int>> pq;            // (길이 합, 현재 건물 번호)로 저장

long long solve()
{
    fill(edge, edge + N + 1, 0);
    fill(dij, dij + N + 1, -1);
    dij[1] = 0;
    pq.push({ 0, 1 });

    while (!pq.empty()) {
        long long sum = -pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        for (auto& e : graph[cur]) {
            if (dij[e.first] == -1 || dij[e.first] > sum + e.second) {              // 방문한 적 없거나 길이 합이 더 작다면
                edge[e.first] = e.second;
                dij[e.first] = sum + e.second;
                pq.push({ -dij[e.first], e.first });
            }
            else if (dij[e.first] == sum + e.second && edge[e.first] > e.second)    // 길이 합은 같은데 더 작은 간선 이용 가능하다면
                edge[e.first] = e.second;
        }
    }
    for (int i = 2; i <= N; i++)
        Ans += edge[i];

    return Ans;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N >> M;
        while (M--) {
            cin >> u >> v >> len;
            graph[u].push_back({ v, len });
            graph[v].push_back({ u, len });
        }

        cout << '#' << test_case << ' ' << solve() << "\n";
        for (int i = 1; i <= N; i++)
            graph[i].clear();
        Ans = 0;
    }
    return 0;
}
