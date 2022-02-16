#include <iostream>
using namespace std;

int T, N, map[1000][1000], dp[1000][1000], Ans, Move;
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };

int DFS(int r, int c)
{
    int cur = 1;
    for (int d = 0; d < 4; d++) {
        int R = r + dr[d];
        int C = c + dc[d];
        if (R >= 0 && R < N && C >= 0 && C < N && map[R][C] == map[r][c] + 1) {
            if (!dp[R][C])
                dp[R][C] = DFS(R, C);       // (R, C) 지점에 도달한 적 없을 경우 최대 이동 가능 거리 구하고 저장
            cur = max(cur, dp[R][C] + 1);   // 그리고 현재 지점(r, c)에서의 최대 이동 가능 거리 갱신
        }
    }
    return cur;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N;
        for (int r = 0; r < N; r++)
            for (int c = 0; c < N; c++)
                cin >> map[r][c];

        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (!dp[r][c])
                    dp[r][c] = DFS(r, c);
                if (Move < dp[r][c]) {
                    Move = dp[r][c];
                    Ans = map[r][c];
                }
                else if (Move == dp[r][c])
                    Ans = min(Ans, map[r][c]);
            }
        }
        cout << '#' << test_case << ' ' << Ans << ' ' << Move << "\n";

        for (int i = 0; i < N; i++)
            fill(dp[i], dp[i] + N, 0);
        Ans = Move = 0;
    }
    return 0;
}
