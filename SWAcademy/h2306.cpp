#include <vector>
#include <queue>
#include <cstring>
using namespace std;

struct Node {
    int id, depth, dist, umbrella, distfromRoot, sumofUmbrella;     // sumofUmbrella : 깊이가 2이하인 노드에 대해 자신 + 자식 노드들의 우산 합
    int anc1, anc2;                                                 // 깊이가 3이상인 노드에 대해서 깊이가 1인 조상, 깊이가 2인 조상을 의미
} storage[10000];
vector<pair<int, int>> tree[10000];                                 // tree : (연결된 노드와의 거리, 연결된 노드)로 저장
int n, Anc[10000][7], visited[10000];

int lca(int u, int v)
{
    if (storage[u].depth < storage[v].depth)
        swap(u, v);

    int diff = storage[u].depth - storage[v].depth;
    for (int i = 0; diff; i++)
    {
        if (diff & 1)
            u = Anc[u][i];
        diff >>= 1;
    }

    if (u == v)
        return u;

    for (int i = 6; i >= 0; i--)
    {
        if (Anc[u][i] != Anc[v][i])
        {
            u = Anc[u][i];
            v = Anc[v][i];
        }
    }

    return Anc[u][0];
}

void moveUmbrella(int from, int to, int num)
{
    storage[from].umbrella -= num;
    storage[to].umbrella += num;

    if (storage[from].depth == 1)
        storage[from].sumofUmbrella -= num;
    else if (storage[from].depth == 2)
        storage[from].sumofUmbrella -= num, storage[Anc[from][0]].sumofUmbrella -= num;
    else if (storage[from].depth > 2)
    {
        int anc1 = storage[from].anc1, anc2 = storage[from].anc2;
        storage[anc1].sumofUmbrella -= num, storage[anc2].sumofUmbrella -= num;
    }

    if (storage[to].depth == 1)
        storage[to].sumofUmbrella += num;
    else if (storage[to].depth == 2)
        storage[to].sumofUmbrella += num, storage[Anc[to][0]].sumofUmbrella += num;
    else if (storage[to].depth > 2)
    {
        int anc1 = storage[to].anc1, anc2 = storage[to].anc2;
        storage[anc1].sumofUmbrella += num, storage[anc2].sumofUmbrella += num;
    }
}

void init(int N, int mParent[], int mDistance[], int mQuantity[])   
{
    memset(storage, 0, sizeof(storage));
    memset(Anc, 0, sizeof(Anc));
    for (int i = 0; i < n; i++)
        tree[i].clear();

    n = N;
    storage[0] = { 0, 0, 0, mQuantity[0], 0, mQuantity[0], 0, 0 };
    for (int i = 1; i < N; i++)
    {
        tree[i].push_back({ mDistance[i], mParent[i] });
        tree[mParent[i]].push_back({ mDistance[i], i });
        storage[0].sumofUmbrella += mQuantity[i];

        Node& parent = storage[mParent[i]];
        int anc1 = 0, anc2 = 0;
        if (parent.depth < 3)
        {
            anc2 = parent.id, anc1 = parent.anc2;                   // 부모 깊이가 2 이하일 땐 anc2가 부모, anc1이 부모의 부모!
            if (parent.depth >= 1)
                storage[anc2].sumofUmbrella += mQuantity[i];
            if (parent.depth == 2)
                storage[anc1].sumofUmbrella += mQuantity[i];
        }
        else
        {
            anc2 = parent.anc2, anc1 = parent.anc1;                 // 부모 깊이가 3 이상이면 anc1, 2는 부모의 그것과 동일
            storage[anc2].sumofUmbrella += mQuantity[i];
            storage[anc1].sumofUmbrella += mQuantity[i];
        }

        storage[i] = { i, parent.depth + 1, mDistance[i], mQuantity[i], parent.distfromRoot + mDistance[i], mQuantity[i], anc1, anc2};
        Anc[i][0] = mParent[i];
    }

    for (int a = 1; a < 7; a++)
        for (int i = 1; i < N; i++)
            Anc[i][a] = Anc[Anc[i][a - 1]][a - 1];
}

int carry(int mFrom, int mTo, int mQuantity)
{
    int middle = lca(mFrom, mTo);                                   // 항상 루트에서부터 lca까지의 거리를 2번 빼줘야 함!
    int d = storage[mFrom].distfromRoot + storage[mTo].distfromRoot - 2 * storage[middle].distfromRoot;

    moveUmbrella(mFrom, mTo, mQuantity);
    return d * mQuantity;
}

int gather(int mID, int mQuantity)
{
    int ans = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;     // (거리, 노드 id)로 저장
    memset(visited, -1, sizeof(visited));
    
    pq.push({ 0, mID });
    visited[mID] = 0;

    while (!pq.empty())
    {
        int dist = pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        if (cur != mID)
        {
            int movingUmbrella = min(mQuantity, storage[cur].umbrella);
            mQuantity -= storage[cur].umbrella;
            moveUmbrella(cur, mID, movingUmbrella);
            ans += movingUmbrella * dist;
            if (mQuantity <= 0)
                return ans;
        }

        for (auto& p : tree[cur])
        {
            if (visited[p.second] == -1 || visited[p.second] > dist + p.first)
            {
                visited[p.second] = dist + p.first;
                pq.push({ visited[p.second], p.second });
            }
        }
    }
    return 0;
}

int sum(int mID)
{
    return storage[mID].sumofUmbrella;
}
