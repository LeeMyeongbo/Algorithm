#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

char map[50][51];
const int dr[] = {-1, -1, 0, 1, 1, 0}, dc[] = {0, 1, 1, 0, -1, -1};

bool bfs(int& N, int num)                              // num : 사용 가능한 색깔 개수
{
    int chk[50][50];
    memset(chk, -1, sizeof(chk));                      // 색깔이 없으면 -1, 색깔 있으면 0~(num-1)로 표시

    for (register int i = 0; i < N; i++) {
        for (register int j = 0; j < N; j++) {
            if (map[i][j] == 'X' && chk[i][j] == -1) {
                if (!num) return false;                // 'X'가 있는데 사용 가능한 색깔이 0가지라면 바로 컽

                queue<pair<int, pair<int, int>>> q;    // (현재 사용 중인 색깔, (r, c))
                chk[i][j] = 0;
                q.push({chk[i][j], {i, j}});

                while (!q.empty()) {
                    int cur = q.front().first;
                    int r = q.front().second.first;
                    int c = q.front().second.second;
                    q.pop();

                    for (register int d = 0; d < 6; d++) {
                        int R = r + dr[d];
                        int C = c + dc[d];
                        if (R >= 0 && R < N && C >= 0 && C < N && map[R][C] == 'X') {
                            if (chk[R][C] == -1) {
                                chk[R][C] = (cur + 1) % num;
                                q.push({chk[R][C], {R, C}});
                            }
                            else if (chk[R][C] == chk[r][c])
                                return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

int main()
{
    int N;
    cin >> N;
    for (register int i = 0; i < N; i++)
        cin >> map[i];
    
    for (int i = 0; i < 3; i++) {   // 0, 1, 2가지 색깔 차례로 써봄
        if (bfs(N, i)) {
            cout << i;
            return 0;
        }
    }

    cout << 3;                      // 0~2까지 다 안된다면 답은 3!
    return 0;
}