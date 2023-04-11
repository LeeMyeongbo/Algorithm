#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct Pos {
    int r, c;
    pair<int, long long> dist;          // 각각 m열에서 어느 행으로부터 왔는지 + 현재까지의 시간 나타냄

    bool operator<(const Pos p) const {
        return dist.second > p.dist.second;
    }
};
priority_queue<Pos> pq;
int N, M, ans[500], map[500][500];
pair<int, long long> visited[500][500];
const int dr[] = {0, 0, 1, -1}, dc[] = {1, -1, 0, 0};

void solve()                    // 다대다 다익스트라(출발점 여러 개 + 도착점 여러 개) -> 익숙해지기!
{
    memset(visited, -1, sizeof(visited));
    for (int i = 0; i < N; i++)                 // 도착점들(m열의 모든 행들)을 pq에 모두 저장
    {
        pq.push({i, M - 1, {i, 0}});
        visited[i][M - 1] = {i, 0};
    }

    while (!pq.empty())         // 그리고 그 도착점들로부터 다익스트라로 역추적하며 출발점 찾아감
    {                           // 1번 열에서 m번 열까지 도착점은 유일하다 했으므로 한 출발점에서 도착점이 2개 이상 겹칠 일은 x
        Pos p = pq.top();
        pq.pop();

        if (p.dist.second > visited[p.r][p.c].second) continue;

        int from = p.dist.first;
        long long elapsed = p.dist.second;
        for (int d = 0; d < 4; d++)
        {
            int R = p.r + dr[d];
            int C = p.c + dc[d];
            if (R >= 0 && R < N && C >= 0 && C < M && (visited[R][C].second == -1 || visited[R][C].second > elapsed + map[p.r][p.c]))
            {
                visited[R][C] = {from, elapsed + map[p.r][p.c]};
                pq.push({R, C, visited[R][C]});
            }
        }
    }
    
    for (int i = 0; i < N; i++)
        ans[visited[i][0].first]++;
    
    for (int i = 0; i < N; i++)
        cout << ans[i] << '\n';
}

int main()
{
    cin >> N >> M;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> map[i][j];
    
    solve();

    return 0;
}