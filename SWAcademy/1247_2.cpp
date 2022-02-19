#include <iostream>
//#include <fstream>
#include <vector>
#include <cmath>
#include <queue>
#define MAX 1<<30
using namespace std;

int T, N, start_x, start_y, dest_x, dest_y, Ans = MAX, visited[1024][10];
pair<int, int> p[10];
queue<pair<int, pair<int, int>>> q;          // (이동 거리, (현재 위치, 2^거친 정점 수 - 1))로 저장

int solve()
{
    for (int i = 0; i < (1 << N); i++)
        fill(visited[i], visited[i] + N, MAX);
    
    for (int d = 0; d < N; d++) {
        visited[1 << d][d] = abs(start_x - p[d].first) + abs(start_y - p[d].second);
        q.push({ visited[1 << d][d], {d, 1 << d} });
    }

    while (!q.empty()) {
        int move = q.front().first;
        pair<int, int> pos = q.front().second;
        q.pop();

        if (pos.second == (1 << N) - 1) {
            Ans = min(Ans, move + abs(dest_x - p[pos.first].first) + abs(dest_y - p[pos.first].second));
            continue;
        }

        for (int v = 0; v < N; v++) {
            if (pos.first != v && visited[pos.second | (1 << v)][v] > move + abs(p[v].first - p[pos.first].first) + abs(p[v].second - p[pos.first].second)) {
                visited[pos.second | (1 << v)][v] = move + abs(p[v].first - p[pos.first].first) + abs(p[v].second - p[pos.first].second);
                q.push({ visited[pos.second | (1 << v)][v], {v, pos.second | (1 << v)} });
            }
        }
    }

    return Ans;
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
            cin >> p[i].first >> p[i].second;       // 고객들의 집 좌표 저장
            //fin >> p[i].first >> p[i].second;
 
        cout << '#' << test_case << ' ' << solve() << "\n";
        Ans = MAX;
    }
    return 0;
}
