#include <iostream>
#include <queue>
using namespace std;

int T, R, C, map[50][50];
const int dr[] = {0, 0, 1, -1}, dc[] = {1, -1, 0, 0};

int bfs(int r, int c)               // 현재 위치(r, c)에서 비가 내릴 때 높이 변화 발생
{
    queue<pair<int, int>> q;
    bool visited[50][50] = {false, };
    int Min = 1001, sum = 0;

    q.push({r, c});
    visited[r][c] = true;

    while (!q.empty()) {
        int cur_r = q.front().first;
        int cur_c = q.front().second;
        q.pop();

        if (!cur_r || !cur_c || cur_r == R - 1 || cur_c == C - 1)                   // 가장자리까지 물이 이동한다면 실패!
            return 0;
        
        for (int d = 0; d < 4; d++) {
            int new_r = cur_r + dr[d];
            int new_c = cur_c + dc[d];
            if (new_r >= 0 && new_r < R && new_c >= 0 && new_c < C) {
                if (!visited[new_r][new_c] && map[new_r][new_c] <= map[r][c]) {     // 현재 탐색 위치보다 높이가 낮다면 물 이동
                    q.push({new_r, new_c});
                    visited[new_r][new_c] = true;
                }
                else if (map[new_r][new_c] > map[r][c])                             // 더 높은 곳이라면 그 최솟값 저장
                    Min = min(Min, map[new_r][new_c]);
            }
        }
    }

    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            if (visited[i][j]) {                        // 물이 이동할 수 있는 곳에 Min만큼 물 채움
                sum += (Min - map[i][j]);
                map[i][j] = Min;
            }
    
    return sum;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test = 1; test <= T; test++) {
        int ans = 0;
        cin >> R >> C;
        for (int r = 0; r < R; r++)
            for (int c = 0; c < C; c++)
                cin >> map[r][c];
        
        for (int r = 1; r < R - 1; r++) {
            for (int c = 1; c < C - 1; c++)
                ans += bfs(r, c);
        }

        cout << "Case #" << test << ": " << ans << "\n";
    }

    return 0;
}