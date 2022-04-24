#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int R, C, K, W, x, y, t, map[21][21];
const int dr[] = {-1, 0}, dc[] = {0, 1};
bool wall[2][21][21];               // wall[0][x][y] : (x, y) 위에 가로 벽, wall[1][x][y] : (x, y) 오른쪽에 세로 벽
vector<pair<int, int>> chk;         // 조사해야 하는 칸 좌표 저장
vector<pair<int, pair<int, int>>> radiator;                     // {바람 방향, {r, c}} 형태로 온풍기 저장

void step1()
{
    for (auto &ra : radiator) {
        bool visited[21][21] = {false, };
        int dir = ra.first, r = ra.second.first, c = ra.second.second;
        queue<pair<int, pair<int, int>>> q;     // {온도 상승량, {r, c}}로 저장

        if (dir == 1) {             // 바람이 동쪽
            map[r][c + 1] += 5;

            q.push({5, {r, c + 1}});
            while (!q.empty()) {
                int incre = q.front().first;
                int cur_r = q.front().second.first;
                int cur_c = q.front().second.second;
                q.pop();

                if (incre == 1) continue;

                // ↗ 이동 시
                if (cur_r - 1 >= 1 && cur_c + 1 <= C && !visited[cur_r - 1][cur_c + 1] && !wall[0][cur_r][cur_c] && !wall[1][cur_r - 1][cur_c]) {
                    q.push({incre - 1, {cur_r - 1, cur_c + 1}});
                    map[cur_r - 1][cur_c + 1] += (incre - 1);
                    visited[cur_r - 1][cur_c + 1] = true;
                }

                // → 이동 시
                if (cur_c + 1 <= C && !visited[cur_r][cur_c + 1] && !wall[1][cur_r][cur_c]) {
                    q.push({incre - 1, {cur_r, cur_c + 1}});
                    map[cur_r][cur_c + 1] += (incre - 1);
                    visited[cur_r][cur_c + 1] = true;
                }

                // ↘ 이동 시
                if (cur_r + 1 <= R && cur_c + 1 <= C && !visited[cur_r + 1][cur_c + 1] && !wall[0][cur_r + 1][cur_c] && !wall[1][cur_r + 1][cur_c]) {
                    q.push({incre - 1, {cur_r + 1, cur_c + 1}});
                    map[cur_r + 1][cur_c + 1] += (incre - 1);
                    visited[cur_r + 1][cur_c + 1] = true;
                }
            }
        }
        else if (dir == 2) {        // 바람이 서쪽
            map[r][c - 1] += 5;

            q.push({5, {r, c - 1}});
            while (!q.empty()) {
                int incre = q.front().first;
                int cur_r = q.front().second.first;
                int cur_c = q.front().second.second;
                q.pop();

                if (incre == 1) continue;

                // ↖ 이동 시
                if (cur_r - 1 >= 1 && cur_c - 1 >= 1 && !visited[cur_r - 1][cur_c - 1] && !wall[0][cur_r][cur_c] && !wall[1][cur_r - 1][cur_c - 1]) {
                    q.push({incre - 1, {cur_r - 1, cur_c - 1}});
                    map[cur_r - 1][cur_c - 1] += (incre - 1);
                    visited[cur_r - 1][cur_c - 1] = true;
                }

                // ← 이동 시
                if (cur_c - 1 >= 1 && !visited[cur_r][cur_c - 1] && !wall[1][cur_r][cur_c - 1]) {
                    q.push({incre - 1, {cur_r, cur_c - 1}});
                    map[cur_r][cur_c - 1] += (incre - 1);
                    visited[cur_r][cur_c - 1] = true;
                }

                // ↙ 이동 시
                if (cur_r + 1 <= R && cur_c - 1 >= 1 && !visited[cur_r + 1][cur_c - 1] && !wall[0][cur_r + 1][cur_c] && !wall[1][cur_r + 1][cur_c - 1]) {
                    q.push({incre - 1, {cur_r + 1, cur_c - 1}});
                    map[cur_r + 1][cur_c - 1] += (incre - 1);
                    visited[cur_r + 1][cur_c - 1] = true;
                }
            }
        }
        else if (dir == 3) {        // 바람이 북쪽
            map[r - 1][c] += 5;

            q.push({5, {r - 1, c}});
            while (!q.empty()) {
                int incre = q.front().first;
                int cur_r = q.front().second.first;
                int cur_c = q.front().second.second;
                q.pop();

                if (incre == 1) continue;

                // ↖ 이동 시
                if (cur_r - 1 >= 1 && cur_c - 1 >= 1 && !visited[cur_r - 1][cur_c - 1] && !wall[0][cur_r][cur_c - 1] && !wall[1][cur_r][cur_c - 1]) {
                    q.push({incre - 1, {cur_r - 1, cur_c - 1}});
                    map[cur_r - 1][cur_c - 1] += (incre - 1);
                    visited[cur_r - 1][cur_c - 1] = true;
                }

                // ↑ 이동 시
                if (cur_r - 1 >= 1 && !visited[cur_r - 1][cur_c] && !wall[0][cur_r][cur_c]) {
                    q.push({incre - 1, {cur_r - 1, cur_c}});
                    map[cur_r - 1][cur_c] += (incre - 1);
                    visited[cur_r - 1][cur_c] = true;
                }

                // ↗ 이동 시
                if (cur_r - 1 >= 1 && cur_c + 1 <= C && !visited[cur_r - 1][cur_c + 1] && !wall[0][cur_r][cur_c + 1] && !wall[1][cur_r][cur_c]) {
                    q.push({incre - 1, {cur_r - 1, cur_c + 1}});
                    map[cur_r - 1][cur_c + 1] += (incre - 1);
                    visited[cur_r - 1][cur_c + 1] = true;
                }
            }
        }
        else {                      // 바람이 남쪽
            map[r + 1][c] += 5;

            q.push({5, {r + 1, c}});
            while (!q.empty()) {
                int incre = q.front().first;
                int cur_r = q.front().second.first;
                int cur_c = q.front().second.second;
                q.pop();

                if (incre == 1) continue;

                // ↙ 이동 시
                if (cur_r + 1 <= R && cur_c - 1 >= 1 && !visited[cur_r + 1][cur_c - 1] && !wall[0][cur_r + 1][cur_c - 1] && !wall[1][cur_r][cur_c - 1]) {
                    q.push({incre - 1, {cur_r + 1, cur_c - 1}});
                    map[cur_r + 1][cur_c - 1] += (incre - 1);
                    visited[cur_r + 1][cur_c - 1] = true;
                }

                // ↓ 이동 시
                if (cur_r + 1 <= R && !visited[cur_r + 1][cur_c] && !wall[0][cur_r + 1][cur_c]) {
                    q.push({incre - 1, {cur_r + 1, cur_c}});
                    map[cur_r + 1][cur_c] += (incre - 1);
                    visited[cur_r + 1][cur_c] = true;
                }

                // ↘ 이동 시
                if (cur_r + 1 <= R && cur_c + 1 <= C && !visited[cur_r + 1][cur_c + 1] && !wall[0][cur_r + 1][cur_c + 1] && !wall[1][cur_r][cur_c]) {
                    q.push({incre - 1, {cur_r + 1, cur_c + 1}});
                    map[cur_r + 1][cur_c + 1] += (incre - 1);
                    visited[cur_r + 1][cur_c + 1] = true;
                }
            }
        }
    }
}

void step2()
{
    int change[21][21] = {0, };
    for (int r = R; r >= 1; r--) {
        for (int c = 1; c <= C; c++) {
            for (int d = 0; d < 2; d++) {           // 위쪽, 오른쪽 순으로 살피면서 벽 없으면 온도 조정
                int new_r = r + dr[d];
                int new_c = c + dc[d];
                if (new_r >= 1 && new_c <= C && !wall[d][r][c]) {
                    if (map[r][c] > map[new_r][new_c]) {
                        int diff = (map[r][c] - map[new_r][new_c]) / 4;
                        change[r][c] -= diff, change[new_r][new_c] += diff;
                    }
                    else {
                        int diff = (map[new_r][new_c] - map[r][c]) / 4;
                        change[r][c] += diff, change[new_r][new_c] -= diff;
                    }
                }
            }
        }
    }

    // 온도 변화 + 가장자리 온도 1도씩 감소
    for (int r = 1; r <= R; r++)
        for (int c = 1; c <= C; c++) {
            map[r][c] += change[r][c];
            if ((r == 1 || r == R || c == 1 || c == C) && map[r][c])
                map[r][c]--;
        }
}

bool check()
{
    for (auto &p : chk)
        if (map[p.first][p.second] < K)
            return false;
    
    return true;
}

int main()
{
    cin >> R >> C >> K;
    for (int r = 1; r <= R; r++) {
        for (int c = 1; c <= C; c++) {
            cin >> map[r][c];
            if (map[r][c] > 0 && map[r][c] < 5) radiator.push_back({map[r][c], {r, c}});
            else if (map[r][c] == 5) chk.push_back({r, c});
            map[r][c] = 0;
        }
    }
    cin >> W;

    while (W--) {
        cin >> x >> y >> t;
        if (!t) wall[0][x][y] = true;
        else wall[1][x][y] = true;
    }

    for (int i = 1; i <= 100; i++) {
        step1();
        step2();
        if (check()) {
            cout << i;
            return 0;
        }
    }

    cout << 101;
    return 0;
}