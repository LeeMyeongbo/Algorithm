#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

vector<int> tree[10001];
int T, V, E, v1, v2, parent, child, anc[10001][14], depth[10001], Anc;

void bfs()                              // bfs 돌며 노드 별 깊이 저장
{
    queue<pair<int, int>> q;
    depth[1] = 1;
    q.push({1, 1});

    while (!q.empty())
    {
        int cur = q.front().first;
        int d = q.front().second;
        q.pop();

        for (int& node : tree[cur])
            if (!depth[node])
            {
                depth[node] = d + 1;
                q.push({node, d + 1});
            }
    }
}

void setAnc()                           // 정점 v의 2^n 번째 조상은 v의 2^(n-1)번째 조상의 2^(n-1)번째 조상과 같다
{
    for (int i = 1; i < Anc; i++)
        for (int v = 1; v <= V; v++)
            anc[v][i] = anc[anc[v][i - 1]][i - 1];
}

int lca()
{
    if (depth[v1] < depth[v2]) swap(v1, v2);    // 무조건 v1의 깊이를 더 깊게

    int diff = depth[v1] - depth[v2];
    for (int d = 0; diff; d++)                  // v1과 v2의 깊이가 같아질 때까지 v1을 올려줌
    {
        if (diff & 1)
            v1 = anc[v1][d];
        diff = diff >> 1;
    }

    if (v1 == v2)                               // v1과 v2가 같게 되면 v2가 곧 lca였음을 의미
        return v2;

    for (int a = Anc - 1; a >= 0; a--)          // v1과 v2를 동시에 올려주면서 lca 탐색
        if (anc[v1][a] != anc[v2][a])
        {
            v1 = anc[v1][a];
            v2 = anc[v2][a];
        }
    
    return anc[v1][0];
}

int subtree(int root)
{
    int cnt = 0;
    queue<int> q;
    q.push(root);

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();

        cnt++;
        for (int& node : tree[cur])
            if (anc[cur][0] != node)        // 부모 노드가 아니면 큐 삽입
                q.push(node);
    }

    return cnt;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) 
    {
        cin >> V >> E >> v1 >> v2;
        Anc = (int)log2(V) + 1;
        for (int e = 0; e < E; e++) {
            cin >> parent >> child;
            tree[parent].push_back(child);
            tree[child].push_back(parent);
            anc[child][0] = parent;
        }

        bfs();
        setAnc();
        int l = lca();
        cout << '#' << test_case << ' ' << l << ' ' << subtree(l) << '\n';

        for (int i = 1; i <= V; i++)
        {
            tree[i].clear();
            fill(anc[i], anc[i] + 14, 0);
        }
        fill(depth, depth + 10001, 0);
    }
    return 0;
}