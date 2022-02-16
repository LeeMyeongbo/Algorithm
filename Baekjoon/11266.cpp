#include <iostream>
#include <vector>
using namespace std;

int V, E, A, B, order, visited[10001];
vector<int> graph[10001], ans;
bool isCutvertex[10001];

int DFS(bool root, int cur)
{
    visited[cur] = ++order;
    int fastest = order;                    // 연결된 정점(현재 정점 포함) 중 가장 순서가 빠른 거
    int child = 0;                          // 자식 수
    
    for (int v : graph[cur]) {
        if (!visited[v]) {
            int low = DFS(false, v);        // 현재 정점에서 갈 수 있는, 방문 순서가 나중인 점들 중에서 가장 빠른 순서인 low 리턴
            child++;

            if (!root && low >= visited[cur])
                isCutvertex[cur] = true;    // 루트가 아니면서 현재 정점의 방문 순서가 low 이상일 경우 단절점!
            fastest = min(fastest, low);    // fastest 갱신
        }
        else
            fastest = min(fastest, visited[v]);
    }
    if (root && child >= 2)                 // 루트면서 자식 트리가 둘 이상이면 단절점!
        isCutvertex[cur] = true;

    return fastest;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> V >> E;
    while (E--) {
        cin >> A >> B;
        graph[A].push_back(B);
        graph[B].push_back(A);
    }

    for (int i = 1; i <= V; i++)
        if (!visited[i])
            DFS(true, i);
    
    for (int i = 1; i <= V; i++) 
        if (isCutvertex[i])
            ans.push_back(i);
    
    cout << ans.size() << "\n";
    for (int a : ans)
        cout << a << ' ';

    return 0;
}
