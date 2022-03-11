#include <iostream>
using namespace std;

int T, N, L, R;
long long dp[21][21][21];

int main(int argc, char** argv)
{
    cin >> T;

    dp[1][1][1] = 1;
    for (long long n = 2; n <= 20; n++)
        for (int l = 1; l <= 20; l++)
            for (int r = 1; r <= 20; r++)
                dp[n][l][r] = dp[n - 1][l - 1][r] + dp[n - 1][l][r - 1] + (n - 2) * dp[n - 1][l][r];

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N >> L >> R;

        cout << '#' << test_case << ' ' << dp[N][L][R] << '\n';
    }
    return 0;
}
