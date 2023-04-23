#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    register unsigned int T, a, b;

    cin >> T;

    for (register unsigned test_case = 1; test_case <= T; ++test_case)
    {
        cin >> a >> b;

        register unsigned int d = b - a;

        cout << '#' << test_case << ' ' << d * (d + 1) / 2 - b << '\n';
    }
    return 0;
}
