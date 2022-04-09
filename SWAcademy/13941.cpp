#include <iostream>
#include <queue>
using namespace std;

int T, N, M, s_r, s_c, map[101][101], ans = -1;
const int dr[] = { 1, -1, 0, 0 }, dc[] = { 0, 0, 1, -1 };
pair<int, int> pos[3], start[3];        // pos : 침대, 의자, 바닥 위치 | start : 침대 복치, 의자 복치, 바닥 복치 시작순으로 저장
char c;
bool chk[3];

void solve(int depth)
{
    static int seq[3];
    
    if (depth == 3) {
        int sum = 0;
        for (int i = 0; i < 3; i++)
            map[pos[i].first][pos[i].second] = seq[i] + 1;      // 침대를 1, 의자를 2, 바닥을 3으로 저장

        for (int i = 0; i < 3; i++) {   // 침대 복치, 의자 복치, 바닥 복치 순으로 진행
            int tmp = 0;                // 각 개복치마다 목적지에 도달하기까지의 최단 거리
            bool arrived = false;       // 각 개복치가 목적지에 도달했는지 여부

            queue<pair<int, pair<int, int>>> q;
            bool visited[101][101] = { false, };

            q.push({ 0, {start[i].first, start[i].second} });
            visited[start[i].first][start[i].second] = true;

            while (!q.empty()) {
                int move = q.front().first;
                int r = q.front().second.first;
                int c = q.front().second.second;
                q.pop();

                if (map[r][c] == i + 1) {   // 각 개복치가 원하는 목적지에 도달했을 경우
                    tmp = move;
                    arrived = true;
                    break;
                }

                for (int d = 0; d < 4; d++) {
                    int R = r + dr[d];
                    int C = c + dc[d];
                    if (R >= 1 && R <= N && C >= 1 && C <= M && !visited[R][C] && map[R][C] != -1) {
                        q.push({ move + 1, {R, C} });
                        visited[R][C] = true;
                    }
                }
            }
            if (arrived)
                sum += tmp;
            else
                return;     // 만약 원하는 목적지에 한 마리라도 도달하지 못했다면 바로 종료
        }
        if (ans == -1)
            ans = sum;

        ans = min(sum, ans);    // 거리 합 최솟값 갱신
        return;
    }

    for (int i = 0; i < 3; i++) {       // 순열 활용
        if (!chk[i]) {
            chk[i] = true;
            seq[depth] = i;
            solve(depth + 1);
            seq[depth] = 0;
            chk[i] = false;
        }
    }
}

int main(int argc, char** argv)
{
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        int idx = 0;

        cin >> N >> M;
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                map[i][j] = 0;                      // 항상 map은 초기화하기!

                cin >> c;
                if (c == '#')
                    map[i][j] = -1;
                else if (c == 'B' || c == 'C' || c == '_')
                    pos[idx++] = { i, j };
            }
        }
        for (int i = 0; i < 3; i++)
            cin >> start[i].first >> start[i].second;
        
        solve(0);
        cout << '#' << test_case << ' ' << ans << '\n';

        ans = -1;
    }
    return 0;
}
