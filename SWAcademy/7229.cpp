#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int T, N, M;
double cake[50];

double solve()
{
    priority_queue<pair<double, pair<int, int>>> pq;
    double Min = 1e9 + 1;
    for (int i = 0; i < N; i++) {
        pq.push({ cake[i], {i, 1} });
        Min = min(Min, cake[i]);
    }
    double ans = pq.top().first - Min;

    for (int i = 0; i < M; i++) {                   // 가장 큰 조각의 index가 바뀔 때까지 2등분, 3등분, 4등분... 반복하며 최대 크기 및 최소 크기를 갱신
        double cur = pq.top().first;
        int index = pq.top().second.first;
        int cnt = pq.top().second.second;
        pq.pop();

        double s = cake[index] / ++cnt;
        pq.push({ s, {index, cnt} });
        Min = min(Min, s);                          // 크기 최솟값 갱신
        ans = min(ans, pq.top().first - Min);       // 최대 크기와 최소 크기 차이 갱신
    }

    return ans;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cout.precision(12);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N;
        for (int i = 0; i < N; i++)
            cin >> cake[i];
        cin >> M;

        cout << '#' << test_case << ' ' << solve() << '\n';
    }
    return 0;
}
