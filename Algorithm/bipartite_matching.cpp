#include <iostream>
#include <vector>
using namespace std;

int N, M, a, b, connect[10001];
vector<int> graph[10001];
bool complete[10001];

bool dfs(int cur)                   // 매칭 성공 시 true, 실패 시 false
{
    for (int i : graph[cur]) {
        if (complete[i])            // 이미 완료된 정점은 skip
            continue;
        complete[i] = true;

        if (!connect[i] || dfs(connect[i])) {
            connect[i] = cur;
            return true;
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N >> M;
    while(M--) {
        cin >> a >> b;
        graph[a].push_back(b);
    }

    int cnt = 0;
    for (int i = 1; i <= N; i++) {                  // i번 정점 넣을 때 매칭 가능한 만큼 최대한 매칭시킴
        fill(complete, complete + N + 1, false);
        if (dfs(i))
            cnt++;
    }

    for (int i = 1; i <= N; i++) {
        if (connect[i])
            cout << connect[i] << " -> " << i << '\n';
    }

    return 0;
}
