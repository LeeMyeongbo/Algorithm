#include <iostream>
#include <cmath>
#define MAX 1048576
using namespace std;

int N, M, tree[MAX * 2];

int find(int index, int start, int end, int left, int right)        // start ~ end : 찾고자 하는 범위, left ~ right : 현재 범위
{
    if (left > end || right < start)
        return 0;
    if (left >= start && right <= end)
        return tree[index];

    return max(find(index * 2, start, end, left, (left + right) / 2), find(index * 2 + 1, start, end, (left + right) / 2 + 1, right));
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N >> M;
    int S = 1 << (int)ceil(log2(N));

    for (int i = 0; i < N; i++)
        cin >> tree[S + i];

    for (int i = S - 1; i > 0; i--)
        tree[i] = max(tree[i * 2], tree[i * 2 + 1]);

    for (int i = M - 1; i < N - M + 1; i++)
        cout << find(1, i - M + 1, i + M - 1, 0, S - 1) << ' ';

    return 0;
}
