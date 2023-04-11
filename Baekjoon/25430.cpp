/* 아직 완벽한 코드 x */
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
using namespace std;

priority_queue<tuple<long long, int, int, int>> pq;     // (지금까지의 이동거리, 현재 커널, 다음 커널의 index, 이전 통로 길이)로 저장
vector<pair<int, int>> graph[50001];                    // graph[n][i] = (커널 v로의 이동통로 길이, 커널 v)
vector<long long> dij[50001];                           // dij[n][i] = 커널 n의 i번 인덱스로 갔을 때 총 이동 거리          
int Start, End;

long long solve(int N)
{
    long long ans = INT64_MAX;

    dij[Start][0] = 0;
    pq.push({0, Start, 0, 0});

    while (!pq.empty())
    {
        long long dist = -get<0>(pq.top());
        int cur = get<1>(pq.top());
        int idx = get<2>(pq.top());
        int pre = get<3>(pq.top());
        pq.pop();

        if (cur == End)
        {
            ans = min(ans, dist);
            continue;
        }
        
        if (dist > dij[cur][idx])
            continue;
        
        int len = graph[cur][idx].first;
        int next = graph[cur][idx].second;
        int next_idx = lower_bound(graph[next].begin(), graph[next].end(), pair<int, int>(len, 0)) - graph[next].begin();

        if (len > pre && next_idx < (int)graph[next].size() && dij[next][next_idx] > dist + len)   // 현재 통로로 이동 가능할 때
        {
            dij[next][next_idx] = dist + len;
            pq.push({-dij[next][next_idx], next, next_idx, len});
        }

        if (idx + 1 < (int)graph[cur].size() && dij[cur][idx + 1] > dist)    // 현재 커널과 연결된 다른 통로들도 살핌
        {
            dij[cur][idx + 1] = dist;
            pq.push({-dist, cur, idx + 1, pre});
        }
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N, M, u, v, len;

    cin >> N >> M;
    while (M--)
    {
        cin >> u >> v >> len;
        graph[u].push_back({len, v});
        graph[v].push_back({len, u});
    }
    cin >> Start >> End;

    for (int i = 1; i <= N; i++)
    {
        dij[i] = vector<long long>(graph[i].size(), INT64_MAX);
        sort(graph[i].begin(), graph[i].end());         // 각 커널마다 통로 길이 오름차순으로 정렬
    }

    long long ans = solve(N);
    ans != INT64_MAX ? cout << ans : cout << "DIGESTA";

    return 0;
}