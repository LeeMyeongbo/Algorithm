#include <iostream>
#include <queue>
using namespace std;

int T, N, map[1000][1000];
bool possible[1000][1000];
pair<int, int> twofive[1000][1000], dp[1000][1000];     // twofive[r][c] : r행 c열에 있는 숫자를 소인수분해 했을 때 (2의 개수, 5의 개수)로 저장

int solve()
{
    queue<pair<int, int>> q;
    q.push({ 0, 0 });
    possible[0][0] = true;

    while (!q.empty()) {                // bfs 통해서 갈 수 있는 곳만 표시
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        if (r + 1 < N && map[r + 1][c] && !possible[r + 1][c]) {
            possible[r + 1][c] = true;
            q.push({ r + 1, c });
        }
        if (c + 1 < N && map[r][c + 1] && !possible[r][c + 1]) {
            possible[r][c + 1] = true;
            q.push({ r, c + 1 });
        }
    }

    dp[0][0] = twofive[0][0];
    for (int i = 1; i < N; i++) {
        if (possible[i][0])
            dp[i][0] = { dp[i - 1][0].first + twofive[i][0].first, dp[i - 1][0].second + twofive[i][0].second };
        if (possible[0][i])
            dp[0][i] = { dp[0][i - 1].first + twofive[0][i].first, dp[0][i - 1].second + twofive[0][i].second };
    }

    for (int r = 1; r < N; r++) {
        for (int c = 1; c < N; c++) {
            if (!possible[r][c])
                continue;

            if (possible[r - 1][c] && possible[r][c - 1]) {                 // 위쪽과 왼쪽 칸으로부터 현재 칸에 올 수 있는 경우
                pair<int, int> down = { dp[r - 1][c].first + twofive[r][c].first, dp[r - 1][c].second + twofive[r][c].second };
                pair<int, int> right = { dp[r][c - 1].first + twofive[r][c].first, dp[r][c - 1].second + twofive[r][c].second };

                dp[r][c] = min(down.first, down.second) > min(right.first, right.second) ? right : down;    // 2와 5 개수의 최솟값이 더 작은 곳을 선택
            }
            else if (possible[r - 1][c])                                    // 위쪽 칸으로부터만 현재 칸에 올 수 있는 경우
                dp[r][c] = { dp[r - 1][c].first + twofive[r][c].first, dp[r - 1][c].second + twofive[r][c].second };
            else if (possible[r][c - 1])                                    // 왼쪽 칸으로부터만 현재 칸에 올 수 있는 경우
                dp[r][c] = { dp[r][c - 1].first + twofive[r][c].first, dp[r][c - 1].second + twofive[r][c].second };
        }
    }

    return min(dp[N - 1][N - 1].first, dp[N - 1][N - 1].second);
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {               // 소인수분해 했을 때 2와 5 개수 저장
                cin >> map[i][j];
                while (map[i][j] && !(map[i][j] % 2)) {
                    twofive[i][j].first++;
                    map[i][j] /= 2;
                }
                while (map[i][j] && !(map[i][j] % 5)) {
                    twofive[i][j].second++;
                    map[i][j] /= 5;
                }
            }
        }

        cout << '#' << test_case << ' ' << solve() << '\n';
        for (int i = 0; i < N; i++) {
            fill(possible[i], possible[i] + N, false);
            for (int j = 0; j < N; j++) {
                twofive[i][j] = { 0, 0 };
                dp[i][j] = { 0, 0 };
            }
        }
    }
    return 0;
}
