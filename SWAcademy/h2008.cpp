#include <queue>
#include <vector>
#include <cstring>
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
using namespace std;

extern bool swap(int dir);

int board[5][5], pattern[3][3], from[5][5], emptyR, emptyC, movingR, movingC;   // (emptyR, emptyC) : 빈 곳의 위치, (movingR, movingC) : 원하는 색깔의 위치
bool check[5][5];                                                               // 이미 board에서 맞춘 부분은 true로 처리
const int dr[] = { -1, 0, 1, 0 }, dc[] = { 0, 1, 0, -1 };                       // up -> right -> down -> left 순서
vector<pair<int, int>> path;

void update(int r, int c, int old_r, int old_c)         // (old_r, old_c)에 있던 색깔을 (r, c)위치에 있던 빈 칸과 바꿈
{
    board[r][c] = board[old_r][old_c];
    board[old_r][old_c] = 0;
}

void bfs(int r, int c, bool finding)
{
    queue<pair<int, int>> q;
    bool visited[5][5] = { false, };

    q.push({ r, c });
    visited[r][c] = true;

    while (!q.empty())
    {
        if (finding) path.push_back(q.front());
        register int cur_r = q.front().first;
        register int cur_c = q.front().second;
        q.pop();

        for (int d = 0; d < 4; d++)
        {
            register int new_r = cur_r + dr[d];
            register int new_c = cur_c + dc[d];
            if (new_r >= 0 && new_r < 5 && new_c >= 0 && new_c < 5 && !visited[new_r][new_c] && !check[new_r][new_c])
            {
                q.push({ new_r, new_c });
                visited[new_r][new_c] = true;
                from[new_r][new_c] = d;                 // (new_r, new_c)에 어떤 방향으로 움직여서 도달했는지 그 방향을 저장
            }
        }
    }
}

void moveEmpty(int r, int c)
{
    bfs(r, c, false);

    while (emptyR != r || emptyC != c)                          // 빈 곳이 (r, c)에 도달할 때까지 반복
    {
        register int dir = (from[emptyR][emptyC] + 2) % 4;

        swap(dir);
        update(emptyR, emptyC, emptyR + dr[dir], emptyC + dc[dir]);
        emptyR += dr[dir];
        emptyC += dc[dir];
    }
}

void solve(int mboard[5][5], int mpattern[3][3], int callCntLimit)
{
    memcpy(board, mboard, sizeof(board));
    memcpy(pattern, mpattern, sizeof(pattern));
    memset(check, false, sizeof(check));

    for (register int r = 0; r < 5; r++)
        for (register int c = 0; c < 5; c++)
            if (!board[r][c])
                emptyR = r, emptyC = c;

    for (register int r = 1; r < 4; r++)
        for (register int c = 1; c < 4; c++)
        {
            if (board[r][c] == pattern[r - 1][c - 1])           // 현재 (r, c)에서 패턴 색깔과 보드 색깔 같다면 check하고 넘김
            {
                check[r][c] = true;
                continue;
            }

            path.clear();
            bfs(r, c, true);                                    // 현재 (r, c)에서부터 이미 맞춘 부분 제외한 위치들까지의 최단 경로 저장
            for (pair<int, int>& pos : path)
                if (board[pos.first][pos.second] == pattern[r - 1][c - 1])
                {
                    movingR = pos.first, movingC = pos.second;  // 원하는 색깔을 최초로 발견했을 때 위치를 (movingR, movingC)에 저장
                    break;
                }

            int tmp[5][5];
            memcpy(tmp, from, sizeof(from));                    // movingR과 movingC가 움직일 경로를 미리 저장

            while (movingR != r || movingC != c)                // movingR, movingC가 최종 도착할 (r, c)에 도달달 때까지 반복
            {
                register int d = tmp[movingR][movingC];         // d : (movingR, movingC)에 도달했을 때 방향
                register int toR = movingR - dr[d];
                register int toC = movingC - dc[d];             // (toR, toC) : (r, c)에서 (movingR, movingC)에 도달하기 직전 위치

                check[movingR][movingC] = true;
                moveEmpty(toR, toC);                            // 빈 칸을 (toR, toC)로 옮김
                check[movingR][movingC] = false;

                swap(d);
                update(toR, toC, movingR, movingC);
                emptyR = movingR, emptyC = movingC;             // swap 이후 (movingR, movingC)자리에 빈 칸이 옴
                movingR = toR, movingC = toC;                   // 그리고 (movingR, movingC)는 (toR, toC)로 옮겨가겠지
            }

            check[r][c] = true;
        }
}
