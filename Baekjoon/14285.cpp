#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

int n, m, a, b, c, s, t, weight_sum, dij[2][5001];      // dij[0][i] : 간선 하나 삭제하지 않은 상태에서의 합, dij[1][i] : 하나 삭제한 상태에서의 합
vector<pair<int, int>> graph[5001];                     // (연결된 정점, 가중치)로 저장

int solve()
{
    priority_queue<pair<pair<int, int>, bool>> pq;
    memset(dij, -1, sizeof(dij));
    dij[0][s] = dij[1][s] = 0;
    pq.push({ {dij[0][s], s}, false });
    
    while (!pq.empty()) {
        int sum = -pq.top().first.first;
        int cur = pq.top().first.second;
        bool deleted = pq.top().second;
        pq.pop();

        for (auto& e : graph[cur]) {
            if (!deleted) {                                                         // 간선이 아직 삭제되지 않았을 경우
                if (dij[0][e.first] == -1 || dij[0][e.first] > sum + e.second) {    // 간선 삭제하지 않고 힙에 저장
                    dij[0][e.first] = sum + e.second;
                    pq.push({ {-dij[0][e.first], e.first}, false });
                }
                if (dij[1][e.first] == -1 || dij[1][e.first] > sum) {               // 간선 삭제하고 힙에 저장
                    dij[1][e.first] = sum;
                    pq.push({ {-sum, e.first}, true });
                }
            }
            else {                                                                  // 이미 삭제되었을 경우
                if (dij[1][e.first] == -1 || dij[1][e.first] > sum + e.second) {    // 그대로 삭제하지 않으면서 진행
                    dij[1][e.first] = sum + e.second;
                    pq.push({ {-dij[1][e.first], e.first}, true });
                }
            }
        }
    }

    return weight_sum - dij[1][t];
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m;
    while (m--) {
        cin >> a >> b >> c;
        graph[a].push_back({ b, c });
        graph[b].push_back({ a, c });
        weight_sum += c;
    }
    cin >> s >> t;

    cout << solve();
    return 0;
}
