#include <queue>
#include <cstring>
#include <unordered_map>
using namespace std;

int n, idx, graph[600][600], inv_graph[600][600];
unordered_map<int, int> cityIdx;
priority_queue<pair<int, int>> pq;          // (현재까지 이동거리, 현재 도시)로 저장

int init(int N, int sCity[], int eCity[], int mCost[]) 
{
    memset(graph, 0, sizeof(graph));
    memset(inv_graph, 0, sizeof(inv_graph));
    cityIdx.clear();
    idx = 0;

    n = N;
    for (register int i = 0; i < N; i++)
    {
        if (!cityIdx.count(sCity[i])) cityIdx.insert({ sCity[i], idx++ });
        if (!cityIdx.count(eCity[i])) cityIdx.insert({ eCity[i], idx++ });

        register int sCityIdx = cityIdx[sCity[i]], eCityIdx = cityIdx[eCity[i]];
        graph[sCityIdx][eCityIdx] = mCost[i];
        inv_graph[eCityIdx][sCityIdx] = mCost[i];
    }

    return idx;
}

void add(int sCity, int eCity, int mCost) 
{
    register int sCityIdx = cityIdx[sCity], eCityIdx = cityIdx[eCity];
    graph[sCityIdx][eCityIdx] = mCost;
    inv_graph[eCityIdx][sCityIdx] = mCost;

    return;
}

int dijkstra(int start, int g[600][600])
{
    int dij[600] = { 0, };
    pq.push({ 0, start });

    while (!pq.empty())
    {
        register int dist = -pq.top().first;
        register int curr = pq.top().second;
        pq.pop();

        if (dist > dij[curr])
            continue;

        for (register int to = 0; to < idx; to++)
        {
            if (to != start && g[curr][to] && (!dij[to] || dij[to] > dist + g[curr][to]))
            {
                dij[to] = dist + g[curr][to];
                pq.push({ -dij[to], to });
            }
        }
    }

    register int sum = 0;
    for (int i = 0; i < idx; i++)
        if (i != start) sum += dij[i];

    return sum;
}

int cost(int mHub) 
{
    register int hubIdx = cityIdx[mHub];
    
    return dijkstra(hubIdx, graph) + dijkstra(hubIdx, inv_graph);       // 물류허브에서 출발해 정방향 1번 + 역방향 1번 총 2번 돌림
}
