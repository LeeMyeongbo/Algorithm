#include <iostream>
using namespace std;

int T, n, arr[100000];

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> arr[i];

        int ans = 1;
        bool increasing = false, decreasing = false;    // 수열이 단조증가 중이라면 increasing = true, 단조감소 중이라면 decreasing = true

        for (int i = 1; i < n; i++) {
            if (arr[i - 1] < arr[i]) {                  // 뒷 자리가 앞 자리보다 클 경우
                if (!increasing && !decreasing)         // increasing, decreasing 모두 false 라면 increasing을 true로 지정
                    increasing = true;
                else if (decreasing) {
                    ans++;
                    increasing = decreasing = false;    // decreasing이 true인 상태였다면 개수 1 증가시키고 둘 다 false로 reset
                }
            }
            else if (arr[i - 1] > arr[i]) {
                if (!increasing && !decreasing)
                    decreasing = true;
                else if (increasing) {
                    ans++;
                    increasing = decreasing = false;
                }
            }
        }

        cout << '#' << test_case << ' ' << ans << "\n";
    }
    return 0;
}
