#include <iostream>
using namespace std;

int T, Min = -1, Ans;
int map[100][100];
const int dr[] = { 0, 0, 1 }, dc[] = { 1, -1, 0 };       // 0 : 동, 1 : 서, 2 : 남

int solve()
{
    for (int x = 0; x < 100; x++) {
        if (map[0][x]) {
            int r = 0, c = x, move = 0, dir = 2;         // r : 행, c : 열, move : 움직인 횟수, dir : 방향(지금은 남쪽)
            while (r < 99) {
                r += dr[dir], c += dc[dir];

                if (dir == 2 && c + 1 < 100 && map[r][c + 1])        // 동쪽에 통로 있다면 방향을 동쪽으로
                    dir = 0;
                else if (dir == 2 && c - 1 >= 0 && map[r][c - 1])    // 서쪽에 통로 있다면 방향을 서쪽으로
                    dir = 1;
                else if (dir != 2 && map[r + 1][c])                  // 남쪽에 통로 있다면 방향을 남쪽으로
                    dir = 2;
                move++;
            }
            if (Min == -1 || Min >= move) {
                Min = move;
                Ans = x;
            }
        }
    }
    return Ans;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    for (int test_case = 1; test_case <= 10; ++test_case) {
        cin >> T;
        for (int r = 0; r < 100; r++)
            for (int c = 0; c < 100; c++)
                cin >> map[r][c];

        cout << '#' << test_case << ' ' << solve() << endl;
        Min = -1;
    }
    return 0;
}
