#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int solution(int n, vector<vector<int>> edge)
{
    int answer = 0, min_path[20001];
    vector<int> graph[20001];
    queue<pair<int, int>> q;            // (���� ��ġ, �ִ� �Ÿ�)�� ����

    fill(min_path, min_path + 20001, -1);
    q.push({ 1, 0 });
    min_path[1] = 0;

    for (vector<int>& e : edge) {       // ���� ���� ���� �׷��� ����
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }

    while (!q.empty()) {
        int cur = q.front().first;
        int dist = q.front().second;
        q.pop();

        for (int v : graph[cur]) {
            if (min_path[v] == -1) {
                q.push({ v, dist + 1 });
                min_path[v] = dist + 1;
            }
        }
    }
    sort(min_path, min_path + n + 1);

    for (int i = n; i > 1; i--) {
        if (min_path[i] == min_path[n])
            answer++;
        else
            break;
    }

    return answer;
}