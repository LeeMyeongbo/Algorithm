#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int map[1000][1000], chk[1000][1000];
const int dr[] = {0, 0, 1, -1}, dc[] = {1, -1, 0, 0};

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    register int N, M, Max = 0;

    cin >> N >> M;
    for (int r = 0; r < N; r++)
        for (int c = 0; c < M; c++)
            cin >> map[r][c];
    
    vector<int> shape;                      // shape[i - 1] : map에서 i(i >= 1) 번째의 모양의 크기 저장
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            if (chk[r][c] || !map[r][c])    // 이미 체크한 곳 또는 0인 곳은 skip
                continue;

            int cnt = 0;
            queue<pair<int, int>> q;
            q.push({r, c});
            chk[r][c] = shape.size() + 1;   // 각 격자 자리마다 몇 번째 모양인지 저장

            while(!q.empty()) {
                int cur_r = q.front().first;
                int cur_c = q.front().second;
                q.pop();

                cnt++;
                for (int d = 0; d < 4; d++) {
                    int R = cur_r + dr[d];
                    int C = cur_c + dc[d];
                    if (R >= 0 && R < N && C >= 0 && C < M && !chk[R][C] && map[R][C]) {
                        q.push({R, C});
                        chk[R][C] = chk[r][c];
                    }
                }
            }
            Max = max(Max, cnt);            // 모양 크기의 최댓값 갱신
            shape.push_back(cnt);
        }
    }

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            if (map[r][c])                  // map에서 1인 곳은 건너뛰고 0인 곳만 바꿔주면서 진행
                continue;
            
            int tmp = 1;
            vector<int> appeared;           // 이미 추가한 모양의 index 저장
            for (int d = 0; d < 4; d++) {   // 바꾼 곳 주위로 4방향 둘러보면서 몇 번 index의 모양이 있는지 판별
                int R = r + dr[d];
                int C = c + dc[d];
                if (R >= 0 && R < N && C >= 0 && C < M) {
                    bool flag = true;
                    if (chk[R][C]) {
                        for (int i : appeared) {    // 모양이 존재할 경우 이미 살펴봤던 모양은 아닌지 판별
                            if (i == chk[R][C])
                                flag = false;
                        }
                        if (flag) {                 // 살펴봤던 모양은 아닌 새로운 index의 모양이면 크기만큼 더해줌
                            appeared.push_back(chk[R][C]);
                            tmp += shape[chk[R][C] - 1];
                        }
                    }
                }
            }
            Max = max(Max, tmp);
        }
    }
    cout << Max;
    return 0;
}