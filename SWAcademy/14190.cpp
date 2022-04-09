#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int T, N, M, start_r, start_c, map[500][500];
const int dr[] = { 1, -1, 0, 0 }, dc[] = { 0, 0, 1, -1 };
bool visited[500][500];

pair<int, int> solve()
{
    int day = 0;
    pair<int, int> ans = { 0, 0 };
    priority_queue<int> pq;                 // 꽃이 피어 있는 마지막 날 오름차순으로 저장 (최소 힙)
    queue<pair<int, pair<int, int>>> q;     // (꽃이 핀 날, (r, c))로 저장

    q.push({ 1, { start_r, start_c } });
    pq.push(-map[start_r][start_c]);
    visited[start_r][start_c] = true;

    while (!q.empty()) {
        if (day < q.front().first) {        // 하루가 지날 때마다 꽃밭에 남은 꽃 개수 갱신 (큐 head에 꽃 피는 날짜가 바뀌면 하루가 지난거임)
            day++;
            while (!pq.empty() && -pq.top() < day)
                pq.pop();

            if (pq.size() > ans.second)
                ans = { day, pq.size() };
        }

        int flower = q.front().first;
        int cur_r = q.front().second.first;
        int cur_c = q.front().second.second;
        q.pop();

        for (int d = 0; d < 4; d++) {       // 꽃이 피자마자 항상 주위에 씨앗이 퍼짐
            int R = cur_r + dr[d];
            int C = cur_c + dc[d];
            if (R >= 0 && R < N && C >= 0 && C < M && !visited[R][C] && map[R][C]) {
                q.push({ flower + 1, { R, C } });
                visited[R][C] = true;
                pq.push(-map[R][C] - day);
            }
        }
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
            for (int j = 0; j < M; j++)
                cin >> map[i][j];
        cin >> start_r >> start_c;

        pair<int, int> ans = solve();

        cout << '#' << test_case << ' ' << ans.first << "일 " << ans.second << "개" << '\n';
        memset(visited, false, sizeof(visited));
    }
    return 0;
}
