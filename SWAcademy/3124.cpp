#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int T, V, E, A, B, parent[100001];
long long C, Ans;
vector<pair<long long, pair<int, int>>> edges;

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
    if (v1 != v2) {
        parent[v1] = v2;
        return true;
    }
    return false;
}

long long solve()
{
    int e = 0;
    sort(edges.begin(), edges.end());

    for (auto& edge : edges) {
        if (Union(edge.second.first, edge.second.second)) {
            Ans += edge.first;
            e++;
        }
        if (e == V - 1)
            return Ans;
    }
    return -1;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> V >> E;
        for (int i = 1; i <= V; i++)
            parent[i] = i;

        while (E--) {
            cin >> A >> B >> C;
            edges.push_back({ C, {A, B} });
        }
        cout << '#' << test_case << ' ' << solve() << "\n";

        Ans = 0;
        edges.clear();
    }
    return 0;
}
