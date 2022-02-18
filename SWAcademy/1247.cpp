#include <iostream>
//#include <fstream>
#include <vector>
#include <cmath>
#define MAX 1<<30
using namespace std;

int T, N, start_x, start_y, dest_x, dest_y, Ans = MAX;
bool visited[10];
pair<int, int> p[10];

void dfs(int cur_x, int cur_y, int depth, int move)
{
    if (depth == N) {
        Ans = min(Ans, move + abs(cur_x - dest_x) + abs(cur_y - dest_y));
        return;
    }
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            visited[i] = true;
            dfs(p[i].first, p[i].second, depth + 1, move + abs(p[i].first - cur_x) + abs(p[i].second - cur_y));
            visited[i] = false;
        }
    }
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    //ifstream fin;
    //fin.open("C:/Users/myeon/Downloads/input.txt");

    //fin >> T;
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        //fin >> N >> start_x >> start_y >> dest_x >> dest_y;
        cin >> N >> start_x >> start_y >> dest_x >> dest_y;
        for (int i = 0; i < N; i++)
            cin >> p[i].first >> p[i].second;       // 고객들의 집 좌료 저장
            //fin >> p[i].first >> p[i].second;

        dfs(start_x, start_y, 0, 0);
        cout << '#' << test_case << ' ' << Ans << "\n";
        Ans = MAX;
    }
    return 0;
}
