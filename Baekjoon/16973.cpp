#include <iostream>
#include <queue>
using namespace std;

int map[1001][1001];
bool visited[1001][1001];

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    register int N, M, H, W, Sr, Sc, Fr, Fc;

    cin >> N >> M;
    for (int r = 1; r <= N; r++)
        for (int c = 1; c <= M; c++)
            cin >> map[r][c];
    cin >> H >> W >> Sr >> Sc >> Fr >> Fc;
    
    queue<pair<int, pair<int, int>>> q;     // (이동 횟수, (왼쪽 위 좌표의 r, 왼쪽 위 좌표의 c))
    q.push({0, {Sr, Sc}});
    visited[Sr][Sc] = true;

    while (!q.empty()) {
        int move = q.front().first;
        int r = q.front().second.first;
        int c = q.front().second.second;
        q.pop();

        if (r == Fr && c == Fc) {
            cout << move;
            return 0;
        }

        // 동쪽으로 움직일 때 : c + W가 격자 범위 넘지 않으면서 map[R][c + W] = 0 이면 됨
        if (c + W < M + 1 && !visited[r][c + 1]) {
            bool flag = true;
            for (int R = r; R < r + H; R++) {
                if (map[R][c + W]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                q.push({move + 1, {r, c + 1}});
                visited[r][c + 1] = true;
            }
        }

        // 서쪽으로 움직일 때 : c - 1이 격자 범위 넘지 않으면서 map[R][c - 1] = 0 이면 됨
        if (c - 1 > 0 && !visited[r][c - 1]) {
            bool flag = true;
            for (int R = r; R < r + H; R++) {
                if (map[R][c - 1]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                q.push({move + 1, {r, c - 1}});
                visited[r][c - 1] = true;
            }
        }

        // 남쪽으로 움직일 때 : r + H가 격자 범위 넘지 않으면서 map[r + H][C] = 0이면 됨
        if (r + H < N + 1 && !visited[r + 1][c]) {
            bool flag = true;
            for (int C = c; C < c + W; C++) {
                if (map[r + H][C]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                q.push({move + 1, {r + 1, c}});
                visited[r + 1][c] = true;
            }
        }

        // 북쪽으로 움직일 때 : r - 1이 격자 범위 넘지 않으면서 map[r - 1][C] = 0이면 됨
        if (r - 1 > 0 && !visited[r - 1][c]) {
            bool flag = true;
            for (int C = c; C < c + W; C++) {
                if (map[r - 1][C]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                q.push({move + 1, {r - 1, c}});
                visited[r - 1][c] = true;
            }
        }
    }
    cout << -1;
    return 0;
}