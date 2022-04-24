#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int R, C, K, W, x, y, t, map[22][22];
const int dr[] = {0, 0, -1, 1}, dc[] = {1, -1, 0, 0};       // 동 서 북 남 순서
bool wall[4][22][22];           // wall[0][x][y] : (x, y) 동쪽에 벽, wall[1][x][y] : 서쪽, [2][x][y]: 북, [3][x][y] : 남
vector<pair<int, int>> chk;     // 조사해야 하는 칸 좌표 저장
vector<pair<int, pair<int, int>>> radiator;    // {바람 방향, {r, c}} 형태로 온풍기 저장

void step1()
{
    for (auto &ra : radiator) {
        bool visited[21][21] = {false, };
        int dir = ra.first, r = ra.second.first, c = ra.second.second;
        queue<pair<int, pair<int, int>>> q;     // {온도 상승량, {r, c}}로 저장

        if (!dir || dir == 1) {                 // 바람 방향이 동 or 서일 때
            map[r][c + dc[dir]] += 5;

            q.push({5, {r, c + dc[dir]}});
            while (!q.empty()) {
                int incre = q.front().first;
                int cur_r = q.front().second.first;
                int cur_c = q.front().second.second;
                q.pop();

                int new_c = cur_c + dc[dir];
                if (incre == 1 || new_c < 1 || new_c > C) continue;

                // 동쪽일 땐 ↗, 서쪽일 땐 ↖ 이동 시 (↑ + → 또는 ↑ + ←)
                if (cur_r - 1 >= 1 && !visited[cur_r - 1][new_c] && !wall[2][cur_r][cur_c] && !wall[dir][cur_r - 1][cur_c]) {
                    q.push({incre - 1, {cur_r - 1, new_c}});
                    map[cur_r - 1][new_c] += (incre - 1);
                    visited[cur_r - 1][new_c] = true;
                }

                // 동쪽일 땐 →, 서쪽일 땐 ← 이동 시
                if (!visited[cur_r][new_c] && !wall[dir][cur_r][cur_c]) {
                    q.push({incre - 1, {cur_r, new_c}});
                    map[cur_r][new_c] += (incre - 1);
                    visited[cur_r][new_c] = true;
                }

                // 동쪽일 땐 ↘, 서쪽일 땐 ↙ 이동 시 (↓ + → 또는 ↓ + ←)
                if (cur_r + 1 <= R && !visited[cur_r + 1][new_c] && !wall[3][cur_r][cur_c] && !wall[dir][cur_r + 1][cur_c]) {
                    q.push({incre - 1, {cur_r + 1, new_c}});
                    map[cur_r + 1][new_c] += (incre - 1);
                    visited[cur_r + 1][new_c] = true;
                }
            }
        }
        else {                                  // 바람 방향이 북 or 남일 때
            map[r + dr[dir]][c] += 5;

            q.push({5, {r + dr[dir], c}});
            while (!q.empty()) {
                int incre = q.front().first;
                int cur_r = q.front().second.first;
                int cur_c = q.front().second.second;
                q.pop();

                int new_r = cur_r + dr[dir];
                if (incre == 1 || new_r < 1 || new_r > R) continue;

                // 북쪽일 땐 ↖, 남쪽일 땐 ↙ 이동 시 (← + ↑ 또는 ← + ↓)
                if (cur_c - 1 >= 1 && !visited[new_r][cur_c - 1] && !wall[1][cur_r][cur_c] && !wall[dir][cur_r][cur_c - 1]) {
                    q.push({incre - 1, {new_r, cur_c - 1}});
                    map[new_r][cur_c - 1] += (incre - 1);
                    visited[new_r][cur_c - 1] = true;
                }

                // 북쪽일 땐 ↑, 남쪽일 땐 ↑ 이동 시
                if (!visited[new_r][cur_c] && !wall[dir][cur_r][cur_c]) {
                    q.push({incre - 1, {new_r, cur_c}});
                    map[new_r][cur_c] += (incre - 1);
                    visited[new_r][cur_c] = true;
                }

                // 북쪽일 땐 ↗, 남쪽일 땐 ↘ 이동 시 (→ + ↑ 또는 → + ↓)
                if (cur_c + 1 <= C && !visited[new_r][cur_c + 1] && !wall[0][cur_r][cur_c] && !wall[dir][cur_r][cur_c + 1]) {
                    q.push({incre - 1, {new_r, cur_c + 1}});
                    map[new_r][cur_c + 1] += (incre - 1);
                    visited[new_r][cur_c + 1] = true;
                }
            }
        }
    }
}

void step2()
{
    int change[21][21] = {0, };
    for (int r = R; r >= 1; r--) {                  // 맨 오른쪽 아래에서부터 살핌
        for (int c = C; c >= 1; c--) {
            for (int d = 1; d < 3; d++) {           // 서쪽, 북쪽 순으로 살피면서 벽 없으면 온도 조정
                int new_r = r + dr[d];
                int new_c = c + dc[d];
                if (new_r >= 1 && new_c >= 1 && !wall[d][r][c]) {
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
    for (int r = 1; r <= R; r++)
        for (int c = 1; c <= C; c++) {
            cin >> t;
            if (t > 0 && t < 5) radiator.push_back({--t, {r, c}});
            else if (t == 5) chk.push_back({r, c});
        }
    cin >> W;

    while (W--) {
        cin >> x >> y >> t;
        if (!t) wall[2][x][y] = wall[3][x - 1][y] = true;
        else wall[0][x][y] = wall[1][x][y + 1] = true;
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