#include <iostream>
#include <queue>
using namespace std;

int N, M, map[1000][1000], restaurant, graph[21][21], ans = -1;
const int dr[] = {0, 0, 1, -1}, dc[] = {1, -1, 0, 0};
char ch;
pair<int, int> rest[21];                // 시작 좌표 = rest[0], 그 외 = 식당 좌표

void makeGraph()
{
    queue<pair<int, pair<int, int>>> q;
    for (register int v = 0; v < restaurant; v++) {    // 시작 좌표 및 식당들 간에 최단 거리를 모두 구해서 저장
        bool visited[1000][1000] = {false, };

        q.push({0, rest[v]});
        visited[rest[v].first][rest[v].second] = true;

        while (!q.empty()) {
            int dist = q.front().first;
            int r = q.front().second.first;
            int c = q.front().second.second;
            q.pop();

            if (map[r][c] > v) graph[v][map[r][c]] = graph[map[r][c]][v] = dist;

            for (register int d = 0; d < 4; d++) {
                int R = r + dr[d], C = c + dc[d];
                if (R >= 0 && R < N && C >= 0 && C < M && map[R][C] != -1 && !visited[R][C]) {
                    q.push({dist + 1, {R, C}});
                    visited[R][C] = true;
                }
            }
        }
    }
}

void getMin(int depth, int cur, int sum)            // 순열 방식으로 5개 식당 방문할 때의 최단 거리 도출
{
    static bool visited[21] = {false, };
    if (depth == 5) {
        if (ans == -1)
            ans = sum;
        ans = min(ans, sum);
        return;
    }

    for (int i = 1; i <= restaurant; i++) {
        if (!visited[i] && graph[cur][i]) {         // 방문하지 않았으면서 경로가 있는 경우에만 깊이 들어감
            visited[i] = true;
            getMin(depth + 1, i, sum + graph[cur][i]);
            visited[i] = false;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N >> M;

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            cin >> ch;
            if (ch == 'X') map[r][c] = -1;
            else if (ch == 'K') {
                map[r][c] = ++restaurant;
                rest[restaurant] = {r, c};
            }
            else if (ch == 'S') rest[0] = {r, c};
        }
    }
    makeGraph();
    getMin(0, 0, 0);
    
    cout << ans;
    return 0;
}