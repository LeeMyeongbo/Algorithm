#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
//#include <fstream>
using namespace std;

int N;
long long tree[1 << 18];
string s;

long long getCnt(int index, int start, int end, int left, int right)
{
    if (left > end || right < start)
        return 0;
    if (left >= start && right <= end)
        return tree[index];
    return getCnt(index * 2, start, end, left, (left + right) / 2) + getCnt(index * 2 + 1, start, end, (left + right) / 2 + 1, right);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    while (true) {
        cin >> N;
        if (!N)
            return 0;

        map<string, int> m;
        int S = 1 << (int)ceil(log2(N));
        long long ans = 0;

        for (int i = 0; i < N; i++) {
            cin >> s;
            m[s] = i;
        }

        for (int i = 0; i < N; i++) {
            cin >> s;
            int n = m[s];
            ans += getCnt(1, n + 1, S - 1, 0, S - 1);

            int idx = S + n;
            while (idx) {
                tree[idx]++;
                idx /= 2;
            }
        }

        cout << ans << '\n';
        memset(tree, 0, sizeof(tree));
    }
}
