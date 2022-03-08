#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int T, N, M, u, v, indegree[100001], inv_indegree[100001], order[100001], inv_order[100001];
vector<int> graph[100001], inv_graph[100001], undir_graph[100001], seq[100001], inv_seq[100001];

bool solve()
{
    queue<int> q, inv_q, chk;
    int v = 0;
    bool visited[100001] = { false, };
    chk.push(1);
    visited[1] = true;

    while (!chk.empty()) {
        int cur = chk.front();
        chk.pop();

        v++;
        if (!indegree[cur])
            q.push(cur);
        if (!inv_indegree[cur])
            inv_q.push(cur);

        for (int i : undir_graph[cur])
            if (!visited[i]) {
                visited[i] = true;
                chk.push(i);
            }
    }
    if (v < N)
        return false;

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        seq[order[cur]].emplace_back(cur);
        for (int i : graph[cur]) {
            indegree[i]--;
            order[i] = max(order[i], order[cur] + 1);
            if (!indegree[i])
                q.push(i);
        }
    }

    while (!inv_q.empty()) {
        int cur = inv_q.front();
        inv_q.pop();

        inv_seq[inv_order[cur]].emplace_back(cur);
        for (int i : inv_graph[cur]) {
            inv_indegree[i]--;
            inv_order[i] = max(inv_order[i], inv_order[cur] + 1);
            if (!inv_indegree[i])
                inv_q.push(i);
        }
    }

    return true;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N >> M;
        while (M--) {
            cin >> u >> v;
            graph[u].emplace_back(v);
            undir_graph[u].emplace_back(v);
            indegree[v]++;

            inv_graph[v].emplace_back(u);
            undir_graph[v].emplace_back(u);
            inv_indegree[u]++;
        }

        int ans[100001] = { 0, }, num = 0;
        if (solve()) {
            for (int i = 0; i < N; i++) {
                if (seq[i].size() == 1) {
                    ans[seq[i][0]]++;
                    if (ans[seq[i][0]] == 2)
                        num++;
                }
                if (inv_seq[i].size() == 1) {
                    ans[inv_seq[i][0]]++;
                    if (ans[inv_seq[i][0]] == 2)
                        num++;
                }
            }
        }

        cout << '#' << test_case << ' ' << num << "\n";
        for (int i = 1; i <= N; i++)
            if (ans[i] == 2)
                cout << i << ' ';
        cout << "\n";

        fill(indegree, indegree + N + 1, 0);
        fill(inv_indegree, inv_indegree + N + 1, 0);
        fill(order, order + N + 1, 0);
        fill(inv_order, inv_order + N + 1, 0);
        for (int i = 0; i <= N; i++) {
            undir_graph[i].clear();
            graph[i].clear();
            inv_graph[i].clear();
            seq[i].clear();
            inv_seq[i].clear();
        }
    }
    return 0;
}
