#include <iostream>
#include <vector>
#include <cmath>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, v1, v2, n1, n2, parent[50001][16], depth[50001], n;		// parent[i][k] : i의 2^k번째 부모
vector<int> tree[50001];

void dfs(int d, int cur, int par)				// 각 정점마다 바로 위(2^0번째) 부모 및 깊이 저장
{
    parent[cur][0] = par;
    depth[cur] = d;

    for (int& i : tree[cur]) {
        if (!depth[i])
            dfs(d + 1, i, cur);
    }
}

void set_Parent()
{
    for (int j = 1; j < n; j++)					// 2^1번째 조상, 2^2번째 조상 순으로 
        for (int i = 1; i <= N; i++)			// 1번부터 N번까지 반복
            parent[i][j] = parent[parent[i][j - 1]][j - 1];
}

int LCA()
{
    if (depth[n1] < depth[n2])					// n1의 깊이가 더 깊도록 설정
        swap(n1, n2);

    int diff = depth[n1] - depth[n2];
    for (int i = 0; diff; i++) {				// n1의 깊이가 n2랑 같을 때까지 위로 올려서 맞춤
        if (diff % 2)
            n1 = parent[n1][i];
        diff /= 2;
    }

    if (n1 == n2)
        return n1;
    for (int i = n - 1; i >= 0; i--) {			// 최상단 노드로부터 조상이 같아지기 전까지 2^i씩 이동
        if (parent[n1][i] != parent[n2][i]) {
            n1 = parent[n1][i];
            n2 = parent[n2][i];
        }
    }
    return parent[n1][0];
}

int main()
{
    FAST;
    cin >> N;
    n = (int)log2(N) + 1;
    for (int i = 0; i < N - 1; i++) {
        cin >> v1 >> v2;
        tree[v1].push_back(v2);
        tree[v2].push_back(v1);
    }
    dfs(1, 1, 0);
    set_Parent();

    cin >> M;
    while (M--) {
        cin >> n1 >> n2;
        cout << LCA() << "\n";
    }
    return 0;
}
