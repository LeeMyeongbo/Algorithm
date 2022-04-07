#include <iostream>
#include <cstring>
using namespace std;

int T, test_case;
char board[2][6][7];                      // [0][r][c] : 분자(자연수), [1][r][c] : 분모
bool fraction[6][6];                      // 분수인 곳은 true로 처리
bool complete;

bool unsame_row(char n, int r)            // (r, c)격자와 같은 행에 겹치는 숫자가 있는지 판단
{
    for (int c = 0; c < 6; c++) {
        if (board[0][r][c] == n)
            return false;
        if (fraction[r][c] && board[1][r][c] == n)
            return false;
    }
    return true;
}

bool unsame_col(char n, int c)            // (r, c)격자와 같은 열에 겹치는 숫자가 있는지 판단
{
    for (int r = 0; r < 6; r++) {
        if (board[0][r][c] == n)
            return false;
        if (fraction[r][c] && board[1][r][c] == n)
            return false;
    }
    return true;
}

bool unsame_2x3(char n, int r, int c)     // (r, c)격자가 속한 2x3 영역에 겹치는 숫자가 있는지 판단
{
    r -= (r % 2), c -= (c % 3);
    for (int R = r; R < r + 2; R++) {
        for (int C = c; C < c + 3; C++) {
            if (board[0][R][C] == n)
                return false;
            if (fraction[R][C] && board[1][R][C] == n)
                return false;
        }
    }
    return true;
}

void solve(int denom, int r, int c)     // denom : 현재 위치가 자연수 or 분자일 경우 0, 분모일 경우 1 
{
    if (r == 6) {                               // 마지막 숫자까지 모두 채웠을 경우 답 출력
        cout << '#' << test_case << '\n';
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                cout << board[0][i][j];
                if (fraction[i][j])
                    cout << '/' << board[1][i][j];
                cout << ' ';
            }
            cout << '\n';
        }
        complete = true;                // 완료 처리
        return;
    }
    if (board[denom][r][c] == '-') {    // 숫자를 채워야 하는 경우엔 1부터 9까지 순서대로 살피며 숫자 집어넣음
        for (char n = '1'; n <= '9'; n++) {
            if (unsame_row(n, r) && unsame_col(n, c) && unsame_2x3(n, r, c)) {
                board[denom][r][c] = n;
                if (fraction[r][c]) {                                   // 현재 위치가 분수일 경우
                    if (!denom && ((board[1][r][c] != '-' && n < board[1][r][c]) || board[1][r][c] == '-'))
                        solve(1, r, c);                                 // 현재 분자일 경우 분모보다 작거나 분모가 아직 '-'여야만 계속 진행
                    else if (denom && n > board[0][r][c]) {             // 현재 분모일 경우 분자보다 커야 계속 진행
                        if (c < 5) solve(0, r, c + 1);
                        else solve(0, r + 1, 0);
                    }
                }
                else {
                    if (c < 5) solve(0, r, c + 1);
                    else solve(0, r + 1, 0);
                }
                board[denom][r][c] = '-';

                if (complete)           // 완료됐을 시엔 함수 종료
                    return;
            }
        }
    }
    else {
        if (fraction[r][c] && !denom) solve(1, r, c);   // 현재 위치가 분자면 분모로 이동하여 진행
        else {                                          // 그 외의 경우엔 다음 열의 정수(분자), 마지막 열의 경우엔 다음 행의 첫 번째 열의 정수(분자)로 이동
            if (c < 5) solve(0, r, c + 1);
            else solve(0, r + 1, 0);
        }
    }
}

int main(int argc, char** argv)
{
    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case) {
        memset(board, 0, sizeof(board));
        memset(fraction, false, sizeof(fraction));

        for (int r = 0; r < 6; r++) {
            for (int c = 0; c < 6; c++) {
                string element;
                cin >> element;
                board[0][r][c] = element[0];
                    
                if (element.length() > 1) {
                    board[1][r][c] = element[2];
                    fraction[r][c] = true;
                }
            }
        }
        solve(0, 0, 0);
        complete = false;
    }
    return 0;
}
