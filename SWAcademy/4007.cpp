#include <iostream>
#include <vector>
#include <queue>
#define MAX 500000000
using namespace std;

int T, N, M, X, s, e, t;
vector<pair<int, int>> graph[50001], inv_graph[50001];      // (도착 정점, 소요 시간)으로 저장

int solve() 
{
    priority_queue<pair<int, int>> pq;                      // (소요 시간 합, 현재 정점)으로 저장
    int forward[50001], backward[50001], ans = 0;           // forward[i] : i→X 소요 시간, backward[i] : X→i 소요 시간
    fill(forward, forward + N + 1, MAX);
    fill(backward, backward + N + 1, MAX);
    
    // i→X 소요 시간 구할 때 inv_graph 이용
    pq.push({ 0, X });
    forward[X] = 0;
    while (!pq.empty()) {
        int time = -pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        for (auto& e : inv_graph[cur]) {
            if (forward[e.first] > time + e.second) {
                forward[e.first] = time + e.second;
                pq.push({ -forward[e.first], e.first });
            }
        }
    }

    // X→i 소요 시간 구할 때 graph 이용
    pq.push({ 0, X });
    backward[X] = 0;
    while (!pq.empty()) {
        int time = -pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        for (auto& e : graph[cur]) {
            if (backward[e.first] > time + e.second) {
                backward[e.first] = time + e.second;
                pq.push({ -backward[e.first], e.first });
            }
        }
    }

    for (int i = 1; i <= N; i++)
        if (forward[i] + backward[i] < MAX)
            ans = max(ans, forward[i] + backward[i]);
    
    return ans;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N >> M >> X;
        while (M--) {
            cin >> s >> e >> t;
            graph[s].push_back({ e, t });
            inv_graph[e].push_back({ s, t });
        }

        cout << '#' << test_case << ' ' << solve() << "\n";
        for (int i = 1; i <= N; i++) {
            graph[i].clear();
            inv_graph[i].clear();
        }
    }
    return 0;
}
