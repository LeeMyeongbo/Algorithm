#include <iostream>
#include <algorithm>
using namespace std;

int T, N;
pair<int, int> student[200];

int solve()
{
    int p[200] = { 0, };
    for (int i = 0; i < N; i++) {                       // 위에 있는 방 : 홀수이므로 / 2 적용, 아래에 있는 방 : 짝수이므로 / 2 - 1 적용
        int start_index = student[i].first % 2 ? student[i].first / 2 : student[i].first / 2 - 1;
        int end_index = student[i].second % 2 ? student[i].second / 2 : student[i].second / 2 - 1;
        int Max = max(start_index, end_index);
        int Min = min(start_index, end_index);

        for (int j = Min; j <= Max; j++)                // 거쳐가는 인덱스 모두 +1씩 더함
            p[j]++;
    }

    sort(p, p + 200);
    return p[199];
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N;
        for (int i = 0; i < N; i++)
            cin >> student[i].first >> student[i].second;
        
        cout << '#' << test_case << ' ' << solve() << '\n';
    }
    return 0;
}
