#include <iostream>
#include <queue>
using namespace std;

int N, M, K, d, map[20][20], r, c, cube[6] = {1, 2, 3, 4, 5, 6};  // 순서대로 윗면, 북쪽면, 동쪽면, 서쪽면, 남쪽면, 아랫면
const int dr[] = {0, 0, 1, -1}, dc[] = {1, -1, 0, 0};             // d : 0=동쪽, 1=남쪽, 2=서쪽, 3=북쪽

void moveEast()             // 윗면->동쪽면, 동쪽면->아랫면, 아랫면->서쪽면, 서쪽면->윗면
{
    int tmp = cube[0];
    cube[0] = cube[3];
    cube[3] = cube[5];
    cube[5] = cube[2];
    cube[2] = tmp;
}

void moveWest()             // 윗면->서쪽면, 서쪽면->아랫면, 아랫면->동쪽면, 동쪽면->윗면
{
    int tmp = cube[0];
    cube[0] = cube[2];
    cube[2] = cube[5];
    cube[5] = cube[3];
    cube[3] = tmp;
}

void moveSouth()            // 윗면->남쪽면, 남쪽면->아랫면, 아랫면->북쪽면, 북쪽면->윗면
{
    int tmp = cube[0];
    cube[0] = cube[1];
    cube[1] = cube[5];
    cube[5] = cube[4];
    cube[4] = tmp;
}

void moveNorth()            // 윗면->북쪽면, 북쪽면->아랫면, 아랫면->남쪽면, 남쪽면->윗면
{
    int tmp = cube[0];
    cube[0] = cube[4];
    cube[4] = cube[5];
    cube[5] = cube[1];
    cube[1] = tmp;
}

int chk(int B)              // B랑 같은 숫자면서 인접한 칸 개수 헤아림
{
    queue<pair<int, int>> q;
    int cnt = 0;
    bool visited[20][20] = {false, };

    q.push({r, c});
    visited[r][c] = true;

    while (!q.empty()) {
        int cur_r = q.front().first;
        int cur_c = q.front().second;
        q.pop();

        cnt++;
        for (int d = 0; d < 4; d++) {
            int R = cur_r + dr[d];
            int C = cur_c + dc[d];
            if (R >= 0 && R < N && C >= 0 && C < M && !visited[R][C] && map[R][C] == B) {
                q.push({R, C});
                visited[R][C] = true;
            }
        }
    }
    return cnt;
}

int main()
{
    int ans = 0;
    cin >> N >> M >> K;
    for (int r = 0; r < N; r++) 
        for (int c = 0; c < M; c++)
            cin >> map[r][c];
    
    while (K--) {
        if (!d) {                   // 동쪽으로 이동할 경우
            if (c + 1 >= M) {       // 동쪽으로 이동할 수 있는 칸이 없을 경우 서쪽으로 이동
                d = 2, c--;
                moveWest();
            }
            else {
                c++;
                moveEast();
            }
        }
        else if (d == 1) {          // 남쪽으로 이동 시
            if (r + 1 >= N) {       // 이동할 수 있는 칸 없으면 북쪽 이동
                d = 3, r--;
                moveNorth();
            }
            else {
                r++;
                moveSouth();
            }
        }
        else if (d == 2) {          // 서쪽
            if (c - 1 < 0) {        // 칸 없으면 동쪽
                d = 0, c++;
                moveEast();
            }
            else {
                c--;
                moveWest();
            }
        }
        else {                      // 북쪽
            if (r - 1 < 0) {        // 칸 없으면 남쪽
                d = 1, r++;
                moveSouth();
            }
            else {
                r--;
                moveNorth();
            }
        }

        if (cube[5] > map[r][c])            // 주사위 아랫면 숫자가 보드 숫자보다 크면 시계방향 전환
            d = (d + 1) % 4;
        else if (cube[5] < map[r][c])       // 더 작으면 반시계 방향 전환
            d = (d + 3) % 4;
        ans += (chk(map[r][c]) * map[r][c]);
    }

    cout << ans;
    return 0;
}