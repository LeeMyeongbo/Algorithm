#include <iostream>
#include <queue>
#define MAX 1<<30
using namespace std;

int T, N, dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
char map[100][101];

int solve()
{
    priority_queue<pair<int, pair<int, int>>> pq;
    int dij[100][100] = { 0, };
    for (int i = 0; i < N; i++)
        fill(dij[i], dij[i] + N, MAX);

    pq.push({ 0, {0, 0} });
    while (!pq.empty()) {
        int sum = -pq.top().first;
        pair<int, int> cur = pq.top().second;
        pq.pop();

        if (cur.first == N - 1 && cur.second == N - 1)
            return sum;

        for (int d = 0; d < 4; d++) {
            int r = cur.first + dr[d];
            int c = cur.second + dc[d];
            if (r >= 0 && r < N && c >= 0 && c < N && dij[r][c] > sum + map[r][c] - '0') {
                dij[r][c] = sum + map[r][c] - '0';
                pq.push({ -dij[r][c], {r, c} });
            }
        }
    }
    return -1;
}

int main(int argc, char** argv)
{
    cin >> T;
    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N;
        for (int i = 0; i < N; i++)
            cin >> map[i];
        
        cout << '#' << test_case << ' ' << solve() << endl;
    }
    return 0;
}
