#include <iostream>
#define MAX 1000000
using namespace std;

int T, n, p, Sum[MAX + 1], day;

int solve()                             // 이진 탐색을 이용하여 누적합 차이 + p가 mid 이상인지 확인
{
    int left = p, right = MAX, ans = 0;

    while (left <= right) {
        int mid = (left + right) / 2;
        bool flag = false;

        if (Sum[mid - 1] + p >= mid)
            flag = true;
        
        if (!flag) {
            for (int i = mid; i <= MAX; i++) {
                if (Sum[i] - Sum[i - mid] + p >= mid) {
                    flag = true;
                    break;
                }
            }
        }
        if (flag) {
            ans = mid;
            left = mid + 1;
        }
        else
            right = mid - 1;
    }

    return ans;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> n >> p;
        for (int i = 0; i < n; i++) {
            cin >> day;
            Sum[day]++;
        }
        for (int i = 1; i <= MAX; i++)
            Sum[i] += Sum[i - 1];
        

        cout << '#' << test_case << ' ' << solve() << '\n';
        fill(Sum, Sum + MAX + 1, 0);
    }
    return 0;
}
