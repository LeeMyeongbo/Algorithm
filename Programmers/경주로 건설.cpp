#include <vector>
#include <queue>
#define INF 1000000000
using namespace std;

const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };

int solution(vector<vector<int>> board) {
    int dij[4][25][25], N = board[0].size();                        // dij[d][r][c] : 방향이 d(0 <= d < 4)일 때 (r, c)에서의 최단 거리 저장
    priority_queue<pair<pair<int, int>, pair<int, int>>> pq;        // ((비용 합, 방향), (r, c))로 저장
                                                                    // 동서남북 순으로 0, 1, 2, 3
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < N; j++)
            fill(dij[i][j], dij[i][j] + N, INF);

    for (int d = 0; d < 4; d++) {
        dij[d][0][0] = 0;
        pq.push({ {0, d}, {0, 0} });
    }

    while (!pq.empty()) {
        int sum = -pq.top().first.first;
        int dir = pq.top().first.second;
        int r = pq.top().second.first;
        int c = pq.top().second.second;
        pq.pop();

        if (r == N - 1 && c == N - 1)
            return sum;
        if (sum > dij[dir][r][c])
            continue;

        for (int d = 0; d < 4; d++) {
            int R = r + dr[d], C = c + dc[d];
            if (R >= 0 && R < N && C >= 0 && C < N && !board[R][C]) {
                if (dir == d && dij[d][R][C] > sum + 100) {             // 방향이 바뀌지 않고 그대로 이동할 때
                    dij[d][R][C] = sum + 100;
                    pq.push({ {-dij[d][R][C], d}, {R, C} });
                }
                else if (dir != d && dij[d][R][C] > sum + 600) {        // 방향이 바뀔 때 -> 코너
                    dij[d][R][C] = sum + 600;
                    pq.push({ {-dij[d][R][C], d}, {R, C} });
                }
            }
        }
    }
    return -1;
}
