#include <iostream>
using namespace std;

int T, K, magnet[5][8], num, r;

void rotate(int m[], int dir)
{
    if (dir == 1) {                 // 시계 방향으로 돌리는 경우
        int temp = m[7];
        for (int i = 6; i >= 0; i--)
            m[i + 1] = m[i];
        m[0] = temp;
    }
    else {                          // 반시계 방향으로 돌리는 경우
        int temp = m[0];
        for (int i = 0; i < 7; i++)
            m[i] = m[i + 1];
        m[7] = temp;
    }
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> K;
        for (int i = 1; i <= 4; i++)
            for (int j = 0; j < 8; j++)
                cin >> magnet[i][j];
        
        int ans = 0;
        while (K--) {
            cin >> num >> r;

            int rot[5] = { 0, };
            rot[num] = r;
            for (int i = num; i < 4; i++) {
                if (magnet[i][2] != magnet[i + 1][6]) {
                    rot[i + 1] = rot[i] * -1;
                }
                else
                    break;
            }

            for (int i = num; i > 0; i--) {
                if (magnet[i][6] != magnet[i - 1][2]) {
                    rot[i - 1] = rot[i] * -1;
                }
                else
                    break;
            }

            for (int i = 1; i <= 4; i++) {
                if (rot[i])
                    rotate(magnet[i], rot[i]);
            }
        }

        for (int i = 1; i <= 4; i++)
            if (magnet[i][0])
                ans += 1 << (i - 1);

        cout << '#' << test_case << ' ' << ans << "\n";
    }
    return 0;
}
