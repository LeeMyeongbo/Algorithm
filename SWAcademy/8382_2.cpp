#include <iostream>
#define MAX 1<<30
using namespace std;

int T, start_x, start_y, dest_x, dest_y, dp[2][401][401];   // dp[0][r][c] : 가로로 도착 시 이동거리, dp[1][r][c] : 세로로 도착 시 이동거리

int main(int argc, char** argv)
{
    for (int i = 0; i < 401; i++) {
        fill(dp[0][i], dp[0][i] + 401, MAX);
        fill(dp[1][i], dp[1][i] + 401, MAX);
    }

    dp[0][0][0] = dp[1][0][0] = 0;
    for (int i = 1; i <= 400; i++) {    // 0번 행, 열 전처리
        if (i & 1) {                    // 0번 행의 홀수 번째 열과 0번 열의 홀수 번째 행 초기값 설정
            dp[1][i][0] = min(dp[1][i][0], dp[0][i - 1][0] + 1);
            dp[0][0][i] = min(dp[0][0][i], dp[1][0][i - 1] + 1);
        }
        else {                          // 0번 행의 짝수 번째 열과 0번 열의 짝수 번째 행 초기값 설정
            dp[0][i][0] = min(dp[0][i][0], dp[1][i - 1][0] + 3);
            dp[1][0][i] = min(dp[1][0][i], dp[0][0][i - 1] + 3);
        }
    }

    for (int r = 1; r <= 400; r++) {
        for (int c = 1; c <= 400; c++) {
            dp[0][r][c] = min(dp[0][r][c], dp[1][r][c - 1] + 1);
            dp[1][r][c] = min(dp[1][r][c], dp[0][r - 1][c] + 1);
        }
    }
    cin >> T;
    
    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> start_x >> start_y >> dest_x >> dest_y;
        dest_x = abs(dest_x - start_x);
        dest_y = abs(dest_y - start_y);
        start_x = start_y = 0;

        cout << '#' << test_case << ' ' << min(dp[0][dest_y][dest_x], dp[1][dest_y][dest_x]) << "\n";
    }
    return 0;
}
