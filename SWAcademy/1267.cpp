#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int V, E, from, to;
    queue<int> q;

    for (int test_case = 1; test_case <= 10; ++test_case)
    {
        vector<int> graph[1001], ans;
        int indegree[1001] = {0, };         // indegree[v] : 정점 v로 향하는 진입간선 개수

        cin >> V >> E;
        for (int e = 0; e < E; e++) 
        {
            cin >> from >> to;
            graph[from].push_back(to);
            indegree[to]++;
        }

        for (int v = 1; v <= V; v++)
            if (!indegree[v])
                q.push(v);
        
        while (!q.empty())                  // 위상정렬 진행
        {
            int cur = q.front();
            q.pop();

            ans.push_back(cur);
            for (int i : graph[cur]) 
            {
                indegree[i]--;
                if (!indegree[i])
                    q.push(i);
            }
        }

        cout << '#' << test_case << ' ';
        for (int i : ans)
            cout << i << ' ';
        cout << "\n";
    }
    return 0;
}
