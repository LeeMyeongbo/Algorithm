#include <iostream>
#include <queue>
using namespace std;

int T, N, M;
char map[2000][2001];
bool visited[2000][2000];

string solve()
{
    string ans = "";
    priority_queue<pair<char, pair<int, int>>> pq[5000];    // 첫 번째 칸으로부터 이동 거리별로 나눠서 우선순위 큐에 저장
    pq[0].push({ -map[0][0], {0, 0} });

    for (int i = 0; i < N + M - 1; i++) {           // 격자판 크기가 N * M일 때 문자열 길이는 반드시 N + M - 1
        char c = -pq[i].top().first;
        ans.push_back(c);

        // 첫 번째 칸으로부터 이동 거리 별 사전순으로 가장 앞서는 문자들로부터만 오른쪽, 아래쪽 살피며 이동
        while (!pq[i].empty() && -pq[i].top().first == c) {
            char ch = -pq[i].top().first;
            pair<int, int> pos = pq[i].top().second;
            pq[i].pop();

            if (pos.first + 1 < N && !visited[pos.first + 1][pos.second]) {
                visited[pos.first + 1][pos.second] = true;
                pq[i + 1].push({ -map[pos.first + 1][pos.second], {pos.first + 1, pos.second } });
            }
            if (pos.second + 1 < M && !visited[pos.first][pos.second + 1]) {
                visited[pos.first][pos.second + 1] = true;
                pq[i + 1].push({ -map[pos.first][pos.second + 1], {pos.first, pos.second + 1 } });
            }
        }
    }

    return ans;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        string ans = "";
        cin >> N >> M;
        for (int r = 0; r < N; r++) {
            fill(visited[r], visited[r] + M, false);
            cin >> map[r];
        }

        cout << '#' << test_case << ' ' << solve() << "\n";
    }
    return 0;
}
