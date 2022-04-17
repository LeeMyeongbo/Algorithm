#include <iostream>
#include <cmath>
using namespace std;

int N, M, S, Q, n, a, tree[1 << 20];

int getSum(int index, int start, int end, int left, int right)
{
    if (left > end || right < start)
        return 0;
    if (left >= start && right <= end)
        return tree[index];
    return getSum(index * 2, start, end, left, (left + right) / 2) + getSum(index * 2 + 1, start, end, (left + right) / 2 + 1, right);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N;
    S = 1 << (int)ceil(log2(N + 1));

    for (int i = 1; i <= N; i++)
        cin >> tree[S + i];                         // 말단 노드에 값 저장
    
    for (int i = S - 1; i > 0; i--)
        tree[i] = tree[i * 2] + tree[i * 2 + 1];    // 내부 노드에 왼쪽 자식 + 오른쪽 자식 합 저장
    
    cin >> M;
    while (M--) {
        cin >> Q;
        if (Q == 1) {
            cin >> n >> a;
            register int index = S + n;

            while (index) {                     // 부대 증원/감원이 일어날 경우 트리 업데이트
                tree[index] += a;
                index /= 2;
            }
        }
        else {                                  // n번 군번의 군인의 소속 부대를 알아낼 경우
            cin >> n;
            register int left = 1, right = N, ans = 0;

            while (left <= right) {             // 맨 처음 소속 부대를 중간쯤(mid)으로 잡고
                register int mid = (left + right) / 2;
                if (getSum(1, 0, mid, 0, S - 1) >= n) {     // 1번부터 mid번 부대까지의 부대원 수를 구해가며 이분 탐색
                    ans = mid;
                    right = mid - 1;            // 1 ~ mid번 부대의 부대원 수 합이 n 이상일 경우 범위를 왼쪽으로 더 작게 잡고 탐색
                }
                else
                    left = mid + 1;             // 그렇지 않다면 오른쪽으로 더 크게 잡고 탐색
            }
            cout << ans << '\n';
        }
    }
    return 0;
}