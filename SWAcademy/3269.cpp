#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
using namespace std;

int order[10001], cnt, K;       // order[i] : i번 정점의 방문 순서
bool complete[10001];           // complete[i] : i번 정점의 scc 탐색이 완료되었는지의 여부
vector<int> graph[10001];
stack<int> s;

int findSCC(int cur)
{
    order[cur] = ++cnt;
    register int p = order[cur];
    s.push(cur);

    for (int& v : graph[cur])
    {
        if (!order[v])
            p = min(p, findSCC(v));     // 방문한 적 없는 정점의 경우 방문 + p의 최솟값 갱신
        else if (!complete[v])
            p = min(p, order[v]);       // 방문은 했는데 scc 탐색이 완료되지 않았을 경우 해당 정점의 방문 순서 이용하여 최솟값 갱신
    }

    if (p == order[cur])
    {
        ++K;
        while (!s.empty())
        {
            register int v = s.top();
            s.pop();

            complete[v] = true;
            
            if (p == order[v])
                break;
        }
    }

    return p;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    register int T, V, E, a, b;
    cin >> T;

    for (register int test_case = 1; test_case <= T; ++test_case)
    {
        cin >> V >> E;
        while (E--)
        {
            cin >> a >> b;
            graph[a].push_back(b);
        }

        for (register int v = 1; v <= V; ++v)
            if (!complete[v])
                findSCC(v);

        cout << '#' << test_case << ' ' << K << '\n';

        cnt = K = 0;
        memset(order, 0, sizeof(order));
        memset(complete, false, sizeof(complete));
        for (register int v = 1; v <= V; ++v)
            graph[v].clear();
    }

    return 0;
}
