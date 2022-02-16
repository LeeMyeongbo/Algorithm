#include <iostream>
#define MAX 1000000000
using namespace std;

int n, m, a, b, c, floyd[101][101];

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        fill(floyd[i], floyd[i] + n + 1, MAX);
        floyd[i][i] = 0;
    }

    while (m--) {
        cin >> a >> b >> c;
        floyd[a][b] = min(floyd[a][b], c);
    }

    for (int pass = 1; pass <= n; pass++)
        for (int s = 1; s <= n; s++)
            for (int d = 1; d <= n; d++)
                floyd[s][d] = min(floyd[s][d], floyd[s][pass] + floyd[pass][d]);
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (floyd[i][j] == MAX)
                cout << 0 << ' ';
            else
                cout << floyd[i][j] << ' ';
        }
        cout << "\n";
    }

    return 0;
}
