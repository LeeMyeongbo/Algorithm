#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<int> graph[200001];             // graph[i] = j : i -> j
int indegree[200001], r[200001];       // indegree[n] : 정점 n의 진입 차수, r[i] : i번 index의 도착 정점
bool visited[200001];

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    int N, M, L, k, x;
    cin >> N >> M;

    for (register int i = 1; i <= M; i++) {
        cin >> k;
        for (register int j = 0; j < k; j++) {
            cin >> x;
            graph[x].push_back(i);      // 각 x1, x2,... 마다 i번 index로 가는 걸로 그래프 형성
        }
        indegree[i] = k;
        cin >> r[i];
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
        int cur = q.front();
        q.pop();
        
        ans.push_back(cur);
        for (int& i : graph[cur]) {

            // i로 향하는 진입 차수를 1 줄이고
            if (--indegree[i] == 0) {

                // 그 i의 진입 차수가 0이 될 때 해당 i번 index의 도착 정점을 방문한 적 없다면 방문 체크 + 큐 삽입
                if (!visited[r[i]]) {
                    visited[r[i]] = true;
                    q.push(r[i]);
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