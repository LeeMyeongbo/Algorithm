#include <iostream>
#include <cmath>
using namespace std;

struct Node {
    int max, min;
} tree[1 << 18];

Node operator+(const Node& n1, const Node& n2) 
{
    return { max(n1.max, n2.max), min(n1.min, n2.min) };
}

Node search(int index, int left, int right, int& r1, int& r2)
{
    if (left > r2 || right < r1)
        return { -1, 100000 };

    if (left >= r1 && right <= r2)
        return tree[index];

    int mid = (left + right) >> 1;
    return search(index << 1, left, mid, r1, r2) + search((index << 1) + 1, mid + 1, right, r1, r2);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int T, N, K, S, Q, A, B;
    cin >> T;

    for (register int t = 0; t < T; ++t)
    {
        cin >> N >> K;
        S = 1 << (int)ceil(log2(N));

        for (register int i = 1; i < (S << 1); ++i)
            tree[i] = { -1, 100000 };

        for (register int i = 0; i < N; ++i)
        {
            int idx = S + i;
            tree[idx] = { i, i };

            idx >>= 1;
            while (idx)
            {
                tree[idx] = tree[idx << 1] + tree[(idx << 1) + 1];
                idx >>= 1;
            }
        }

        while (K--)
        {
            cin >> Q >> A >> B;
            if (!Q)
            {
                int idx_a = S + A, idx_b = S + B;
                Node tmp = tree[idx_a];

                tree[idx_a] = tree[idx_b];
                idx_a >>= 1;
                while (idx_a)
                {
                    tree[idx_a] = tree[idx_a << 1] + tree[(idx_a << 1) + 1];
                    idx_a >>= 1;
                }

                tree[idx_b] = tmp;
                idx_b >>= 1;
                while (idx_b)
                {
                    tree[idx_b] = tree[idx_b << 1] + tree[(idx_b << 1) + 1];
                    idx_b >>= 1;
                }
            }
            else
            {
                Node node = search(1, 0, S - 1, A, B);      // [A, B] 구간에서 최솟값이 A, 최댓값이 B면 됨
                if (node.min == A && node.max == B)
                    cout << "YES\n";
                else
                    cout << "NO\n";
            }
        }
    }

    return 0;
}
