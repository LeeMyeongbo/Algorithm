#include <iostream>
#include <queue>
#include <tuple>
using namespace std;

int n, m, map[500][500];
bool visited[2][10][500][500];              // visited[0] : 낮일 때 check, visited[1] : 밤일 때 check
const int dr[] = {0, 0, 1, -1}, dc[] = {1, -1, 0, 0};

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> map[i][j];
    
    queue<tuple<int, int, int, int>> q;     // (낮(짝수) or 밤(홀수), 해당 낮(밤) 동안 움직인 횟수, r, c)
    q.push({0, 0, 0, 0});
    visited[0][0][0][0] = true;

    while (!q.empty()) {
        int day_night, move, r, c;
        tie(day_night, move, r, c) = q.front();
        q.pop();

        if (r == n - 1 && c == n - 1) {
            string str = day_night % 2 ? "moon" : "sun";                // day/night가 짝수(0 포함)면 낮, 홀수면 밤
            cout << day_night / 2 + 1 << ' ' << str;                    // 몇 번째 날인지도 출력

            return 0;
        }

        int new_m = (move + 1) % m;                                     // 이동 1번 ㄱㄱ (m번 이동하면 다시 0으로)
        int dn = !new_m ? day_night + 1 : day_night;                    // 한 번 이동해서 총 이동횟수가 m이 되면 낮/밤 상태 바뀜
        for (int d = 0; d < 4; d++) {
            int R = r + dr[d], C = c + dc[d];
            if (R >= 0 && R < n && C >= 0 && C < n) {
                if (!map[R][C] && !visited[dn % 2][new_m][R][C]) {      // 방문 안 한 빈 곳 있으면 이동
                    q.push({dn, new_m, R, C});
                    visited[dn % 2][new_m][R][C] = true;
                }
                else if (day_night % 2 && map[R][C]) {                  // 현재 밤이고 근처가 벽인 경우 -> 빈칸 나올 때까지 벽 건너감
                    while (R >= 0 && R < n && C >= 0 && C < n && map[R][C]) {
                        R += dr[d];
                        C += dc[d];
                    }
                    if (R >= 0 && R < n && C >= 0 && C < n && !map[R][C] && !visited[dn % 2][new_m][R][C]) {
                        q.push({dn, new_m, R, C});
                        visited[dn % 2][new_m][R][C] = true;
                    }
                }
            }
        }
    }

    cout << -1;
    return 0;
}