#include <iostream>
#define S (1 << 18)
#define MOD 1000000007
#define MAX 200000 - 1
using namespace std;

struct Node {
    long long posSum;           // 구간 내 심어진 나무들의 좌표 합
    int cnt;                    // 구간 내 나무 개수
} tree[1 << 19];

Node search(int index, int left, int right, int r1, int r2)
{
    if (left > r2 || right < r1)
        return { 0, 0 };

    if (left >= r1 && right <= r2)
        return tree[index];

    int mid = (left + right) >> 1;
    Node lnode = search(index << 1, left, mid, r1, r2);
    Node rnode = search((index << 1) + 1, mid + 1, right, r1, r2);

    return { lnode.posSum + rnode.posSum, lnode.cnt + rnode.cnt };
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    register int N, ans = 1;
    cin >> N;

    for (register int i = 0; i < N; ++i)
    {
        register long long sum, x;
        cin >> x;
        
        register int idx = S + x;
        while (idx)
        {
            tree[idx].posSum += x;
            ++tree[idx].cnt;
            idx >>= 1;
        }

        if (i)
        {
            Node lnode = search(1, 0, S - 1, 0, x - 1);         // 현재 심는 나무의 왼쪽 거리 합 = 나무 개수 * 현재 좌표 - 왼쪽 좌표 합
            Node rnode = search(1, 0, S - 1, x + 1, MAX);       // 오른쪽 거리 합 = 오른쪽 좌표 합 - 나무 개수 * 현재 좌표

            sum = (x * lnode.cnt - lnode.posSum + rnode.posSum - x * rnode.cnt) % MOD;    // 반드시 sum도 MOD 취해줘야 함!
            ans = sum * ans % MOD;                              // sum * ans 하는 과정에서 long long 범위도 벗어날 수 있기 때문
        }
    }

    cout << ans;

    return 0;
}
