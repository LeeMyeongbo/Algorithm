#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

vector<pair<int, set<int>>> graph[200001]; // graph[r] = (제거된 간선 수, {x1, x2, x3...})
bool visited[200001];
set<int> connect[200001];                  // connect[i] = j : i는 j로 이어짐을 의미

int main()
{
    int N, M, L, k, x;
    cin >> N >> M;

    while (M--) {
        cin >> k;
        set<int> tmp;
        vector<int> tmp2;
        for (register int i = 0; i < k; i++) {
            cin >> x;
            tmp.insert(x);
            tmp2.push_back(x);
        }
        cin >> x;
        graph[x].push_back({0, tmp});

        for (int& i : tmp2)
            connect[i].insert(x);
    }

    vector<int> ans;
    queue<int> q;
    cin >> L;

    while (L--) {
        cin >> x;
        q.push(x);
        visited[x] = true;
    }

    while (!q.empty()) {
        int cur = q.front();    // 현재 정점
        q.pop();
        ans.push_back(cur);

        // 현재 정점에서 갈 수 있는 정점들 살피며 현재 정점으로부터 나가는 진출 간선 제거
        for (auto it = connect[cur].begin(); it != connect[cur].end(); it++) {
            for (auto& g : graph[*it]) {
                g.first += g.second.count(cur);

                // 만약 지운 간선들 수가 필요한 물약의 수와 같게 된다면 큐 삽입 + 방문 체크
                if (g.first == g.second.size() && !visited[*it]) {
                    q.push(*it);
                    visited[*it] = true;
                }
            }
        }
    }

    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (int& i : ans)
        cout << i << ' ';

    return 0;
}