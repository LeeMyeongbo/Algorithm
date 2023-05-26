#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int depth[100001], anc[100001][17];
queue<int> q;
vector<int> tree[100001];

int getlca(int v1, int v2)
{
    if (depth[v1] < depth[v2])
        swap(v1, v2);

    register int diff = depth[v1] - depth[v2];
    for (register int i = 0; diff; ++i)
    {
        if (diff & 1)
            v1 = anc[v1][i];
        diff >>= 1;
    }

    if (v1 == v2)
        return v1;

    for (register int i = 16; i >= 0; --i)
        if (anc[v1][i] != anc[v2][i])
        {
            v1 = anc[v1][i];
            v2 = anc[v2][i];
        }
    
    return anc[v1][0];
}

long long solve()
{
    register int pre = 1;
    register long long ans = 0;

    q.push(1);
    while (!q.empty())
    {
        register int cur = q.front();
        q.pop();

        register int lca = getlca(cur, pre);
        ans += depth[cur] + depth[pre] - (depth[lca] << 1);

        for (int& i : tree[cur])
            q.push(i);

        pre = cur;
    }

    return ans;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    register int T, N, p;

    cin >> T;
    for (register int test_case = 1; test_case <= T; ++test_case)
    {
        cin >> N;
        for (register int v = 2; v <= N; ++v)
        {
            cin >> p;
            tree[p].push_back(v);
            depth[v] = depth[p] + 1;
            anc[v][0] = p;
        }

        for (register int p = 1; p < 17; ++p)
            for (register int v = 1; v <= N; ++v)
                anc[v][p] = anc[anc[v][p - 1]][p - 1];

        cout << '#' << test_case << ' ' << solve() << '\n';
        
        for (register int v = 1; v <= N; ++v)
            tree[v].clear();
        memset(depth, 0, sizeof(depth));
        memset(anc, 0, sizeof(anc));
    }

    return 0;
}
