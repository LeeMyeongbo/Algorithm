#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int order[100001], cnt;
int scc[100001], indegree_scc[100001], scc_cnt;     // scc[i] : i번 정점(건물)이 몇 번째 scc에 속하는 지, indegree_scc[i] : i번 scc의 진입 차수
vector<int> graph[100001];
stack<int> s;

int getSCC(int cur)
{
    int p = order[cur] = ++cnt;
    s.push(cur);

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

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    register int N, M, x, y, ans = 0;
    cin >> N >> M;

    for (register int e = 0; e < M; ++e)
    {
        cin >> x >> y;
        graph[x].emplace_back(y);
    }

    for (register int v = 1; v <= N; ++v)
        if (!scc[v])
            getSCC(v);

    for (register int from = 1; from <= N; ++from)
        for (int& to : graph[from])
            if (scc[from] != scc[to])
                ++indegree_scc[scc[to]];

    for (register int s = 1; s <= scc_cnt; ++s)
        if (!indegree_scc[s])
            ++ans;

    cout << ans;

    return 0;
}
