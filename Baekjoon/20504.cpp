#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int N, M, u, v, T, t[200000], order, seq[200001], scc_num, sccid[200001], scc_indegree[200000], starting_scc;
bool complete[200001], visited_scc[200000];
vector<int> graph[200001];
stack<int> s;

int dfs(int cur)
{
    seq[cur] = ++order;
    int par = order;
    s.push(cur);

    for (int& i : graph[cur]) {
        if (!seq[i])
            par = min(par, dfs(i));
        else if (!complete[i])
            par = min(par, seq[i]);
    }
    if (par == seq[cur]) {
        scc_num++;
        while (!s.empty()) {
            int v = s.top();
            s.pop();

            complete[v] = true;
            sccid[v] = scc_num;
            if (v == cur)
                break;
        }
    }
    return par;
}

int find()
{
    int Found = 0;
    for (int i = 1; i <= N; i++)
        for (int& j : graph[i])
            if (sccid[i] != sccid[j])
                scc_indegree[sccid[j]]++;

    for (int i = 1; i <= scc_num; i++)
        if (!scc_indegree[i])
            starting_scc++;				// 진입차수가 0인 scc 개수 체크 (최소한 진입간선이 없는 scc에서부터 시작해야 하기 때문)

    for (int i = 0; i < T; i++) {		// 해당 t[i]가 속한 scc의 진입차수가 0이고 방문한 적 없는 scc라면 방문 체크 + 개수 증가
        if (!scc_indegree[sccid[t[i]]] && !visited_scc[sccid[t[i]]]) {
            visited_scc[sccid[t[i]]] = true;
            Found++;
        }
    }
    if (Found < starting_scc)	// 개수 헤아려서 진입차수가 0인 scc의 개수보다 작다면
        return -1;				// 미처 헤아리지 못한, 또 다른 진입차수가 0인 scc의 함수들은 호출될 수 없다는 의미
    else
        return Found;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N >> M;
    while (M--) {
        cin >> u >> v;
        graph[u].push_back(v);
    }
    cin >> T;
    for (int i = 0; i < T; i++)
        cin >> t[i];

    for (int i = 1; i <= N; i++)
        if (!complete[i])
            dfs(i);

    cout << find();
    return 0;
}
