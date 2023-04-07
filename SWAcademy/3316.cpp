#include <iostream>
#include <cstring>
using namespace std;

long long dp[10001][16];                // dp[day][Case] (day는 1부터 시작)
string str;                             // Case=1 -> 0001(A), Case=5 -> 0101(CA), Case=11 -> 1011(DBA)

int main(int argc, char** argv)
{
	int T;
	cin >> T;

	for (int test_case = 1; test_case <= T; ++test_case)
	{
        long long ans = 0;
        cin >> str;

        for (int Case = 1; Case < 16; Case++)
        {
            if (Case & 1 && Case & (1 << (str[0] - 'A')))   // 첫날에는 A와 책임자가 있는 경우 1로 설정
                dp[1][Case] = 1;
        }

        for (int day = 1; day < str.length(); day++)
        {
            for (int Case = 1; Case < 16; Case++)           // 다음 날 부터 (A), (B), (AB), ...순으로 살핌
            {
                if ((Case & (1 << (str[day] - 'A'))) == 0)  // 책임자 포함되어 있지 않으면 skip
                    continue;
                
                for (int c = 1; c < 16; c++)                // 이전 날 인원이랑 겹치는지 살핌
                    if (c & Case)
                    {
                        dp[day + 1][Case] += dp[day][c];
                        dp[day + 1][Case] %= 1000000007;
                    }
            }
        }

        for (int i = 1; i < 16; i++)
        {
            ans += dp[str.length()][i];
            ans %= 1000000007;
        }
        
        cout << '#' << test_case << ' ' << ans << '\n';
        memset(dp, 0, sizeof(dp));
	}
	return 0;
}