#include <iostream>
#define INF 1 << 28
using namespace std;

int N, M, map[501][501], v1, v2, cost;

void init()
{
    for (int i = 1; i <= N; i++) {
        fill(map[i], map[i] + N + 1, INF);
        map[i][i] = 0;
    }
}

void floyd()
{
    for (int pass = 1; pass <= N; pass++)
        for (int start = 1; start <= N; start++)
            for (int end = 1; end <= N; end++)
                map[start][end] = min(map[start][end], map[start][pass] + map[pass][end]);
}

int main()
{
    cin >> N >> M;
    init();

    while (M--) {
        cin >> v1 >> v2 >> cost;
        map[v1][v2] = min(map[v1][v2], cost);
    }
    floyd();

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (map[i][j] == INF)
                cout << "INF" << ' ';
            else
                cout << map[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}
