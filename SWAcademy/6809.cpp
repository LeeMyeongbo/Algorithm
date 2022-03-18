#include <iostream>
#include <string.h>
using namespace std;

int T, N, ans, energy[81], dp[81][165][165];

void dfs(int i, int pre, int cur, int next)         // 각각 왼쪽 에너지량, 현재 에너지량, 다음 에너지량
{
    if (dp[i][cur][pre] != -1)
        return;

    dp[i][cur][pre] = 1;
    if (i == N) {
        ans = max(ans, cur);
        return;
    }

    if (cur > 0 && pre > 0)
        dfs(i + 1, cur - 1, pre + next, energy[i + 2]);
    dfs(i + 1, cur, next, energy[i + 2]);
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N;

        for (int i = 1; i <= N; i++)
            cin >> energy[i];

        memset(dp, -1, sizeof(dp));

        if (N == 1)
            ans = energy[1];
        else if (N == 2)
            ans = energy[2];
        else
            for (int i = 1; i <= N; i++)
                dfs(i, energy[i - 1], energy[i], energy[i + 1]);

        cout << '#' << test_case << ' ' << ans << '\n';
        ans = 0;
    }
    return 0;
}
