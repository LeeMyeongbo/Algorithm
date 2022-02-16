#include <iostream>
#include <queue>
using namespace std;

int T, N, mine[300][300], visited[300][300];       // mine[r][c] : (r, c) 주변에 있는 지뢰 개수
const int dr[] = { -1, -1, 0, 1, 1, 1, 0, -1 }, dc[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
char map[300][301];

int solve()
{
    int num = 0;

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            if (map[r][c] == '.' && !mine[r][c] && !visited[r][c]) {    // 빈 곳이면서 주변에 지뢰가 없고 방문한 적도 없을 경우
                queue<pair<int, int>> q;
                q.push({ r, c });
                visited[r][c] = ++num;

                while (!q.empty()) {
                    int r = q.front().first;
                    int c = q.front().second;
                    q.pop();

                    for (int d = 0; d < 8; d++) {
                        int R = r + dr[d];
                        int C = c + dc[d];
                        if (R >= 0 && R < N && C >= 0 && C < N && map[R][C] == '.' && !visited[R][C]) { // 빈 곳이면서 방문하지 않았다면
                            visited[R][C] = num;                        // 방문 체크
                            if (!mine[R][C])                            // 주변에 지뢰도 없다면 큐에 삽입
                                q.push({ R, C });
                        }
                    }
                }
            }
        }
    }

    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            if (map[r][c] == '.' && !visited[r][c])         // 빈 곳인데 방문한 적 없을 경우 -> 한 번 클릭해줘야 함
                num++;

    return num;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N;
        for (int i = 0; i < N; i++)
            cin >> map[i];

        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (map[r][c] == '.') {
                    for (int d = 0; d < 8; d++) {
                        int R = r + dr[d];
                        int C = c + dc[d];
                        if (R >= 0 && R < N && C >= 0 && C < N && map[R][C] == '*')
                            mine[r][c]++;
                    }
                }
            }
        }

        cout << '#' << test_case << ' ' << solve() << "\n";
        for (int r = 0; r < N; r++) {
            fill(mine[r], mine[r] + N, 0);
            fill(visited[r], visited[r] + N, 0);
        }
    }
    return 0;
}
