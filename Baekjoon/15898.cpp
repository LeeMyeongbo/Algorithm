#include <iostream>
using namespace std;

int N, num[10][4][4][4], ans;       // num[i][ro][r][c] : i번 재료가 ro번 회전한 상태에서의 (r, c) 자리 효능
char che[10][4][4][5];              // che[i][ro][r][c] : i번 재료가 ro번 회전한 상태에서의 (r, c) 자리 원소
bool visited[10];

void dfs(int depth)
{
    static int choose[3], rotate[3];        // choose[i] : i번째 재료가 몇 번인지, rotate[i] : i번째 재료를 몇 번 회전했는지
    static pair<int, int> start_point[3];   // start_point[i] : i번째 재료의 좌측 상단 좌표 저장

    if (depth == 3) {
        int board[5][5] = {0, };
        char ch_board[5][6];
        for (int i = 0; i < 5; i++)
            fill(ch_board[i], ch_board[i] + 5, 'W');
        
        for (int i = 0; i < 3; i++) {
            int ingred = choose[i];
            int ro = rotate[i];
            int sr = start_point[i].first;
            int sc = start_point[i].second;

            for (int r = 0; r < 4; r++) {
                for (int c = 0; c < 4; c++) {
                    int result = board[sr + r][sc + c] + num[ingred][ro][r][c];
                    if (result < 0)
                        board[sr + r][sc + c] = 0;
                    else if (result > 9)
                        board[sr + r][sc + c] = 9;
                    else
                        board[sr + r][sc + c] = result;
                    
                    if (che[ingred][ro][r][c] != 'W')
                        ch_board[sr + r][sc + c] = che[ingred][ro][r][c];
                }
            }
        }
        int effect = 0;
        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 5; c++) {
                if (ch_board[r][c] == 'R')
                    effect += board[r][c] * 7;
                else if (ch_board[r][c] == 'B')
                    effect += board[r][c] * 5;
                else if (ch_board[r][c] == 'G')
                    effect += board[r][c] * 3;
                else if (ch_board[r][c] == 'Y')
                    effect += board[r][c] * 2;
            }
        }
        ans = max(ans, effect);

        return;
    }
    for (int i = 0; i < N; i++) {                   // 총 N개 재료 중 3개 순서 고려 선택 (nP3)
        if (!visited[i]) {
            visited[i] = true;
            choose[depth] = i;
            for (int ro = 0; ro < 4; ro++) {        // i번 재료 회전(0 ~ 3번)
                rotate[depth] = ro;
                for (int sr = 0; sr < 2; sr++)
                    for (int sc = 0; sc < 2; sc++) {    // (0, 0), (0, 1), (1, 0), (1, 1) 중에서 시작 지점 선택
                        start_point[depth] = {sr, sc};
                        dfs(depth + 1);
                        start_point[depth] = {0, 0};
                    }
                rotate[depth] = 0;
            }
            choose[depth] = 0;
            visited[i] = false;
        }
    }
}

int main()
{
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int r = 0; r < 4; r++) 
            for (int c = 0; c < 4; c++)
                cin >> num[i][0][r][c];
        for (int r = 0; r < 4; r++)
            for (int c = 0; c < 4; c++)
                cin >> che[i][0][r][c];
    }

    for (int i = 0; i < N; i++)                 // 각 재료마다 1번 ~ 3번 회전한 상태 저장
        for (int ro = 1; ro < 4; ro++)
            for (int r = 0; r < 4; r++)
                for (int c = 0; c < 4; c++) {
                    num[i][ro][c][3 - r] = num[i][ro - 1][r][c];
                    che[i][ro][c][3 - r] = che[i][ro - 1][r][c];
                }
    dfs(0);
    cout << ans;

    return 0;
}