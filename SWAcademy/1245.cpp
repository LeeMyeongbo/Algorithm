#include <iostream>
#include <algorithm>
using namespace std;

int T, N;
pair<double, double> magnet[10];      // (위치, 질량)으로 저장

double solve(int left)
{
    double l = magnet[left].first, r = magnet[left + 1].first;

    while (true) {
        double middle = (l + r) / 2;
        double F1 = 0.0, F2 = 0.0;

        for (int i = 0; i <= left; i++)
            F1 += magnet[i].second / (middle - magnet[i].first) / (middle - magnet[i].first);
        for (int i = left + 1; i < N; i++)
            F2 += magnet[i].second / (middle - magnet[i].first) / (middle - magnet[i].first);

        if (abs(l - r) < 1e-12)       // 좌표값 오차가 10^-12보다 작아지면 종료
            return middle;
        else {
            if (F1 > F2)
                l = middle;
            else
                r = middle;
        }
    }
    return 0.0;
}

int main(int argc, char** argv)
{
    cout.precision(10);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N;
        for (int i = 0; i < N; i++)
            cin >> magnet[i].first;
        for (int i = 0; i < N; i++)
            cin >> magnet[i].second;

        sort(magnet, magnet + N);           // 좌표 기준으로 오름차순 정렬

        cout << fixed << '#' << test_case << ' ';
        for (int d = 0; d < N - 1; d++)
            cout << solve(d) << ' ';
        cout << "\n";
    }
    return 0;
}
