#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int T, N, parent[1001];
double E;
vector<pair<long long, pair<int, int>>> edges;
long long x[1001], y[1001];

int Find(int v)
{
    if (v == parent[v])
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
    int num = 0;
    long long sum = 0;

    for (auto& e : edges) {
        if (Union(e.second.first, e.second.second)) {
            sum += e.first;
            num++;
        }
        if (num == N - 1)
            break;
    }
    return (long long)round(sum * E);
}

int main(int argc, char** argv)
{   cin >> T;
    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N;
        for (int i = 1; i <= N; i++) {
            parent[i] = i;
            cin >> x[i];
        }
        for (int i = 1; i <= N; i++)
            cin >> y[i];
        cin >> E;

        for (int i = 1; i < N; i++)
            for (int j = i + 1; j <= N; j++)
                edges.push_back({ (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]), {i, j} });

        sort(edges.begin(), edges.end());

        cout << '#' << test_case << ' ' << solve() << endl;
        edges.clear();
    }
    return 0;
}
