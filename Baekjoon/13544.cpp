#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#define MAX 131072
using namespace std;

int N, M, a, b, c, last_ans;
vector<int> tree[MAX * 2];

int Find(int index, int start, int end, int left, int right, int k)        // start ~ end : i ~ j, left ~ right : 현재 범위
{
    if (left > end || right < start)
        return 0;
    if (left >= start && right <= end)
        return tree[index].end() - upper_bound(tree[index].begin(), tree[index].end(), k);

    return Find(index * 2, start, end, left, (left + right) / 2, k) + Find(index * 2 + 1, start, end, (left + right) / 2 + 1, right, k);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    int S = 1 << (int)ceil(log2(N));

    for (int i = 0; i < N; i++) {
        cin >> M;
        tree[S + i].push_back(M);
    }

    for (int i = S - 1; i > 0; i--) {
        int left = 0, right = 0, left_size = tree[i * 2].size(), right_size = tree[i * 2 + 1].size();

        while (left < left_size && right < right_size) {
            if (tree[i * 2][left] < tree[i * 2 + 1][right])
                tree[i].push_back(tree[i * 2][left++]);
            else
                tree[i].push_back(tree[i * 2 + 1][right++]);
        }
        while (left < left_size)
            tree[i].push_back(tree[i * 2][left++]);
        while (right < right_size)
            tree[i].push_back(tree[i * 2 + 1][right++]);
    }

    cin >> M;
    while (M--) {
        cin >> a >> b >> c;
        int i = a ^ last_ans;
        int j = b ^ last_ans;
        int k = c ^ last_ans;

        last_ans = Find(1, i - 1, j - 1, 0, S - 1, k);
        cout << last_ans << '\n';
    }
    return 0;
}
