#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, weight, parent[1025];
vector<pair<int, pair<int, int>>> edges;
vector<int> graph[1025];

int Find(int n)
{
    if (parent[n] == n)
        return n;
    return parent[n] = Find(parent[n]);
}

bool Union(int n1, int n2)
{
    n1 = Find(n1);
    n2 = Find(n2);
    if (n1 == n2)
        return false;
    if (n1 > n2)
        swap(n1, n2);
    parent[n2] = n1;
    return true;
}

void solve()
{
    sort(edges.begin(), edges.end());
    for (auto& e : edges) {
        if (Union(e.second.first, e.second.second)) {
            graph[e.second.first].push_back(e.second.second);
            graph[e.second.second].push_back(e.second.first);
        }
    }
    for (int i = 1; i <= N; i++) {
        sort(graph[i].begin(), graph[i].end());
        cout << graph[i].size() << " ";
        for (int& v : graph[i])
            cout << v << " ";
        cout << "\n";
    }
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    for (int i = 1; i <= N; i++)
        parent[i] = i;
    
    for (int i = 1; i < N; i++) {
        for (int j = i + 1; j <= N; j++) {
            cin >> weight;
            edges.push_back({weight, {i, j}});
        }
    }
    solve();
	return 0;
}