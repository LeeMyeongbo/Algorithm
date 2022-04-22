#include <iostream>
#include <queue>
using namespace std;

int N, M, H[100][100], Ans;
const int dr[] = {0, 0, 1, -1}, dc[] = {1, -1, 0, 0};

int BFS(int r, int c)
{
    queue<pair<int, int>> q;
    bool visited[100][100] = {false, };
    int Min = 10001, ret = 0;

    q.push({r, c});
    visited[r][c] = true;

    while (!q.empty()) {
        int cur_r = q.front().first;
        int cur_c = q.front().second;
        q.pop();

        if (cur_r == 0 || cur_r == N - 1 || cur_c == 0 || cur_c == M - 1)
            return 0;                           // 현재 가장자리에 위치하고 있으면 물이 빠져나감 -> 바로 종료

        for (int d = 0; d < 4; d++) {
            int R = cur_r + dr[d];
            int C = cur_c + dc[d];
            if (R >= 0 && R < N && C >= 0 && C < M && !visited[R][C]) {
                if (H[R][C] <= H[r][c]) {       // BFS를 시작한 위치(r, c)보다 높이가 작거나 같은 곳을 탐색
                    q.push({R, C});
                    visited[R][C] = true;
                }
                else
                    Min = min(Min, H[R][C]);    // 높이가 크다면 그 중에서 최저 높이 갱신
            }
        }
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (visited[i][j])
                ret += (Min - H[i][j]), H[i][j] = Min;  // 방문한 곳에 물을 채우고 채운 양을 리턴
    
    return ret;
}

int main()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> H[i][j];
    
    for (int r = 1; r < N - 1; r++)
        for (int c = 1; c < M - 1; c++)
            Ans += BFS(r, c);               // 매 위치마다 BFS 시행

    cout << Ans;
    return 0;
}