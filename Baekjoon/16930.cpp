#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

char map[1000][1001];
const int dr[] = {0, 0, 1, -1}, dc[] = {1, -1, 0, 0};
int visited[1000][1000];

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int N, M, K, x1, y1, x2, y2, ans = -1;

    cin >> N >> M >> K;
    for (register int i = 0; i < N; i++)
        cin >> map[i];
    cin >> x1 >> y1 >> x2 >> y2;
    --x1, --y1, --x2, --y2;

    memset(visited, -1, sizeof(visited));
    queue<pair<int, int>> q;                // (현재 r, 현재 c)로 저장

    visited[x1][y1] = 0;
    q.push({x1, y1});

    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        if (r == x2 && c == y2) {
            if (ans == -1)
                ans = visited[r][c];
            
            ans = min(ans, visited[r][c]);
            continue;
        }

        for (register int d = 0; d < 4; d++) {
            int m = 1, R = r + dr[d], C = c + dc[d];

            // 범위 벗어나거나 벽 만날 때까지, 혹은 이동한 곳의 방문 시각이 현재 위치의 방문 시각보다 작거나 같아질 때까지 최대 K번 이동
            while (R >= 0 && R < N && C >= 0 && C < M && map[R][C] == '.' && (visited[R][C] == -1 || visited[R][C] > visited[r][c]) && m <= K) {
                if (visited[R][C] == -1) {      // 아직 방문하지 않은 곳은 현재 위치의 방문 시각 + 1로 저장
                    q.push({R, C});
                    visited[R][C] = visited[r][c] + 1;
                }
                R += dr[d], C += dc[d], ++m;
            }
        }
    }

    cout << ans;
    return 0;
}