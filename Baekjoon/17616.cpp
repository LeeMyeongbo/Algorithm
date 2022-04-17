#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> graph[100001], inv_graph[100001];
bool visited[100001];

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    register int N, M, X, A, B, behind = 0, front = 0;
    cin >> N >> M >> X;

    while (M--) {
        cin >> A >> B;
        graph[A].push_back(B);      // graph[A] = B : A 뒤에 B
        inv_graph[B].push_back(A);  // inv_graph[B] = A : B 앞에 A
    }

    queue<int> q;

    visited[X] = true;
    q.push(X);
    while (!q.empty()) {            // 먼저 X 뒤에 확정적으로 몇 명 있는지 구함
        int cur = q.front();
        q.pop();

        for (int v : graph[cur]) {
            if (!visited[v]) {
                visited[v] = true;
                behind++;
                q.push(v);
            }
        }
    }

    q.push(X);
    while (!q.empty()) {            // 그리고 X 앞에 확정적으로 몇 명 있는지도
        int cur = q.front();
        q.pop();

        for (int v : inv_graph[cur]) {
            if (!visited[v]) {
                visited[v] = true;
                front++;
                q.push(v);
            }
        }
    }

    cout << front + 1 << ' ' << N - behind;
    return 0;
}