#include <iostream>
#include <algorithm>
using namespace std;

int L, sa[200000], isa[200000], ranking[200000];
string S;
pair<int, int> sr[200000];

bool cmp(int a, int b)
{
    return sr[a] < sr[b];
}

int solve()
{
    for (int i = 0; i < L; i++) {
        sa[i] = i;
        ranking[i] = S[i] - 'a' + 1;
    }

    for (int d = 2; d < L; d = d << 1) {
        for (int i = 0; i < L; i++) {
            if (i + d / 2 < L)
                sr[i] = { ranking[i], ranking[i + d / 2] };
            else
                sr[i] = { ranking[i], 0 };
        }
        sort(sa, sa + L, cmp);

        ranking[sa[0]] = 1;
        for (int i = 1; i < L; i++)
            ranking[sa[i]] = sr[sa[i]] == sr[sa[i - 1]] ? ranking[sa[i - 1]] : ranking[sa[i - 1]] + 1;
    }

    for (int i = 0; i < L; i++)
        isa[sa[i]] = i;

    int ans = 0;
    for (int pos = 0, i = 0; i < L; i++) {
        if (!isa[i])
            continue;
        int pre = sa[isa[i] - 1];

        while (i + pos < L && pre + pos < L && S[i + pos] == S[pre + pos])
            pos++;

        ans = max(ans, pos);
        if (pos)
            pos--;
    }

    return ans;
}

int main(int argc, char** argv)
{
    cin >> L >> S;
    cout << solve();

    return 0;
}
