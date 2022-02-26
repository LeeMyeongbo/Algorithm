#include <iostream>
using namespace std;

int T, R, C, mem;
char map[20][21];
bool visited[16][4][20][20];

bool dfs(int r, int c, int dir)             // dir : 0=서, 1=동, 2=북, 3=남
{
    if (visited[mem][dir][r][c])
        return false;
    visited[mem][dir][r][c] = true;

    switch (map[r][c]) {
    case '<':
        return dfs(r, (c + C - 1) % C, 0);
    case '>':
        return dfs(r, (c + 1) % C, 1);
    case '^':
        return dfs((r + R - 1) % R, c, 2);
    case 'v':
        return dfs((r + 1) % R, c, 3);
    case '_':
        if (mem)
            return dfs(r, (c + C - 1) % C, 0);
        else
            return dfs(r, (c + 1) % C, 1);
    case '|':
        if (mem)
            return dfs((r + R - 1) % R, c, 2);
        else
            return dfs((r + 1) % R, c, 3);
    case '?':                                   // '?'일 경우에는 어쩔 수 없이 4방향 모두 탐색해 봐야 함 (dfs로 해야하는 이유)
        if (dfs(r, (c + C - 1) % C, 0))         // 프로그램을 정지할 수 있을 때까지 최대한 계속 해봄
            return true;
        if (dfs(r, (c + 1) % C, 1))
            return true;
        if (dfs((r + R - 1) % R, c, 2))
            return true;
        return dfs((r + 1) % R, c, 3);
    case '.':
        if (!dir)
            return dfs(r, (c + C - 1) % C, 0);
        else if (dir == 1)
            return dfs(r, (c + 1) % C, 1);
        else if (dir == 2)
            return dfs((r + R - 1) % R, c, 2);
        else
            return dfs((r + 1) % R, c, 3);
    case '@':
        return true;
    case '+':
        mem = (mem + 1) % 16;
        if (!dir)
            return dfs(r, (c + C - 1) % C, 0);
        else if (dir == 1)
            return dfs(r, (c + 1) % C, 1);
        else if (dir == 2)
            return dfs((r + R - 1) % R, c, 2);
        else
            return dfs((r + 1) % R, c, 3);
    case '-':
        mem = (mem + 15) % 16;
        if (!dir)
            return dfs(r, (c + C - 1) % C, 0);
        else if (dir == 1)
            return dfs(r, (c + 1) % C, 1);
        else if (dir == 2)
            return dfs((r + R - 1) % R, c, 2);
        else
            return dfs((r + 1) % R, c, 3);
    default:
        mem = map[r][c] - '0';
        if (!dir)
            return dfs(r, (c + C - 1) % C, 0);
        else if (dir == 1)
            return dfs(r, (c + 1) % C, 1);
        else if (dir == 2)
            return dfs((r + R - 1) % R, c, 2);
        else
            return dfs((r + 1) % R, c, 3);
    }
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> R >> C;
        for (int r = 0; r < R; r++)
            cin >> map[r];

        cout << '#' << test_case << ' ';
        if (dfs(0, 0, 1))
            cout << "YES\n";
        else
            cout << "NO\n";

        for (int a = 0; a < 16; a++)
            for (int b = 0; b < 4; b++)
                for (int c = 0; c < R; c++)
                    for (int d = 0; d < C; d++)
                        visited[a][b][c][d] = false;
        mem = 0;
    }
    return 0;
}
