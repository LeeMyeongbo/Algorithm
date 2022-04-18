#include <iostream>
#include <cmath>
using namespace std;

int N, A[100001], answer[100001], tree[1 << 18];    // tree : 구간 별로 자리가 얼마나 비어있는지 저장

int main()
{
    cin >> N;
    register int S = 1 << (int)ceil(log2(N + 1));
    for (register int i = 1; i <= N; i++) {
        cin >> A[i];
        tree[S + i] = 1;
    }
    for (register int i = S - 1; i > 0; i--)
        tree[i] = tree[i * 2] + tree[i * 2 + 1];
    
    for (register int i = 1; i <= N; i++) { // 1부터 N까지 차례로 집어넣으면서 진행
        register int cur = 1;
        while (cur < S) {
            if (tree[cur + cur] > A[i])
                cur += cur;                 // 왼쪽 자식의 빈 곳의 합이 A[i]보다 큰 경우 왼쪽으로 진행
            else {
                A[i] -= tree[cur + cur];
                cur = cur + cur + 1;        // 그렇지 않다면 A[i]를 왼쪽 자식만큼 빼주고 오른쪽으로 진행
            }
        }
        answer[cur - S] = i;

        while (cur) {           // 숫자 집어넣으면 해당 자리 처리
            --tree[cur];
            cur /= 2;
        }
    }

    for (register int i = 1; i <= N; i++)
        cout << answer[i] << '\n';

    return 0;
}