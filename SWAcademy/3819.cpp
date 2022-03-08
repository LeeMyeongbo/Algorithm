#include <iostream>
using namespace std;

int T, N, A[200000];

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N;

        for (int i = 0; i < N; i++)
            cin >> A[i];
        
        int sum = 0, ans = A[0];
        for (int i = 0; i < N; i++) {
            sum = max(A[i], sum + A[i]);        // A[i]와 A[0]에서 A[i - 1]까지의 합(sum) + A[i] 중 더 큰 걸 선택해서 sum에 저장
            ans = max(ans, sum);
        }

        cout << '#' << test_case << ' ' << ans << "\n";
    }
    return 0;
}
