#include <iostream>
#include <algorithm>
using namespace std;

int T, N, K;
pair<double, double> ant[20000];
double pos[20000], loc[20000];

bool possible(double time) {
    for (int i = 0; i < N; ++i)                 // 개미 이동
        pos[i] = ant[i].first + (time * ant[i].second);
    
    int cnt = 0, liveant = N - K;
    loc[cnt++] = pos[0];

    for (int i = 1; i < N; ++i) {               // i 번째 개미가 이전 개미보다 뒤에 위치하는 경우
        if (loc[cnt - 1] < pos[i])
            loc[cnt++] = pos[i];
        else if (loc[0] >= pos[i])              // 속력이 낮아서 이전 개미가 앞지르게 된 경우
            loc[0] = pos[i];
        else {                                  // 중간영역에 있는 경우 Binary Search.
            int left = 0, right = cnt - 1, mid;
            mid = (left + right) / 2;
            while (left < right) {
                if (loc[mid] < pos[i])
                    left = mid + 1;
                else
                    right = mid;
                mid = (left + right) / 2;
            }
            loc[mid] = pos[i];
        }
    }
    
    return liveant > cnt;                       // 충돌되지 않고 살아남은 개미 비교
}

double solve()
{
    double left = 0, right = 1e9 + 1, ans = -1;
    
    while (right - left > 1e-7) {
        double mid = (left + right) / 2;
        if (possible(mid))                      // 현재 mid 초 이하로 잡았을 때 남아있는 개미 수가 N - K보다 작다면 
            ans = right = mid;                  // 시간(mid)을 더 작게 잡음
        else
            left = mid;
    }

    return ans;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cout.precision(12);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N >> K;
        for (int i = 0; i < N; i++)
            cin >> ant[i].first >> ant[i].second;

        sort(ant, ant + N);
        cout << fixed << '#' << test_case << ' ' << solve() << '\n';
    }
    return 0;
}
