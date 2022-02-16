#include <iostream>
#include <queue>
using namespace std;

int len, start, from, to;
bool contact[101][101];
int visited[101];
queue<pair<int, int>> q;

int solve()
{
    int Ans = 0;
    visited[start] = 1;
    q.push({ start, visited[start] });

    while (!q.empty()) {
        int cur = q.front().first;
        int seq = q.front().second;
        q.pop();

        for (int i = 1; i <= 100; i++) {
            if (contact[cur][i] && !visited[i]) {
                visited[i] = seq + 1;
                q.push({ i, visited[i] });
            }
        }
    }

    int Max = 0;
    for (int i = 100; i > 0; i--) {
        if (visited[i] > Max) {
            Max = visited[i];
            Ans = i;
        }
    }

    return Ans;
}

int main(int argc, char** argv)
{   
    for (int test_case = 1; test_case <= 10; ++test_case) {
        cin >> len >> start;
        for (int i = 0; i < len / 2; i++) {
            cin >> from >> to;
            contact[from][to] = true;
        }

        cout << '#' << test_case << ' ' << solve() << "\n";

        for (int i = 0; i < 101; i++)
            fill(contact[i], contact[i] + 101, false);
        
        fill(visited, visited + 101, 0);
    }
    return 0;
}
