#include <iostream>
using namespace std;

int N, start_r, start_c, Ans = -1;
const int dr[] = {0, 0, 1, -1}, dc[] = {1, -1, 0, 0};
char map[20][21];
bool visited[10][20][20];

void dfs(int cur_r, int cur_c, int move, int coins, int number) {       // 현재 행, 열, 움직인 횟수, 모은 동전 수, 마지막으로 거친 동전 번호
    if (Ans != -1 && move > Ans)
        return;
    visited[number][cur_r][cur_c] = true;
    for (int d = 0; d < 4; d++) {
        int R = cur_r + dr[d];
        int C = cur_c + dc[d];
        if (R >= 0 && R < N && C >= 0 && C < N && map[R][C] != '#') {
            if ((map[R][C] == '.' || map[R][C] == 'S') && !visited[number][R][C]) {
                dfs(R, C, move + 1, coins, number);
            }
            else if (map[R][C] >= '1' && map[R][C] <= '9' && !visited[number][R][C]) {
                if (map[R][C] - '0' > number && coins < 3)
                    dfs(R, C, move + 1, coins + 1, map[R][C] - '0');
                dfs(R, C, move + 1, coins, number);
            }
            else if (map[R][C] == 'E') {
                int Move = move + 1;
                if (coins >= 3) {
                    if (Ans == -1)
                        Ans = Move;
                    Ans = Ans > Move ? Move : Ans;
                }
            }
        }
    }
    visited[number][cur_r][cur_c] = false;
}

int main()
{
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> map[i];
        for (int j = 0; j < N; j++) {
            if (map[i][j] == 'S') {
                start_r = i;
                start_c = j;
            }
        }
    }
    dfs(start_r, start_c, 0, 0, 0);
    cout << Ans;

    return 0;
}