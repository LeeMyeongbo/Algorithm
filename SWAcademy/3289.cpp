#include <iostream>
#include <vector>
using namespace std;

int T, n, m, cal, a, b, parent[1000001];

int Find(int v)
{
    if (parent[v] == v)
        return v;
    return parent[v] = Find(parent[v]);
}

void Union(int v1, int v2)
{
    v1 = Find(v1);
    v2 = Find(v2);
    parent[v1] = v2;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            parent[i] = i;

        cout << '#' << test_case << ' ';
        for (int i = 0; i < m; i++) {
            cin >> cal >> a >> b;
            if (!cal)
                Union(a, b);
            else
                Find(a) == Find(b) ? cout << 1 : cout << 0;
        }
        cout << "\n";
    }
    return 0;
}
