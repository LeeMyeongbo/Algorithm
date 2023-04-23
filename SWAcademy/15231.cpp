#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int T, N, V;

    cin >> T;

    for (register unsigned int test_case = 1; test_case <= T; ++test_case)
    {
        cin >> N >> V;
        register unsigned int v_depth = 0, n_depth = 0, ans = 0;

        while (V > 3)
        {
            v_depth++;
            V >>= 1;
        }
        while (N > 3)
        {
            n_depth++;
            N >>= 1;
        }

        if (N == 1)                             // 정점이 하나밖에 없을 경우
            ans = 0;
        else if (N == 2 && V == 2 || V == 1)    // N과 V의 조상이 모두 2거나 V가 1일 경우
            ans = v_depth + n_depth + 1;
        else
            ans = v_depth + n_depth + 2;

        cout << '#' << test_case << ' ' << ans << '\n';
    }
    return 0;
}
