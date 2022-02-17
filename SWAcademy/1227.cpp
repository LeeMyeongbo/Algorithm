#include <iostream>
#include <queue>
using namespace std;

int N, start_r, start_c;
char map[100][101];
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };

int BFS()
{
    queue<pair<int, int>> q;
    bool visited[100][100] = { false, };

    q.push({ start_r, start_c });
    visited[start_r][start_c] = true;

    while (!q.empty()) {
        pair<int, int> pos = q.front();
        q.pop();

        if (map[pos.first][pos.second] == '3')
            return 1;

        for (int d = 0; d < 4; d++) {
            int R = pos.first + dr[d];
            int C = pos.second + dc[d];
            if (R >= 0 && R < 100 && C >= 0 && C < 100 && !visited[R][C] && map[R][C] != '1') {
                visited[R][C] = true;
                q.push({ R, C });
            }
        }
    }
    return 0;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    for (int test_case = 1; test_case <= 10; ++test_case) {
        cin >> N;
        for (int i = 0; i < 100; i++) {
            cin >> map[i];
            for (int j = 0; j < 100; j++) {
                if (map[i][j] == '2')
                    start_r = i, start_c = j;
            }
        }

        cout << '#' << test_case << ' ' << BFS() << "\n";
    }
    return 0;
}
