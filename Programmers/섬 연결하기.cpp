#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int parent[101];

int Find(int v)
{
    if (parent[v] == v)
        return v;
    return parent[v] = Find(parent[v]);
}

bool Union(int v1, int v2)
{
    v1 = Find(v1);
    v2 = Find(v2);

    if (v1 == v2)
        return false;

    parent[v1] = v2;
    return true;
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;

    for (int i = 1; i <= n; i++)
        parent[i] = i;

    vector<pair<int, pair<int, int>>> edges;
    for (auto& c : costs)
        edges.push_back({ c[2], {c[0], c[1]} });
    sort(edges.begin(), edges.end());

    int num = 0;
    for (auto& e : edges) {
        if (Union(e.second.first, e.second.second)) {
            answer += e.first;
            num++;
            if (num == n - 1)
                break;
        }
    }

    return answer;
}
