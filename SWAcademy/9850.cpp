#include <iostream>
#include <algorithm>
using namespace std;

int T, N, M;
pair<int, int> want[200000], rest[200000];

bool comp1(const pair<int, int>& p1, const pair<int, int>& p2)      // 먼저 왼쪽 기준 오름차순으로 + 왼쪽 좌표 같다면 오른쪽 기준 내림차순으로
{
    if (p1.first < p2.first)
        return true;
    return p1.first == p2.first && p1.second > p2.second;
}

bool comp2(const pair<int, int>& p1, const pair<int, int>& p2)      // 먼저 오른쪽 기준 내림차순으로 + 오른쪽 좌표 같다면 왼쪽 기준 오름차순으로
{
    if (p1.second > p2.second)
        return true;
    return p1.second == p2.second && p1.first < p2.first;
}

int solve()
{
    int ans = 0, left_cur = 0, idx = 0;          // left_cur : 현재 왼쪽에 앉은 사람 수

    for (int i = 0; i < N; i++) {
        if (want[i].first - left_cur > 0)
            left_cur++;
        else
            rest[idx++] = want[i];
    }
    sort(rest, rest + idx, comp2);

    int right_cur = 0;                          // right_cur : 현재 오른쪽에 앉은 사람 수
    for (int i = 0; i < idx; i++) {
        if (M + 1 - rest[i].second - right_cur > 0 && right_cur + left_cur < M)
            right_cur++;
        else
            ans++;
    }

    return ans;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N >> M;
        for (int i = 0; i < N; i++)
            cin >> want[i].first >> want[i].second;

        sort(want, want + N, comp1);

        cout << '#' << test_case << ' ' << solve() << '\n';
    }
    return 0;
}
