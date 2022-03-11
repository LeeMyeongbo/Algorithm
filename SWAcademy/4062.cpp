#include <iostream>
using namespace std;

int T, N, dp[1000][1000];
char map[1000][1001];

int main(int argc, char** argv)
{
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N;
        for (int i = 0; i < N; i++)
            cin >> map[i];

        int ans = 0;
        for (int i = 0; i < N; i++) {
            dp[0][i] = map[0][i] == '1' ? 0 : 1;
            ans = max(ans, dp[0][i]);

            dp[i][0] = map[i][0] == '1' ? 0 : 1;
            ans = max(ans, dp[i][0]);
        }

        for (int r = 1; r < N; r++) {
            for (int c = 1; c < N; c++) {
                if (map[r][c] == '0') {
                    if (dp[r][c - 1] == dp[r - 1][c] && dp[r - 1][c] == dp[r - 1][c - 1])
                        dp[r][c] = dp[r][c - 1] + 1;
                    else
                        dp[r][c] = min(dp[r - 1][c - 1], min(dp[r][c - 1], dp[r - 1][c])) + 1;
                }
                else
                    dp[r][c] = 0;
                ans = max(ans, dp[r][c]);
            }
        }

        cout << '#' << test_case << ' ' << ans << '\n';
    }
    return 0;
}
