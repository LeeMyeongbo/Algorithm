#include <iostream>
#include <cmath>
#define MAX 131072
using namespace std;

int N, M, Q, A, i, r, l, v;
pair<int, int> tree[MAX * 2];                       // (두 구간에서 최댓값, 그 다음으로 큰 값)으로 저장

pair<int, int> getMax(int index, int left, int right)
{
    if (left > r || right < l)
        return { 0, 0 };
    if (left >= l && right <= r)
        return tree[index];

    pair<int, int> l_pair = getMax(index * 2, left, (left + right) / 2);
    pair<int, int> r_pair = getMax(index * 2 + 1, (left + right) / 2 + 1, right);
    if (l_pair < r_pair)
        swap(l_pair, r_pair);

    return { l_pair.first, max(l_pair.second, r_pair.first) };
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N;

    int S = 1 << (int)ceil(log2(N));
    for (int n = 0; n < N; n++) {
        cin >> A;
        tree[S + n] = { A, 0 };                     // 수열 A의 값은 자연수(1 ~ 10^9)이므로 최솟값은 0으로 잡자
    }
    for (int n = S - 1; n > 0; n--) {
        pair<int, int> l_pair = tree[n * 2];
        pair<int, int> r_pair = tree[n * 2 + 1];
        if (l_pair < r_pair)
            swap(l_pair, r_pair);

        tree[n] = { l_pair.first, max(l_pair.second, r_pair.first) };
    }
    
    cin >> M;
    while (M--) {
        cin >> Q;
        if (Q == 1) {
            cin >> i >> v;
            int idx = S + i - 1;
            tree[idx] = { v, 0 };
            idx /= 2;
            while (idx) {                           // bottom-up 방식으로 갱신
                pair<int, int> l_pair = tree[idx * 2];
                pair<int, int> r_pair = tree[idx * 2 + 1];
                if (l_pair < r_pair)
                    swap(l_pair, r_pair);

                tree[idx] = { l_pair.first, max(l_pair.second, r_pair.first) };
                idx /= 2;
            }
        }
        else {
            cin >> l >> r;
            l--, r--;
            pair<int, int> ans = getMax(1, 0, S - 1);
            cout << ans.first + ans.second << '\n';
        }
    }

    return 0;
}
