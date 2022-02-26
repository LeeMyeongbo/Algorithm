#include <iostream>
#include <queue>
using namespace std;

struct Node {
    bool suyeon;
    int r, c, time;
};
int T, N, M, start_r, start_c;
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
char map[50][51];
bool visited[50][50];
queue<Node> q;

int bfs()
{
    q.push({ true, start_r, start_c, 0 });          // 수연이 출발 지점 큐에 넣음
    visited[start_r][start_c] = true;

    while (!q.empty()) {
        Node node = q.front();
        q.pop();

        if (map[node.r][node.c] == 'D')
            return node.time;

        for (int d = 0; d < 4; d++) {
            int R = node.r + dr[d];
            int C = node.c + dc[d];
            if (R >= 0 && R < N && C >= 0 && C < M && !visited[R][C] && map[R][C] != 'X') {
                if (!node.suyeon && map[R][C] == '.') {             // 악마의 손아귀 확장
                    q.push({ node.suyeon, R, C, node.time + 1 });
                    visited[R][C] = true;
                }
                else if (node.suyeon) {                             // 수연이 이동
                    q.push({ node.suyeon, R, C, node.time + 1 });
                    visited[R][C] = true;
                }
            }
        }
    }
    return -1;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N >> M;
        for (int i = 0; i < N; i++) {
            cin >> map[i];
            for (int j = 0; j < M; j++) {
                if (map[i][j] == 'S') {
                    start_r = i, start_c = j;       // 출발 지점 지정
                    map[i][j] = '.';
                }
                else if (map[i][j] == '*') {        // 악마의 손아귀를 먼저 큐에 넣음
                    q.push({ false, i, j, 0 });
                    visited[i][j] = true;
                }
            }
        }
        int ans = bfs();
        cout << '#' << test_case << ' ';
        ans != -1 ? cout << ans << "\n" : cout << "GAME OVER\n";

        while (!q.empty())
            q.pop();
        for (int i = 0; i < N; i++)
            fill(visited[i], visited[i] + M, false);
    }
    return 0;
}
