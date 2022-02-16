#include <iostream>
#include <queue>
#define MAX 141
using namespace std;

struct Node {
    int r, c, cur, move;              // 행, 열, 번호, 움직인 거리
};
int T, a, b, map[MAX + 1][MAX + 1];
const int dr[] = { -1, -1, 0, 0, 1, 1 }, dc[] = { -1, 0, -1, 1, 0, 1 };
pair<int, int> p[MAX * (MAX + 1) / 2 + 1];

int solve()
{
    queue<Node> q;
    bool visited[MAX * (MAX + 1) / 2 + 1] = { false, };

    q.push({ p[a].first, p[a].second, a, 0 });
    visited[a] = true;

    while (!q.empty()) {
        Node node = q.front();
        q.pop();

        if (node.cur == b)
            return node.move;

        for (int d = 0; d < 6; d++) {
            int R = node.r + dr[d];
            int C = node.c + dc[d];

            // map 범위 벗어나지 않으면서 갈 수 있는 위치에 속하고 방문한 적 없을 경우 큐에 저장
            if (R > 0 && R <= MAX && C > 0 && C <= MAX && map[R][C] && !visited[map[R][C]]) {
                visited[map[R][C]] = true;
                q.push({ R, C, map[R][C], node.move + 1 });
            }
        }
    }
    return -1;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    int n = 0;
    for (int i = 1; i <= MAX; i++) {
        for (int j = 1; j <= i; j++) {
            map[i][j] = ++n;                        // 맵 생성
            p[n].first = i, p[n].second = j;        // 숫자 별로 좌표 저장
        }
    }

    for (int test = 1; test <= T; test++) {
        cin >> a >> b;
        cout << "#" << test << ' ' << solve() << "\n";
    }
    
    return 0;
}
