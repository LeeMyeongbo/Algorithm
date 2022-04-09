#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

int T, X, Y, parent[101], map[50][50];          // map : 벽은 -2, 빈 곳은 -1, 그 외 A와 S는 0, 1, 2...로 저장
const int dr[] = { 1, -1, 0, 0 }, dc[] = { 0, 0, 1, -1 };
char c;
vector<pair<int, int>> pos;
vector<pair<int, pair<int, int>>> edges;

int Find(int v)
{
    if (parent[v] == v)
        return v;
    return parent[v] = Find(parent[v]);
}

bool Union(int v1, int v2)
{
    v1 = Find(v1);
    v2 = Find(v2);
    if (v1 == v2)
        return false;

    parent[v1] = v2;
    return true;
}

int solve()
{
    int ans = 0;
    for (int i = 0; i < (int)pos.size(); i++) {         // 각 A(S도 포함) 마다 나머지 모든 A(S)까지의 거리를 edges에 저장
        queue<pair<int, pair<int, int>>> q;             // 이를 위해 각 A(S) 마다 BFS를 (전체 A, S 개수 - 1)번씩 돌림
        bool visited[50][50] = { false, };

        q.push({ 0, pos[i] });
        visited[pos[i].first][pos[i].second] = true;

        while (!q.empty()) {
            int r = q.front().second.first;
            int c = q.front().second.second;
            int cnt = q.front().first;
            q.pop();

            for (int d = 0; d < 4; d++) {
                int R = r + dr[d];
                int C = c + dc[d];
                if (R >= 0 && R < Y && C >= 0 && C < X && !visited[R][C] && map[R][C] != -2) {
                    q.push({ cnt + 1, {R, C} });
                    visited[R][C] = true;

                    if (map[R][C] != -1)
                        edges.push_back({ cnt + 1, {i, map[R][C]} });   // 다른 A 혹은 S 만났을 시 최소 거리 저장
                }
            }
        }
    }
    sort(edges.begin(), edges.end());
    for (int i = 0; i < (int)pos.size(); i++)
        parent[i] = i;

    int e_num = 0;
    for (auto& edge : edges) {
        if (Union(edge.second.first, edge.second.second)) {             // MST를 이용하여 모든 노드들 연결하기 위한 최소비용 구함
            e_num++;
            ans += edge.first;
            if (e_num == (int)pos.size() - 1)
                return ans;
        }
    }

    return 0;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        memset(map, -1, sizeof(map));

        cin >> X >> Y;
        for (int i = 0; i < Y; i++) {
            for (int j = 0; j < X; j++) {
                cin >> c;
                if (c == '#')
                    map[i][j] = -2;
                else if (c == 'A' || c == 'S') {
                    map[i][j] = pos.size();
                    pos.push_back({ i, j });        // A 또는 S인 지역은 따로 좌표도 저장
                }
            }
        }

        cout << solve() << '\n';

        pos.clear();
        edges.clear();
    }
    return 0;
}
