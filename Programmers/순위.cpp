#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

int getNum(int start, vector<int> graph[])
{
    queue<int> q;
    bool visited[101] = { false, };
    int cnt = 0;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (int v : graph[cur]) {
            if (!visited[v]) {
                q.push(v);
                visited[v] = true;
                cnt++;
            }
        }
    }

    return cnt;
}

int solution(int n, vector<vector<int>> results) {
    int answer = 0;
    vector<int> graph[101], inv_graph[101];

    for (vector<int> v : results) {
        graph[v[0]].push_back(v[1]);
        inv_graph[v[1]].push_back(v[0]);
    }
    for (int i = 1; i <= n; i++) {
        if (getNum(i, graph) + getNum(i, inv_graph) == n - 1)
            answer++;
    }
    return answer;
}
