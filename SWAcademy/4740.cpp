#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

int T, N, M, Q;
const int dr[] = { 1, -1, 0, 0 }, dc[] = { 0, 0, 1, -1 };
char map[30][31], query, tmp[30];

void move_down()            // 밑으로 떨어질 땐 가장 아래 블록에서부터 시작해서 차례대로 최대한 아래쪽으로 옮김
{
    for (int r = N - 2; r >= 0; r--) {
        for (int c = 0; c < M; c++) {
            int R = r;
            while (R + 1 < N && map[R + 1][c] == '#') {
                map[R + 1][c] = map[R][c];
                map[R++][c] = '#';
            }
        }
    }
}

int getMax()                // 크기가 가장 큰 블록 집합의 크기 반환
{
    queue<pair<int, int>> q;
    bool visited[30][30] = { false, };
    int Max = 0;

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            if (visited[r][c] || map[r][c] == '#')
                continue;

            q.push( {r, c} );
            visited[r][c] = true;
            int cnt = 0;
            char color = map[r][c];

            while (!q.empty()) {
                int cur_r = q.front().first;
                int cur_c = q.front().second;
                q.pop();

                cnt++;
                for (int d = 0; d < 4; d++) {
                    int R = cur_r + dr[d];
                    int C = cur_c + dc[d];
                    if (R >= 0 && R < N && C >= 0 && C < M && !visited[R][C] && map[R][C] == color) {
                        visited[R][C] = true;
                        q.push({ R, C });
                    }
                }
            }
            Max = max(Max, cnt);
        }
    }
    return Max;
}

void destroy(int Max)           // 전달받은 크기의 블록 집합 삭제
{
    queue<pair<int, int>> q;
    bool visited[30][30] = { false, };

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            if (visited[r][c] || map[r][c] == '#')
                continue;

            q.push({ r, c });
            visited[r][c] = true;
            
            vector<pair<int, int>> list;
            char color = map[r][c];

            while (!q.empty()) {
                int cur_r = q.front().first;
                int cur_c = q.front().second;
                q.pop();

                list.push_back({ cur_r, cur_c });
                for (int d = 0; d < 4; d++) {
                    int R = cur_r + dr[d];
                    int C = cur_c + dc[d];
                    if (R >= 0 && R < N && C >= 0 && C < M && !visited[R][C] && map[R][C] == color) {
                        visited[R][C] = true;
                        q.push({ R, C });
                    }
                }
            }
            
            if (list.size() == Max) {
                for (auto& p : list)
                    map[p.first][p.second] = '#';
            }
        }
    }
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N >> M >> Q;
        for (int r = 0; r < N; r++)
            cin >> map[r];
        move_down();                // 혹시나 초기에 붕 떠 있는 블록이 있을 수도 있으니까 먼저 떨어뜨리고 시작

        while (Q--) {
            cin >> query;
            if (query == 'U') {
                cin >> tmp;
                bool possible = true;
                for (int i = 0; i < M; i++) {
                    if (map[0][i] != '#') {             // 천장에 블록이 하나라도 닿아 있으면 못 올림
                        possible = false;
                        break;
                    }
                }
                if (possible) {                         // 천장과 닿아있는 블록이 없다면 
                    for (int r = 1; r < N; r++)
                        for (int c = 0; c < M; c++)
                            map[r - 1][c] = map[r][c];  // 한 칸씩 올림
                    for (int i = 0; i < M; i++)
                        map[N - 1][i] = tmp[i];         // 그리고 맨 밑에 입력한 거 추가
                }
                move_down();                            // 떨어뜨리기!
            }
            else if (query == 'L') {                    // 왼쪽으로 밀착할 땐 왼쪽 블럭에서부터 시작해서 차례대로 최대한 왼쪽으로 옮김
                for (int c = 1; c < M; c++) {
                    for (int r = 0; r < N; r++) {
                        int C = c;
                        while (C > 0 && map[r][C - 1] == '#') {
                            map[r][C - 1] = map[r][C];
                            map[r][C--] = '#';
                        }
                    }
                }
            }
            else if (query == 'R') {                    // 오른쪽으로 밀착할 땐 오른쪽 블럭에서부터 시작해서 차례대로 최대한 오른쪽으로!
                for (int c = M - 2; c >= 0; c--) {
                    for (int r = 0; r < N; r++) {
                        int C = c;
                        while (C + 1 < M && map[r][C + 1] == '#') {
                            map[r][C + 1] = map[r][C];
                            map[r][C++] = '#';
                        }
                    }
                }
            }
            else {                                      // D일 경우 
                int Max = getMax();                     // BFS 한 번 돌리면서 크기가 가장 큰 블록 집합의 블록 수 구함
                destroy(Max);                           // 그리고 BFS 한 번 더 돌리면서 크기가 가장 큰 블록 집합 삭제
                move_down();
            }
        }
        cout << '#' << test_case << "\n";
        for (int r = 0; r < N; r++)
            cout << map[r] << "\n";
        cout << "\n";

        memset(map, 0, sizeof(map));
    }
    return 0;
}
