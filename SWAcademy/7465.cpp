#include <iostream>
//#include <fstream>
#include <vector>
#include <queue>
using namespace std;

int T, N, M, v1, v2;
vector<int> graph[101];

int solve()
{
    queue<int> q;
    bool visited[101] = { false, };
    int ans = 0;

    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            visited[i] = true;
            q.push(i);

            while (!q.empty()) {
                int cur = q.front();
                q.pop();

                for (int v : graph[cur]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
            ans++;
        }
    }
    return ans;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    //ifstream fin;
    //fin.open("C:/Users/myeon/Downloads/s_input.txt");

    //fin >> T;
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        //fin >> N >> M;
        cin >> N >> M;
        for (int i = 0; i < M; i++) {
            //fin >> v1 >> v2;
            cin >> v1 >> v2;
            graph[v1].push_back(v2);
            graph[v2].push_back(v1);
        }

        cout << '#' << test_case << ' ' << solve() << "\n";
        for (int i = 1; i <= N; i++)
            graph[i].clear();
    }
    return 0;
}
