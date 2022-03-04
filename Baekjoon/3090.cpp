#include <iostream>
using namespace std;

int N;
long long T, arr[100000], tmp[100000], ans[100000], Max;

void solve()                                        // 인접한 두 수의 차이를 기준으로 이분탐색
{
    long long left = 0, right = Max;
    while (left <= right) {
        long long mid = (left + right) / 2;
        long long sum = 0;

        for (int i = 0; i < N; i++)
            tmp[i] = arr[i];

        for (int i = 0; i < N - 1; i++) {           // 왼쪽에서 오른쪽으로 가며 차이가 mid보다 클 경우 조정
            if (tmp[i] > tmp[i + 1] + mid) {
                sum += tmp[i] - tmp[i + 1] - mid;
                tmp[i] = tmp[i + 1] + mid;
            }
            else if (tmp[i + 1] > tmp[i] + mid) {
                sum += tmp[i + 1] - tmp[i] - mid;
                tmp[i + 1] = tmp[i] + mid;
            }
        }
        for (int i = N - 1; i > 0; i--) {           // 오른쪽에서 왼쪽으로 가며 차이가 mid보다 클 경우 조정
            if (tmp[i] > tmp[i - 1] + mid) {
                sum += tmp[i] - tmp[i - 1] - mid;
                tmp[i] = tmp[i - 1] + mid;
            }
            else if (tmp[i - 1] > tmp[i] + mid) {
                sum += tmp[i - 1] - tmp[i] - mid;
                tmp[i - 1] = tmp[i] + mid;
            }
        }

        if (sum <= T) {                             // 답이 가능할 경우 ans 배열에 저장
            right = mid - 1;
            for (int i = 0; i < N; i++)
                ans[i] = tmp[i];
        }
        else
            left = mid + 1;
    }
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N >> T;

    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        Max = max(Max, arr[i]);
    }

    solve();

    for (int i = 0; i < N; i++)
        cout << ans[i] << ' ';

    return 0;
}
