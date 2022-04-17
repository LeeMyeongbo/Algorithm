#include <iostream>
#include <cmath>
using namespace std;

int N, S, answer[100001], inv_seq[100001], tree[1 << 18];       // tree : 특정 구간에 숫자가 얼마나 비어있는지 구함

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

    for (register int i = N; i > 0; i--) {              // N부터 1까지 숫자를 집어넣으면서 진행
        register int start = 1;
        while (start < S) {
            if (tree[start + start + 1] > inv_seq[i])   // 오른쪽 자식의 숫자가 inv_seq[i]보다 클 경우 오른쪽 자식으로 이동
                start = start + start + 1;
            else {                                      // 그렇지 않다면 왼쪽으로 이동 + inv_seq[i]에서 오른쪽 자식의 숫자만큼 빼줌
                inv_seq[i] -= tree[start + start + 1];
                start += start;
            }
        }
        answer[start - S] = i;

        while (start) {             // 트리 갱신 (숫자 i가 차지하게 된 곳을 0으로)
            --tree[start];
            start /= 2;
        }
    }

    for (register int i = 1; i <= N; i++)
        cout << answer[i] << ' ';
    
    return 0;
}