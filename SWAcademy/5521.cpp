#include <iostream>
#include <vector>
#include <queue>
#define MAX 1<<30
using namespace std;

int T, N, M, a, b;
vector<int> graph[501];

int solve()
{
    priority_queue<pair<int, int>> pq;
    int visited[501], ans = 0;

    fill(visited, visited + N + 1, MAX);
    pq.push({ 0, 1 });
    visited[1] = 0;

    while (!pq.empty()) {
        int move = -pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        if (move >= 2)
            continue;

        for (int i : graph[cur]) {
            if (visited[i] > move + 1) {
                visited[i] = move + 1;
                pq.push({ -visited[i], i });
                ans++;
            }
        }
    }

    return ans;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N >> M;
        while (M--) {
            cin >> a >> b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        cout << '#' << test_case << ' ' << solve() << "\n";

        for (int i = 1; i <= N; i++)
            graph[i].clear();
    }
    return 0;
}
