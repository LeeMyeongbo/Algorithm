#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    register int v1, v2, n, k, s;
    bool map[401][401];                 // map[i][j] : i -> j 순으로 사건이 발생
    memset(map, false, sizeof(map));

    cin >> n >> k;
    while (k--)
    {
        cin >> v1 >> v2;
        map[v1][v2] = true;
    }

    for (int pass = 1; pass <= n; pass++)
        for (int start = 1; start <= n; start++)
            for (int end = 1; end <= n; end++)
                if (map[start][pass] && map[pass][end])
                    map[start][end] = true;

    cin >> s;
    while (s--)
    {
        cin >> v1 >> v2;

        if (map[v1][v2]) cout << -1 << '\n';
        else if (map[v2][v1]) cout << 1 << '\n';
        else cout << 0 << '\n';
    }

    return 0;
}
