#include <iostream>
#include <tuple>
#include <algorithm>
using namespace std;

int T, N, M, si, ei, ci, dp[501], pre[501];
tuple<int, int, int> work[501];

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N >> M;
        fill(dp, dp + N + 1, 0);
        fill(pre, pre + N + 1, 0);

        for (int i = 1; i <= N; i++) {
            cin >> si >> ei >> ci;
            work[i] = { ei, si, ci };
        }
        sort(work + 1, work + N + 1);

        for (int i = 1; i <= N; i++) {
            for (int j = 1; j < i; j++) {                   // i번 index의 작업 시작일이 j번 index의 작업 완료일보다 크면
                if (get<0>(work[j]) < get<1>(work[i]))      // pre[i]에 i번 index 작업의 (겹치지 않는)이전 마지막 작업 index 저장
                    pre[i] = j;
                else 
                    break;
            }   
        }

        for (int i = 1; i <= N; i++)
            dp[i] = max(dp[i - 1], dp[pre[i]] + get<2>(work[i]));

        cout << '#' << test_case << ' ' << dp[N] << '\n';
    }
    return 0;
}
