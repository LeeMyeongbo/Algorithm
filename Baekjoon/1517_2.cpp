#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

pair<int, int> A[500000];
vector<long long> tree;

long long search(int index, int left, int right, int r1, int r2)
{
    if (left > r2 || right < r1)
        return 0;
    
    if (left >= r1 && right <= r2)
        return tree[index];
    
    int mid = (left + right) >> 1;
    return search(index << 1, left, mid, r1, r2) + search((index << 1) + 1, mid + 1, right, r1, r2);
}

int main()
{
    int N, S;
    cin >> N;
    S = 1 << (int)ceil(log2(N));
    tree.resize(S << 1, 0);

    for (int i = 0; i < N; i++)
    {
        cin >> A[i].first;
        A[i].second = i + 1;
    }
    sort(A, A + N);

    long long ans = 0;
    for (int i = 0; i < N; i++)
    {
        int idx = A[i].second;
        int index = S + idx - 1;
        ans += search(1, 1, S, idx + 1, N);

        while (index)
        {
            tree[index]++;
            index = index >> 1;
        }
    }

    cout << ans;
    return 0;
}