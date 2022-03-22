#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int n, m, S, num, i, j, k;
vector<int> tree[1 << 18];

int getVal(int index, int left, int right, int val)
{
    if (left > j || right < i)
        return 0;
    if (left >= i && right <= j)
        return upper_bound(tree[index].begin(), tree[index].end(), val) - tree[index].begin();
    return getVal(index * 2, left, (left + right) / 2, val) + getVal(index * 2 + 1, (left + right) / 2 + 1, right, val);
}

int Q()
{
    int left = (int)-1e9, right = (int)1e9, ans = 0;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (getVal(1, 0, S - 1, mid) >= k) {        // mid를 크게 잡으면 리턴되는 getVal 값도 커지니까 right를 반 줄임
            ans = mid;
            right = mid - 1;
        }
        else
            left = mid + 1;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m;
    S = 1 << (int)ceil(log2(n + 1));

    for (int idx = 1; idx <= n; idx++) {
        cin >> num;
        tree[S + idx].push_back(num);
    }
    for (int idx = S - 1; idx > 0; idx--) {
        int left = 0, right = 0, l_size = tree[idx + idx].size(), r_size = tree[idx + idx + 1].size();

        while (left < l_size && right < r_size) {
            if (tree[idx + idx][left] < tree[idx + idx + 1][right])
                tree[idx].push_back(tree[idx + idx][left++]);
            else
                tree[idx].push_back(tree[idx + idx + 1][right++]);
        }
        while (left < l_size)
            tree[idx].push_back(tree[idx + idx][left++]);
        while(right < r_size)
            tree[idx].push_back(tree[idx + idx + 1][right++]);
    }

    while (m--) {
        cin >> i >> j >> k;
        cout << Q() << '\n';
    }
    return 0;
}
