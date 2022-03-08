#include <iostream>
using namespace std;

int T, N, K, M, u, v, Max;
bool graph[11][11], visited[11];

void dfs(int depth, int cur)
{
    Max = max(Max, depth);
    for (int i = 1; i <= N; i++) {
        if (graph[cur][i] && !visited[i]) {
            visited[i] = true;
            dfs(depth + 1, i);
            visited[i] = false;
        }
    }
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N >> K;

        while (K--) {
            cin >> M >> u;

            for (int i = 0; i < M - 1; i++) {
                cin >> v;
                graph[u][v] = true;
                u = v;
            }
        }
        
        cout << '#' << test_case << ' ';
        for (int i = 1; i <= N; i++) {
            int num = 0;
            for (int j = 1; j <= N; j++)
                if (graph[i][j])
                    num++;
            cout << num << ' ';

            graph[0][i] = true;
        }

        dfs(0, 0);
        cout << Max << "\n";
        for (int i = 1; i <= N; i++)
            fill(graph[i], graph[i] + N + 1, false);
        Max = 0;
    }
    return 0;
}
