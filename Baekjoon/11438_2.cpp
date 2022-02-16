#include <iostream>
#include <vector>
#include <cmath>
#define MAX 131072                      // 2^17
using namespace std;

int N, M, v1, v2, n, depth[100001], parent[17][100001];    // parent[i][v] : v의 2^i번째 부모 정점
vector<int> tree[100001];

void init(int d, int cur, int par)
{
    depth[cur] = d;
    parent[0][cur] = par;

    for (int v : tree[cur])
        if (!depth[v])
            init(d + 1, v, cur);
}

void setAncestor()                      // v의 2^k번째 부모 = v의 2^(k-1)번째 부모의 2^(k-1)번째 부모
{
    for (int k = 1; k < n; k++)
        for (int v = 1; v <= N; v++)
            parent[k][v] = parent[k - 1][parent[k - 1][v]];
}

int LCA(int a, int b)
{
    if (depth[a] < depth[b])            // a의 깊이가 더 깊도록 설정
        swap(a, b);

    int gap = depth[a] - depth[b];
    for (int i = 0; gap; i++) {         // a와 b의 깊이가 같아질 때까지 a를 위로 올림
        if (gap % 2)
            a = parent[i][a];
        gap /= 2;
    }

    if (a == b)                         // a와 b가 같아졌다면 a가 최소 공통 조상
        return a;

    for (int i = n - 1; i >= 0; i--) {  // 2^(n-1)번째 조상부터 살펴보며 서로 조상이 같지 않은 시점마다 해당 조상 위치로 올림
        if (parent[i][a] != parent[i][b]) {
            a = parent[i][a];
            b = parent[i][b];
        }
    }

    return parent[0][a];                // a의 부모 정점 = 최소 공통 조상
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N;
    n = (int)ceil(log2(N));
    for (int i = 0; i < N - 1; i++) {
        cin >> v1 >> v2;
        tree[v1].push_back(v2);
        tree[v2].push_back(v1);
    }

    init(1, 1, 0);                      // 각 정점의 깊이 정보 저장
    setAncestor();                      // 각 정점의 조상들 정보 저장

    cin >> M;
    while (M--) {
        cin >> v1 >> v2;
        cout << LCA(v1, v2) << "\n";
    }

    return 0;
}
