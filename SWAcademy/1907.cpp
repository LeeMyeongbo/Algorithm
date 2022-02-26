#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
    int r, c, time;
};
int T, H, W, Ans, sand[1000][1000];         // sand[r][c] : r행 c열 지역 주변에 모래 없는 칸 개수 저장
const int dr[] = { -1, -1, 0, 1, 1, 1, 0, -1 }, dc[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
char map[1000][1001];
bool visited[1000][1000];
queue<Node> q;

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> H >> W;
        for (int i = 0; i < H; i++) {
            fill(sand[i], sand[i] + W, 0);
            fill(visited[i], visited[i] + W, false);
        }

        for (int i = 0; i < H; i++) {
            cin >> map[i];
            for (int j = 0; j < W; j++) {
                if (map[i][j] == '.') {             // 모래 없는 지역 큐에 저장
                    q.push({ i, j, 0 });
                    visited[i][j] = true;
                }
            }
        }

        while (!q.empty()) {
            Node node = q.front();
            q.pop();

            Ans = max(Ans, node.time);

            for (int d = 0; d < 8; d++) {
                int R = node.r + dr[d];
                int C = node.c + dc[d];
                if (R >= 0 && R < H && C >= 0 && C < W) {
                    sand[R][C]++;                                           // 인접한 칸에 모래 없는 칸 개수를 1씩 늘림
                    if (sand[R][C] >= map[R][C] - '0' && !visited[R][C]) {  // 모래 없는 칸 개수가 튼튼함 이상이면서 방문한 적 없으면
                        q.push({ R, C, node.time + 1 });                    // 모래가 무너지는 것 -> 큐 저장 + 방문 체크
                        visited[R][C] = true;
                    }
                }
            }
        }
        cout << '#' << test_case << ' ' << Ans << "\n";
        Ans = 0;
    }
    return 0;
}
