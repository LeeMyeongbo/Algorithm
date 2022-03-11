#include <iostream>
#define MAX 1 << 28
using namespace std;

int T, N, M, a, b, c, map[501][501];

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N >> M;

        for (int i = 1; i <= N; i++) {
            fill(map[i], map[i] + N + 1, MAX);
            map[i][i] = 0;
        }
        while (M--) {
            cin >> a >> b >> c;
            map[a][b] = min(map[a][b], c);
        }

        for (int pass = 1; pass <= N; pass++)
            for (int start = 1; start <= N; start++)
                for (int end = 1; end <= N; end++)
                    map[start][end] = min(map[start][end], map[start][pass] + map[pass][end]);
        
        cout << '#' << test_case << ' ';
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++) {
                if (map[i][j] == MAX)
                    cout << -1 << ' ';
                else
                    cout << map[i][j] << ' ';
            }
        cout << '\n';
    }
    return 0;
}
