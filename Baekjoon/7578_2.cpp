#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<long long> tree;
int A[1000001], B[500001];     // A[n] : A열에서 식별번호가 n인 기계가 몇 번째인지, B[i] : A열에서 i번째인 기계가 B열에서는 몇 번째인지

long long search(int index, int left, int right, int range1, int range2)
{
    if (left > range2 || right < range1)
        return 0;
    
    if (left >= range1 && right <= range2)
        return tree[index];
    
    int mid = left + right >> 1;
    return search(index << 1, left, mid, range1, range2) + search((index << 1) + 1, mid + 1, right, range1, range2);
}

void update(int index)
{
    while (index)
    {
        tree[index]++;
        index = index >> 1;
    }
}

int main()          // inversion counting
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    int N, S, machine;
    long long ans = 0;

    cin >> N;
    S = 1 << (int)ceil(log2(N));
    tree.resize(S << 1, 0);

    for (int i = 0; i < N; i++)
    {
        cin >> machine;
        A[machine] = i + 1;
    }
    
    for (int i = 0; i < N; i++)
    {
        cin >> machine;
        B[A[machine]] = i + 1;
    }

    for (int i = 1; i <= N; i++)
    {
        ans += search(1, 1, S, B[i] + 1, N);    // B열에서 i번째 기계의 오른쪽 구간을 살피면서 개수 더함
        update(S + B[i] - 1);
    }

    cout << ans;
    return 0;
}