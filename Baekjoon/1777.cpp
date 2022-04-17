#include <iostream>
#include <cmath>
using namespace std;

int N, S, answer[100001], inv_seq[100001], tree[1 << 18];       // tree : 특정 구간에 숫자가 얼마나 비어있는지 구함

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
    cin >> N;
    S = 1 << (int)ceil(log2(N + 1));
    for (register int i = 1; i <= N; i++) {
        cin >> inv_seq[i];
        tree[S + i] = 1;
    }
    for (register int i = S - 1; i > 0; i--)
        tree[i] = tree[i * 2] + tree[i * 2 + 1];

    for (register int i = N; i > 0; i--) {
        register int left = 1, right = N, ans = 1;

        while (left <= right) {
            register int mid = (left + right) / 2;
            if (getSum(1, mid, N, 0, S - 1) >= inv_seq[i] + 1) {    // mid부터 N까지 비어있는 자리가 inv_seq[i]+1 이상일 경우
                ans = mid;
                left = mid + 1;                                 // 해당 mid 저장하고 범위를 오른쪽으로 반 줄임
            }
            else
                right = mid - 1;                                // 그렇지 않으면 왼쪽으로 반 줄임
        }
        answer[ans] = i;

        register int index = S + ans;
        while (index) {
            --tree[index];
            index /= 2;
        }
    }

    for (int i = 1; i <= N; i++)
        cout << answer[i] << ' ';
    
    return 0;
}