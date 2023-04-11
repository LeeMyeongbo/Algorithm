#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct Node {
    int r, c;
    long long cost;

    bool operator<(const Node& n)const {
        return cost > n.cost;
    }
};
priority_queue<Node> pq;
int N, M, map[300][300];
long long dij[300][300];
const int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1}, dc[] = {0, 1, 1, 1, 0, -1, -1, -1};

long long solve()
{
    memset(dij, -1, sizeof(dij));

    for (int i = 1; i < N - 1; i++)         // 제일 왼쪽에 있는 열의 벽 세울 수 있는 곳 저장
    {
        if (map[i][0] > -1)
        {
            pq.push({i, 0, map[i][0]});
            dij[i][0] = map[i][0];
        }
    }
    for (int j = 0; j < M - 1; j++)         // 제일 아래에 있는 행의 벽 세울 수 있는 곳 저장
    {
        if (map[N - 1][j] > -1)
        {
            pq.push({N - 1, j, map[N - 1][j]});
            dij[N - 1][j] = map[N - 1][j];
        }
    }

    while (!pq.empty())
    {
        Node node = pq.top();
        pq.pop();

        if (node.r == 0 || node.c == M - 1)     // 제일 위의 행 또는 제일 오른쪽 열에 도달하면 종료
            return node.cost;
        
        for (int d = 0; d < 8; d++)
        {
            int R = node.r + dr[d];
            int C = node.c + dc[d];
            if (R >= 0 && R < N && C >= 0 && C < M && map[R][C] > -1 && (dij[R][C] == -1 || dij[R][C] > node.cost + map[R][C]))
            {
                dij[R][C] = node.cost + map[R][C];
                pq.push({R, C, dij[R][C]});
            }
        }
    }

    return -1;
}

int main()
{
    cin >> N >> M;
    for (int r = 0; r < N; r++)
        for (int c = 0; c < M; c++)
        {
            cin >> map[r][c];
            if (map[r][c] == -2)
                map[r][c] = 0;          // 벽이 있다 = 벽을 세우는 데 비용이 0인 경우와 같음!
        }    
    
    cout << solve();

    return 0;
}