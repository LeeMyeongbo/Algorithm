#include <iostream>
#include <cmath>
using namespace std;

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    register int T;
    register long long N;
    cin >> T;

    for (register int test_case = 1; test_case <= T; ++test_case)
    {
        cin >> N;
        cout << '#' << test_case << ' ';

        register long long v = sqrt(N * 8 + 1);
        if (v * v == N * 8 + 1)
            cout << (v - 1) / 2 << '\n';
        else
            cout << -1 << '\n';
    }

    return 0;
}
