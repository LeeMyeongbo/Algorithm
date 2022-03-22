#include <iostream>
#include <cmath>
using namespace std;

int N, K, S, tmp[250000], Max;
long long tree[1 << 18], ans;

long long findMid(long long s)
{
    long long index = 1, k = (K + 1) / 2;
    while (index < s) {
        // 왼쪽 서브트리의 노드 수가 현재 k 이상일 경우 중앙값이 왼쪽 서브트리에 존재 -> 그대로 왼쪽 자식으로 이동
        if (tree[index + index] >= k)
            index += index;
        // 그게 아니라면 왼쪽 서브트리에는 중앙값이 존재하지 않는 것 -> 오른쪽 자식으로 이동 + k에서 왼쪽 서브트리 노드 수 빼줌
        else {
            k -= tree[index + index];
            index = index + index + 1;
        }
    }
    return index - s;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> tmp[i];
        Max = max(Max, tmp[i]);
    }
    S = 1 << (int)ceil(log2(Max + 1));

    for (int i = 0; i < K; i++) {
        int idx = S + tmp[i];
        while (idx) {
            tree[idx]++;
            idx /= 2;
        }
    }

    for (int i = K; i <= N; i++) {
        ans += findMid(S);          // K개씩 잘라가며 트리에 저장하고 그 중간값 찾는 방식으로 감
        if (i == N) break;

        int idx = S + tmp[i - K];
        while (idx) {               // K번 전에 넣었던 숫자 도로 트리에서 제거
            tree[idx]--;
            idx /= 2;
        }
        idx = S + tmp[i];
        while (idx) {               // 이후 K + 1번째 숫자 트리에 추가
            tree[idx]++;
            idx /= 2;
        }
    }

    cout << ans;
    return 0;
}
