#include <iostream>
using namespace std;

int T, R, C, Ans;
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
char map[20][21];
bool visited[26];               // A~Z까지 방문 체크

void dfs(int depth, int r, int c)
{
    visited[map[r][c] - 'A'] = true;
    for (int d = 0; d < 4; d++) {
        int new_r = r + dr[d];
        int new_c = c + dc[d];
        if (new_r >= 0 && new_r < R && new_c >= 0 && new_c < C && !visited[map[new_r][new_c] - 'A'])
            dfs(depth + 1, new_r, new_c);
    }
    Ans = max(Ans, depth);
    visited[map[r][c] - 'A'] = false;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> R >> C;
        for (int r = 0; r < R; r++)
            cin >> map[r];

        dfs(1, 0, 0);           // naive하게 완탐 돌리면서 살펴봄
        cout << '#' << test_case << ' ' << Ans << "\n";

        Ans = 0;
    }
    return 0;
}
