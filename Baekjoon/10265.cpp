#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

int n, k, x, cnt, order[1001], connectedCnt;    // connectedCnt : 그래프 내 연결 요소 개수
int sccCnt, scc[1001], sccSize[1001];           // scc[i] : i번 사람이 몇 번째 scc에 속하는 지, sccSize[i] : i번째 scc의 크기
int dp[1001][1001];                             // dp[i][j] : 버스에 j명까지 탑승이 가능할 때, 1 ~ i번 연결 요소까지 고려했을 경우 최대 탑승 가능 인원
bool visited[1001];
pair<int, int> minmaxByCC[1001];                // minmaxByCC[i] : i번 연결 요소에서 (태워야 될 사람 수의 최솟값, 최댓값)
stack<int> s;
vector<int> graph[1001], bidirectionalGraph[1001];
queue<int> q;

int findSCC(int cur)
{
    int p = order[cur] = ++cnt;
    s.emplace(cur);

    for (int& to : graph[cur])
    {
        if (!order[to])
            p = min(p, findSCC(to));
        else if (!scc[to])
            p = min(p, order[to]);
    }

    if (p == order[cur])
    {
        ++sccCnt;
        while (!s.empty())
        {
            register int v = s.top();
            s.pop();

            scc[v] = sccCnt;
            ++sccSize[sccCnt];

            if (p == order[v])
                break;
        }
    }

    return p;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n >> k;
    for (register int i = 1; i <= n; ++i)           // 간선이 정확히 n개이므로 연결 요소 하나 당 사이클이 1개씩만 존재
    {
        cin >> x;
        graph[i].emplace_back(x);

        bidirectionalGraph[i].emplace_back(x);
        bidirectionalGraph[x].emplace_back(i);
    }

    // 각 정점(사람)마다 SCC 탐색
    for (register int i = 1; i <= n; ++i)
        if (!scc[i])
            findSCC(i);

    // 연결 요소 별로 버스에 태워야 될 사람의 최댓값 및 최솟값 저장
    for (register int i = 1; i <= n; ++i)
    {
        if (!visited[i])
        {
            register int M = 0, m = 0;
            visited[i] = true;
            q.emplace(i);

            while (!q.empty())
            {
                register int cur = q.front();
                q.pop();

                ++M;
                m = max(m, sccSize[scc[cur]]);

                for (int& to : bidirectionalGraph[cur])
                {
                    if (!visited[to])
                    {
                        visited[to] = true;
                        q.emplace(to);
                    }
                }
            }

            minmaxByCC[++connectedCnt] = { m, M };
        }
    }

    // DP 진행
    for (register int i = 1; i <= connectedCnt; ++i)
    {
        for (register int j = 1; j <= k; ++j)
        {
            if (j < minmaxByCC[i].first)        // j가 현재 i번 연결 요소에서 최소한 태워야 할 인원(min)보다 작을 경우
                dp[i][j] = dp[i - 1][j];        // i-1번 연결 요소까지 고려했을 때의 최댓값과 동일
            else if (j >= minmaxByCC[i].first && j <= minmaxByCC[i].second)
                dp[i][j] = j;
            else                                // j가 현재 i번 연결 요소에서 최대 태울 수 있는 인원(max)을 넘어섰을 경우
            {
                // dp[i - 1][j], min + dp[i - 1][j - min], ..., max + dp[i - 1][j - max] 중 최댓값을 취함
                for (register int k = minmaxByCC[i].first; k <= minmaxByCC[i].second; ++k)
                {
                    register int tmp = max(k + dp[i - 1][j - k], dp[i - 1][j]);    
                    dp[i][j] = max(tmp, dp[i][j]);
                }
            }
        }
    }

    cout << dp[connectedCnt][k];

    return 0;
}
