#include <iostream>
#include <cmath>
#define S 2097152
#define MAX 2000000
using namespace std;

int T, N, D;
long long P, A[MAX], Sum[S * 2];                                            // Sum[1] ~ Sum[S - 1] : 내부노드, Sum[S] ~ Sum[2 * S - 1] : 리프노드

long long find(int index, int start, int end, int left, int right)          // start/end : 리프 기준 구하고자 하는 범위, left/right : 리프 기준 현재 범위
{
    if (right < start || left > end)
        return 0;
    if (right <= end && left >= start)
        return Sum[index];
    return max(find(index * 2, start, end, left, (left + right) / 2), find(index * 2 + 1, start, end, (left + right) / 2 + 1, right));
}

int solve(int width)
{
    int left = 0, right = 0, ans = 1;
    long long sum = A[left];                                                // sum : left에서 right까지 다 더한 값

    while (right < N) {
        if (right - left + 1 <= D) {
            ans = max(ans, ++right - left);
            sum += A[right];
        }
        else {
            long long Max = find(1, left, right - D + 1, 0, width - 1);     // 현재 [left, right] 구간 중에서 숫자 연속으로 D개 더했을 때 가장 큰 값 찾음   
            if (sum - Max <= P) {                                           // 탐색할 때 반드시 전체 범위(0 ~ width-1)에서 탐색해야 함! (N - D) 아님 주의!
                ans = max(ans, ++right - left);
                sum += A[right];
            }
            else
                sum -= A[left++];
        }
    }

    return ans;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N >> P >> D;
        for (int i = 0; i < N; i++)
            cin >> A[i];

        int width = 1 << (int)ceil(log2(N - D + 1));        // 인덱스 트리는 반드시 배열 크기를 2의 자승으로 정하는 것이 중요!
                                                            // width : 리프노드의 개수이자 리프노드의 시작 index
        for (int i = 0; i < D; i++)
            Sum[width] += A[i];
        for (int i = 0; i < N - D; i++)
            Sum[width + i + 1] = Sum[width + i] - A[i] + A[i + D];      // 리프노드에 값 저장

        for (int i = width - 1; i > 0; i--)
            Sum[i] = max(Sum[i * 2], Sum[i * 2 + 1]);                   // 리프 제외한 내부노드에 값 저장

        cout << '#' << test_case << ' ' << solve(width) << '\n';
        fill(A, A + N, 0);
        fill(Sum, Sum + S * 2, 0);
    }
    return 0;
}
