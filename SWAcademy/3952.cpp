#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

queue<int> q;
vector<int> graph[50001];
int indegree[50001];

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    register int T, N, M, a, b;
    cin >> T;

    for (register int test_case = 1; test_case <= T; ++test_case)
    {
        cin >> N >> M;
        while (M--)
        {
            cin >> a >> b;
            graph[a].emplace_back(b);
            ++indegree[b];
        }

        for (register int v = 1; v <= N; ++v)
            if (!indegree[v])
                q.emplace(v);

        cout << '#' << test_case << ' ';

        while (!q.empty())
        {
            register int cur = q.front();
            q.pop();

            cout << cur << ' ';

            for (int& to : graph[cur])
            {
                --indegree[to];
                if (!indegree[to])
                    q.emplace(to);
            }
        }
        cout << '\n';

        memset(indegree, 0, sizeof(indegree));
        for (register int v = 1; v <= N; ++v)
            graph[v].clear();
    }

    return 0;
}
