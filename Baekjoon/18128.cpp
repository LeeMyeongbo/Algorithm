#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int N, W, x, y, watering[1000][1000];
const int dr[] = {0, 0, 1, -1, -1, -1, 1, 1}, dc[] = {1, -1, 0, 0, -1, 1, -1, 1};
char map[1000][1001];

bool chk(int limit)
{
    queue<pair<int, int>> q;
    bool visited[1000][1000] = {false, };

    q.push({0, 0});
    visited[0][0] = true;

    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        for (int d = 0; d < 8; d++) {
            int R = r + dr[d], C = c + dc[d];
            if (R >= 0 && R < N && C >= 0 && C < N && map[R][C] == '1') {
                if (R == N - 1 && C == N - 1)
                    return true;
                else if (!visited[R][C] && watering[R][C] <= limit) {
                    q.push({R, C});
                    visited[R][C] = true;
                }
            }
        }
    }

    return false;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    memset(watering, -1, sizeof(watering));
    cin >> N >> W;

    queue<pair<int, pair<int, int>>> q;
    while (W--) {
        cin >> x >> y;
        watering[--x][--y] = 0;
        q.push({0, {x, y}});
    }

    for (int i = 0; i < N; i++)
        cin >> map[i];
    
    int Min = 0, Max = 0, ans = -1;
    while (!q.empty()) {                    // 물 퍼지면서 각 지점마다 어느 시점에 물이 도달하는 지 저장
        int day = q.front().first;
        int r = q.front().second.first;
        int c = q.front().second.second;
        q.pop();

        Max = max(Max, day);
        for (int d = 0; d < 4; d++) {
            int R = r + dr[d], C = c + dc[d];
            if (R >= 0 && R < N && C >= 0 && C < N && watering[R][C] == -1) {
                watering[R][C] = day + 1;
                q.push({day + 1, {R, C}});
            }
        }
    }

    while (Min <= Max) {                    // 이후 이분탐색으로 치삼이가 목표 지점에 도달할 수 있는 최소 시간 구함
        int mid = (Min + Max) / 2;
        if (chk(mid)) {
            ans = mid;
            Max = mid - 1;
        }
        else
            Min = mid + 1;
    }

    cout << ans;
    return 0;
}