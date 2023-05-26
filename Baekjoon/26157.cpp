#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#define MAX 200000 + 1
using namespace std;

int order[MAX], cnt, scc[MAX], scc_cnt, scc_indegree[MAX], scc_candidate;
stack<int> s;
vector<int> graph[MAX], scc_graph[MAX], ans;
queue<int> q;

int getSCC(int cur)
{
    int p = order[cur] = ++cnt;
    s.emplace(cur);

    for (int& to : graph[cur])
    {
        if (!order[to])
            p = min(p, getSCC(to));
        else if (!scc[to])
            p = min(p, order[to]);
    }

    if (p == order[cur])
    {
        ++scc_cnt;
        while (!s.empty())
        {
            register int v = s.top();
            s.pop();

            scc[v] = scc_cnt;

            if (p == order[v])
                break;
        }
    }

    return p;
}

bool topological(int& N)
{
    for (register int v = 1; v <= N; ++v)           // scc 축약 그래프(DAG) 형성 + 각 scc마다 진입 차수 저장
        for (int& to : graph[v])
            if (scc[to] != scc[v])
            {
                scc_graph[scc[v]].emplace_back(scc[to]);
                ++scc_indegree[scc[to]];
            }

    for (register int s = 1; s <= scc_cnt; ++s)     // 진입 차수가 0인 scc 큐에 삽입 + 정답 후보에 해당 scc 저장
        if (!scc_indegree[s])
        {
            q.push(s);
            scc_candidate = s;
        }

    while (!q.empty())
    {
        if (q.size() > 1)                           // 큐에 저장된 scc가 2개 이상 -> 가능한 위상 정렬 개수가 여러 개 -> 해밀턴 경로 x
            return false;

        register int cur_scc = q.front();
        q.pop();

        for (int& to : scc_graph[cur_scc])
        {
            --scc_indegree[to];
            if (!scc_indegree[to])
                q.emplace(to);
        }
    }

    return true;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    register int N, M, v, w;
    cin >> N >> M;

    for (register int e = 0; e < M; ++e)
    {
        cin >> v >> w;
        graph[v].emplace_back(w);
    }

    for (register int v = 1; v <= N; ++v)           // 모든 정점들의 scc 구함
        if (!scc[v])
            getSCC(v);

    if (topological(N))
    {
        for (register int v = 1; v <= N; ++v)
            if (scc[v] == scc_candidate)
                ans.emplace_back(v);

        cout << ans.size() << '\n';
        for (int& i : ans)
            cout << i << ' ';
    }
    else
        cout << 0;

    return 0;
}
