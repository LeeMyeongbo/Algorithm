#include <iostream>
using namespace std;

int N, M, a, b, Ans;
bool graph[501][501], inv_graph[501][501];          // 각각 문제에서 주어진 그래프와 그 그래프의 역방향 그래프를 의미

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M;
    while (M--) {
        cin >> a >> b;
        graph[a][b] = inv_graph[b][a] = true;
    }
    
    for (int pass = 1; pass <= N; pass++)
        for (int s = 1; s <= N; s++)
            for (int d = 1; d <= N; d++)
                if (graph[s][pass] && graph[pass][d])
                    graph[s][d] = true;

    for (int pass = 1; pass <= N; pass++)
        for (int s = 1; s <= N; s++)
            for (int d = 1; d <= N; d++)
                if (inv_graph[s][pass] && inv_graph[pass][d])
                    inv_graph[s][d] = true;

    for (int i = 1; i <= N; i++) {
        int cnt = 0;
        for (int j = 1; j <= N; j++) {
            if (graph[i][j] || inv_graph[i][j])     // cnt = i에서 출발하여 도달할 수 있는 정점 개수 + 출발해서 i에 도달하는 정점 개수 
                cnt++;
        }
        if (cnt == N - 1)
            Ans++;
    }

    cout << Ans;
    return 0;
}
