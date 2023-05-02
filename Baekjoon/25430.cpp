/* 부분 점수밖에 못 긁음(차후 수정 예정) */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
    long long dist;                     // dist : 지금까지 이동거리
    int pre_len, cur, idx;              // pre_len : 이전 통로 길이, cur : 현재 커널, idx : 다음에 이용할 통로의 index

    bool operator<(const Node& n) const {
        if (dist > n.dist)
            return true;
        else if (dist == n.dist)
            return pre_len > n.pre_len;

        return false;
    }
};
priority_queue<Node> pq;
vector<pair<int, int>> graph[50001];     // graph[n][i] = (커널 v로의 이동통로 길이, 커널 v) -> 오름차순 정렬
vector<long long> dij[50001];            // dij[n][i] = graph[n]의 i번 인덱스로 왔을 때 총 이동 거리          
int Start, End;

long long solve(int N)
{
    register long long ans = INT64_MAX;
    if (!dij[Start].size())
        return Start == End ? 0 : ans;

    dij[Start][0] = 0;
    pq.push({ 0, 0, Start, 0 });

    while (!pq.empty())
    {
        register Node n = pq.top();
        pq.pop();

        if (n.idx >= (int)graph[n.cur].size() || n.dist > dij[n.cur][n.idx])
            continue;

        register int len = graph[n.cur][n.idx].first;
        register int next = graph[n.cur][n.idx].second;
        register int curr_idx = lower_bound(graph[next].begin(), graph[next].end(), make_pair(len, n.cur)) - graph[next].begin();
        register int next_idx = upper_bound(graph[next].begin(), graph[next].end(), make_pair(len, N + 1)) - graph[next].begin();

        if (dij[next][curr_idx] > n.dist + len)                                        // 현재 통로로 이동 가능할 때
        {
            dij[next][curr_idx] = n.dist + len;
            pq.push({ dij[next][curr_idx], len, next, next_idx });
        }

        if (n.idx + 1 < (int)graph[n.cur].size() && dij[n.cur][n.idx + 1] > n.dist)    // 현재 커널과 연결된 다른 통로들도 살핌
        {
            dij[n.cur][n.idx + 1] = n.dist;
            pq.push({ n.dist, n.pre_len, n.cur, n.idx + 1  });
        }
    }
    for (long long& l : dij[End])
        ans = min(ans, l);

    return ans;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    register int N, M, u, v, len;

    cin >> N >> M;
    while (M--)
    {
        cin >> u >> v >> len;
        graph[u].emplace_back(make_pair(len, v));
        graph[v].emplace_back(make_pair(len, u));
    }
    cin >> Start >> End;

    for (int i = 1; i <= N; i++)
    {
        dij[i] = vector<long long>(graph[i].size(), INT64_MAX);
        sort(graph[i].begin(), graph[i].end());                     // 각 커널마다 통로 길이 오름차순으로 정렬
    }

    long long ans = solve(N);
    ans != INT64_MAX ? cout << ans : cout << "DIGESTA";

    return 0;
}
