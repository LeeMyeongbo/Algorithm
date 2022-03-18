#include <iostream>
using namespace std;

int T, N, a, b;
pair<int, int> robot[1000001];

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        int Max = 0, ans = 100001;

        cin >> N;
        for (int i = 0; i < N; i++) {
            cin >> a >> b;
            Max = max(Max, a);
            robot[a] = { b, 0 };
        }

        for (int i = 1; i <= Max; i++) {
            if (robot[i].first) {
                if (i - robot[i].first > 1)
                    robot[i].second = robot[i - robot[i].first - 1].second + 1;
                else
                    robot[i].second = 1;
            }
            else
                robot[i].second = robot[i - 1].second;
        }

        for (int i = 1; i <= Max; i++)
            ans = min(ans, N - robot[i].second);

        cout << '#' << test_case << ' ' << ans << '\n';

        for (int i = 1; i <= Max; i++)
            robot[i] = { 0, 0 };
    }
    return 0;
}
