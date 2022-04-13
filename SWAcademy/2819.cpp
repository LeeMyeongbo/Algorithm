#include <iostream>
#include <set>
using namespace std;

int T, map[4][4], ans;
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
set<string> visited;
string str = "";

void dfs(int depth, int r, int c)
{
    if (depth == 7) {
        if (!visited.count(str)) {
            visited.insert(str);
            ans++;
        }
        return;
    }

    for (register int d = 0; d < 4; d++) {
        register int R = r + dr[d];
        register int C = c + dc[d];
        if (R >= 0 && R < 4 && C >= 0 && C < 4) {
            str.push_back(map[R][C] + '0');
            dfs(depth + 1, R, C);
            str.pop_back();
        }
    }
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (register int test_case = 1; test_case <= T; ++test_case) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                cin >> map[i][j];

        for (int r = 0; r < 4; r++)
            for (int c = 0; c < 4; c++) {
                str.push_back(map[r][c]);
                dfs(1, r, c);
                str.pop_back();
            }

        cout << '#' << test_case << ' ' << ans << "\n";
        ans = 0;
        visited.clear();
    }
    return 0;
}
