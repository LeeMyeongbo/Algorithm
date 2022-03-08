#include <iostream>
using namespace std;

int T, len[1000000];
string S;

int solve()
{
    int l = 0;
    fill(len, len + S.length(), 0);

    for (int i = 1; i < S.length(); ) {
        if (S[i] == S[l])
            len[i++] = ++l;
        else {
            if (l)
                l = len[l - 1];
            else
                i++;
        }
    }
    int cur = len[S.length() - 1], i;

    for (i = S.length() - 1; cur; i--) {
        if (len[i] != cur)
            return 0;
        cur--;
    }

    if (S.length() % (i + 1) == 0)
        return S.length() / (i + 1);

    return 1;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> S;

        cout << '#' << test_case << ' ' << solve() << '\n';
    }
    return 0;
}
