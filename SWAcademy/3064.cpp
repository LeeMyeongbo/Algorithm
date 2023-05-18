#include <iostream>
using namespace std;

int tree[5][100001];

void update(int idx, int num, int N, int T)
{
    while (idx <= N)
    {
        tree[T][idx] += num;
        idx += (idx & -idx);
    }
}

int search(int idx, int N, int T)
{
    int ans = 0;
    while (idx)
    {
        ans += tree[T][idx];
        idx -= (idx & -idx);
    }

    return ans;
}

int main(void)
{
    register int T, N, M, A, q, x, y;
    
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> T;

    for (register int t = 0; t < T; t++)
    {
        cin >> N >> M;
        cout << '#' << t + 1 << ' ';

        for (register int i = 1; i <= N; i++)
        {
            cin >> A;
            update(i, A, N, t);
        }

        while (M--)
        {
            cin >> q >> x >> y;
            if (q == 1)
                update(x, y, N, t);
            else
                cout << search(y, N, t) - search(x - 1, N, t) << ' ';
        }
        cout << '\n';
    }

    return 0;
}
