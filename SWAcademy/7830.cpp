#include <iostream>
using namespace std;

int T, N, M;
const int dr[] = { 1, -1, -1, 1 }, dc[] = { 1, 1, -1, -1 };
char map[750][751];

bool determine(int r, int c, int size)
{
    int R = r, C = c - (size - 1);
    for (int d = 0; d < 4; d++) {
        for (int s = 0; s < size - 1; s++) {
            R += dr[d], C += dc[d];
            if (map[R][C] == '0')
                return false;
        }
    }
    return true;
}

int solve()
{
    int s = min(N, M);
    s = s % 2 ? s / 2 + 1 : s / 2;

    for (int size = s; size > 0; size--) {
        for (int r = size - 1; r <= N - size; r++) {
            for (int c = size - 1; c <= M - size; c++) {
                if (determine(r, c, size))
                    return size;
            }
        }
    }
    return 0;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N >> M;
        for (int i = 0; i < N; i++)
            cin >> map[i];

        cout << '#' << test_case << ' ' << solve() << "\n";
    }
    return 0;
}
