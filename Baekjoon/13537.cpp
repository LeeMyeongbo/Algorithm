#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#define MAX 131072
using namespace std;

int N, M, S, a, i, j, k;
vector<int> mergesort_tree[MAX * 2];

int find(int index, int left, int right)
{
    if (left > j || right < i)
        return 0;
    if (left >= i && right <= j)
        return mergesort_tree[index].end() - upper_bound(mergesort_tree[index].begin(), mergesort_tree[index].end(), k);

    return find(index * 2, left, (left + right) / 2) + find(index * 2 + 1, (left + right) / 2 + 1, right);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    S = 1 << (int)ceil(log2(N));

    for (int n = 0; n < N; n++) {
        cin >> a;
        mergesort_tree[S + n].emplace_back(a);
    }

    for (int n = S - 1; n > 0; n--) {           // 인덱스 트리 형식으로 머지소트 트리 형성
        int left = 0, right = 0, left_size = mergesort_tree[n * 2].size(), right_size = mergesort_tree[n * 2 + 1].size();

        while (left < left_size && right < right_size) {
            if (mergesort_tree[n * 2][left] < mergesort_tree[n * 2 + 1][right])
                mergesort_tree[n].emplace_back(mergesort_tree[n * 2][left++]);
            else
                mergesort_tree[n].emplace_back(mergesort_tree[n * 2 + 1][right++]);
        }
        while (left < left_size)
            mergesort_tree[n].emplace_back(mergesort_tree[n * 2][left++]);
        while (right < right_size)
            mergesort_tree[n].emplace_back(mergesort_tree[n * 2 + 1][right++]);
    }

    cin >> M;
    while(M--) {
        cin >> i >> j >> k;
        i--, j--;
        cout << find(1, 0, S - 1) << '\n';
    }

    return 0;
}
