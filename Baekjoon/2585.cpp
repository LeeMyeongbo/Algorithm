#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <cmath>
using namespace std;

pair<int, int> graph[1002];

bool bfs(int n, int k, int fuel)      // 연료통 크기가 fuel일 때 k번 이하로 내려서 갈 수 있는지 판단
{
    queue<tuple<int, int, int, int>> q;     // (내린 횟수, 남은 연료, 현재 x, 현재 y)
    bool visited[1002] = {false, };

    q.push({0, fuel, 0, 0});
    visited[0] = true;

    while (!q.empty()) {
        int cnt, f, x, y;
        tie(cnt, f, x, y) = q.front();
        q.pop();

        if (x == 10000 && y == 10000)
            return true;
        
        for (int i = 1; i <= n + 1; i++) {
            if (!visited[i]) {
                register int new_x = graph[i].first;
                register int new_y = graph[i].second;
                register int needed_f = (int)ceil(sqrt((x - new_x) * (x - new_x) + (y - new_y) * (y - new_y)) / 10);

                // 현재 남은 연료 양이 필요한 연료 양 이상일 경우 바로 감
                if (f >= needed_f) {
                    q.push({cnt, f - needed_f, new_x, new_y});
                    visited[i] = true;
                }
                // 혹은 연료통 크기가 필요한 연료 양 이상이면서 내려도 k번 이하일 경우 내려서 충전
                else if (fuel >= needed_f && cnt + 1 <= k) {
                    q.push({cnt + 1, fuel - needed_f, new_x, new_y});
                    visited[i] = true;
                }
            }
        }
    }

    return false;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    register int n, k, ans = 0;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> graph[i].first >> graph[i].second;
    graph[n + 1] = {10000, 10000};

    register int left = 0, right = 20000;
    while (left <= right) {
        register int mid = (left + right) / 2;
        if (bfs(n, k, mid)) {       // 연료통 크기가 mid일 때 k번 이하로 내려서 목적지로 갈 수 있다면
            ans = mid;
            right = mid - 1;        // 연료통 크기를 더 작게 잡아봄
        }
        else
            left = mid + 1;         // 그렇지 않다면 더 크게
    }

    cout << ans;
    return 0;
}