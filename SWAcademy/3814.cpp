#include <iostream>
using namespace std;

int T, N;
long long K, arr[100000], tmp[100000], Max;

long long solve()                                       // 인접한 두 수 차이를 이용하여 이분탐색
{
    long long left = 0, right = Max, ans = 0;
    while (left <= right) {
        long long mid = (left + right) / 2, sum = 0;    // 두 수 차이의 합을 구할 시 int형 범위 넘어설 수도 있음!

        for (int i = 0; i < N; i++)
            tmp[i] = arr[i];
        for (int i = 0; i < N - 1; i++) {               // 왼쪽에서 오른쪽으로 가며 차이가 mid를 넘길 시 조정
            if (tmp[i] > tmp[i + 1] + mid) {
                sum += tmp[i] - tmp[i + 1] - mid;
                tmp[i] = tmp[i + 1] + mid;
            }
            else if (tmp[i + 1] > tmp[i] + mid) {
                sum += tmp[i + 1] - tmp[i] - mid;
                tmp[i + 1] = tmp[i] + mid;
            }
        }
        for (int i = N - 1; i > 0; i--) {               // 오른쪽에서 왼쪽으로 가며 차이가 mid를 넘길 시 조정
            if (tmp[i] > tmp[i - 1] + mid) {
                sum += tmp[i] - tmp[i - 1] - mid;
                tmp[i] = tmp[i - 1] + mid;
            }
            else if (tmp[i - 1] > tmp[i] + mid) {
                sum += tmp[i - 1] - tmp[i] - mid;
                tmp[i - 1] = tmp[i] + mid;
            }
        }

        if (sum <= K) {             // 감소시킨 총합이 K 이하일 경우에는 
            ans = mid;              // 일단 답 저장하고
            right = mid - 1;        // 허용 가능한 차이의 최댓값을 더 작게 잡아봄 (작은 쪽으로 범위를 반 줄인다)
        }
        else
            left = mid + 1;         // K 넘어가면 허용 가능한 차이의 최댓값을 더 크게 잡음 (큰 쪽으로 범위 반 줄임)
    }
    return ans;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N >> K;

        for (int i = 0; i < N; i++) {
            cin >> arr[i];
            Max = max(Max, arr[i]);
        }
        
        cout << '#' << test_case << ' ' << solve() << "\n";
        Max = 0;
    }
    return 0;
}
