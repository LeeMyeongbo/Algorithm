#include <iostream>
using namespace std;

int t;
char map[100][101];

bool Find(int start_r, int start_c, int length, bool dir)
{
    if (dir) {      // 가로 방향일 경우
        for (int i = 0; i < length / 2; i++) {
            if (map[start_r][start_c + i] != map[start_r][start_c + length - 1 - i])
                return false;
        }
    }
    else {          // 세로 방향일 경우
        for (int i = 0; i < length / 2; i++) {
            if (map[start_r + i][start_c] != map[start_r + length - 1 - i][start_c])
                return false;
        }
    }
    return true;
}

int Solve()
{
    for (int length = 100; length > 0; length--) {      // 길이가 100인 것부터 시작해서 하나씩 줄여나가며 살펴봄
        for (int start_c = 0; start_c <= 100 - length; start_c++) {         // 가로 방향으로 먼저 살피며 펠린드롬 탐색
            for (int start_r = 0; start_r < 100; start_r++) {
                if (Find(start_r, start_c, length, true))
                    return length;
            }
        }
        for (int start_r = 0; start_r <= 100 - length; start_r++) {         // 세로 방향으로 살피며 펠린드롬 탐색
            for (int start_c = 0; start_c < 100; start_c++) {
                if (Find(start_r, start_c, length, false))
                    return length;
            }
        }
    }
    return 1;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    for (int test_case = 1; test_case <= 10; ++test_case) {
        cin >> t;
        for (int r = 0; r < 100; r++)
            cin >> map[r];

        cout << '#' << test_case << ' ' << Solve() << "\n";
    }
    return 0;
}
