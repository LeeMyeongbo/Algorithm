#include <string>
#include <cstring>
#include <cmath>
#include <unordered_map>
#include <vector>
using namespace std;

int cnt, depth[50001], parent[50001][13], ans;
bool visited[50001];
vector<int> graph[50001];
unordered_map<string, int> species;
#define MAXL	(11)	

void init(char mRootSpecies[MAXL])
{
    for (int i = 0; i < 50001; i++)
        graph[i].clear();
    species.clear();

    cnt = 0;
    memset(depth, 0, sizeof(depth));
    memset(parent, 0, sizeof(parent));

    string mroot(mRootSpecies);
    species[mroot] = ++cnt;
    depth[cnt] = 1;
}

void add(char mSpecies[MAXL], char mParentSpecies[MAXL])
{
    string mchild(mSpecies), mparent(mParentSpecies);
    species[mchild] = ++cnt;

    int par = species[mparent], chi = species[mchild];
    graph[par].emplace_back(chi);
    graph[chi].emplace_back(par);

    depth[chi] = depth[par] + 1;
    parent[chi][0] = par;

    int max_anc = (int)ceil(log2(depth[chi]));
    for (int i = 1; i < max_anc; i++)
        parent[chi][i] = parent[parent[chi][i - 1]][i - 1];
}

int lca(int u, int v)
{
    if (depth[u] < depth[v])
        swap(u, v);
    
    int diff = depth[u] - depth[v];
    for (int i = 0; diff; i++)
    {
        if (diff & 1)
            u = parent[u][i];
        diff >>= 1;
    }

    if (u == v)
        return u;
    
    int max_anc = (int)ceil(log2(depth[u]));
    for (int i = max_anc; i >= 0; i--)
    {
        if (parent[u][i] != parent[v][i])
        {
            u = parent[u][i];
            v = parent[v][i];
        }
    }

    return parent[u][0];
}

int getDistance(char mSpecies1[MAXL], char mSpecies2[MAXL])
{
    string ms1(mSpecies1), ms2(mSpecies2);
    int s1 = species[ms1], s2 = species[ms2];

    int anc = lca(s1, s2);
	return depth[s1] - depth[anc] + depth[s2] - depth[anc];
}

void dfs(int depth, int d, int cur)
{
    if (d == depth)
    {
        ans++;
        return;
    }
    for (int& i : graph[cur])
    {
        if (!visited[i])
        {
            visited[i] = true;
            dfs(depth, d + 1, i);
            visited[i] = false;
        }
    }
}

int getCount(char mSpecies[MAXL], int mDistance)
{
    string sp(mSpecies);
    int v = species[sp];

    visited[v] = true;
    dfs(mDistance, 0, v);
    visited[v] = false;

    int a = ans;
    ans = 0;

	return a;
}
