#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<pair<int, pair<int, int>>> graph;     // (간선 길이, (정점1, 정점2))로 저장
int V, E, parent[10001];

int Find(int v)
{
    if (v == parent[v])
        return v;
    
    return parent[v] = Find(parent[v]);
}

void Union(int v1, int v2)
{
    v1 = Find(v1);
    v2 = Find(v2);
    parent[v1] = v2;
}

int main()
{
    cin >> V >> E;
    for (register unsigned int v = 1; v <= V; v++)
        parent[v] = v;
    
    int edge, v1, v2, connected_e = 0, ans = 0;

    for (register unsigned int e = 0; e < E; e++)
    {
        cin >> v1 >> v2 >> edge;
        graph.push_back({edge, {v1, v2}});
    }

    sort(graph.begin(), graph.end());       // 간선들을 가중치 오름차순으로 정렬

    for (register unsigned int e = 0; e < (int)graph.size() && connected_e < V - 1; e++)
    {
        edge = graph[e].first;
        v1 = graph[e].second.first;
        v2 = graph[e].second.second;

        if (Find(v1) != Find(v2))           // 간선들을 가중치가 작은 것부터 하나씩 빼며 MST 형성
        {
            Union(v1, v2);
            ans += edge;
            connected_e++;
        }
    }

    cout << ans;
    return 0;
}