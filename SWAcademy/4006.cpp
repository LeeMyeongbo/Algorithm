#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int T, N, M, s, e, c, parent[50001];

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

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N >> M;
        vector<pair<int, pair<int, int>>> edges;
        int ans = 0, n = 0;

        for (int i = 1; i <= N; i++)
            parent[i] = i;

        while (M--) {
            cin >> s >> e >> c;
            edges.push_back({ c, {s, e} });
        }

        sort(edges.begin(), edges.end());
        for (auto& e : edges) {
            if (Union(e.second.first, e.second.second)) {
                ans += e.first;
                n++;
            }
            if (n == N - 1)
                break;
        }

        cout << '#' << test_case << ' ' << ans << "\n";
    }
    return 0;
}
