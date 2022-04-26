#include <iostream>
#include <vector>
using namespace std;

int T, N, Max = -1, list[20];
pair<int, int> nasa[20];
bool visited[20];

void dfs(vector<int> graph[], int cur, int depth)
{
    static int tmp[20];
    tmp[depth] = cur;
    
    for (int &i : graph[cur]) {
        if (!visited[i]) {
            visited[i] = true;
            dfs(graph, i, depth + 1);
            visited[i] = false;
        }
    }
    if (Max < depth) {
        Max = depth;
        for (int i = 0; i <= depth; i++)
            list[i] = tmp[i];
    }
}

int main(int argc, char** argv)
{
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        vector<int> graph[20];

        cin >> N;
        for (int i = 0; i < N; i++)
            cin >> nasa[i].first >> nasa[i].second;
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i != j && nasa[i].second == nasa[j].first)
                    graph[i].push_back(j);
            }
        }

        for (int i = 0; i < N; i++) {
            visited[i] = true;
            dfs(graph, i, 0);
            visited[i] = false;
        }

        cout << '#' << test_case << ' ';
        for (int i = 0; i <= Max; i++)
            cout << nasa[list[i]].first << ' ' << nasa[list[i]].second << ' ';
        cout << '\n';

        Max = -1;
	}
	return 0;
}