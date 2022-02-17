#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int x, y, move;
    bool garo;                  // garo : 가로 방향으로 이동했을 시 true, 세로 방향으로 이동했을 시 false
};
int T, start_x, start_y, dest_x, dest_y;
bool visited[2][201][201];      // [0][r][c] : 가로 방향으로 도착 시 체크, [1][r][c] : 세로 방향으로 도착 시 체크

int solve()
{
    queue<Node> q;
    q.push({ start_x, start_y, 0, 0 });
    q.push({ start_x, start_y, 0, 1 });
    visited[0][start_y][start_x] = visited[1][start_y][start_x] = true;

    while (!q.empty()) {
        Node node = q.front();
        q.pop();

        if (node.x == dest_x && node.y == dest_y)
            return node.move;

        if (node.garo) {                                                // 가로 방향으로 왔을 경우 -> 세로로 이동
            if (node.y - 1 >= 0 && !visited[1][node.y - 1][node.x]) {   // 북쪽으로 이동가능한지 살피고 이동
                visited[1][node.y - 1][node.x] = true;
                q.push({ node.x, node.y - 1, node.move + 1, false });
            }
            if (node.y + 1 < 201 && !visited[1][node.y + 1][node.x]) {  // 남쪽으로 이동가능한지 살피고 이동
                visited[1][node.y + 1][node.x] = true;
                q.push({ node.x, node.y + 1, node.move + 1, false });
            }
        }
        else {                                                          // 세로 방향으로 왔을 경우 -> 가로로 이동
            if (node.x - 1 >= 0 && !visited[0][node.y][node.x - 1]) {   // 서쪽으로 이동가능한지 살피고 이동
                visited[0][node.y][node.x - 1] = true;
                q.push({ node.x - 1, node.y, node.move + 1, true });
            }
            if (node.x + 1 < 201 && !visited[0][node.y][node.x + 1]) {  // 동쪽으로 이동가능한지 살피고 이동
                visited[0][node.y][node.x + 1] = true;
                q.push({ node.x + 1, node.y, node.move + 1, true });
            }
        }
    }
    return 0;
}

int main(int argc, char** argv)
{   
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> start_x >> start_y >> dest_x >> dest_y;
        start_x += 100, start_y += 100, dest_x += 100, dest_y += 100;

        cout << '#' << test_case << ' ' << solve() << "\n";
        for (int i = 0; i < 201; i++) {
            fill(visited[0][i], visited[0][i] + 201, false);
            fill(visited[1][i], visited[1][i] + 201, false);
        }
    }
    return 0;
}
