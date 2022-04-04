#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;

int map[300][300], parent[100000];
const int dr[] = { 1, -1, 0, 0 }, dc[] = { 0, 0, 1, -1 };

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

int solution(vector<vector<int>> land, int height) {    // BFS + MST로 풀이 가능
    int answer = 0;

    queue<pair<int, int>> q;
    int len = land[0].size(), num = 0;

    for (int r = 0; r < len; r++) {                 // 먼저 사다리 없이 이동가능한 영역별로 표시를 해줘야 함
        for (int c = 0; c < len; c++) {
            if (map[r][c])
                continue;

            map[r][c] = ++num;                      // 방문한 적 없는 영역을 만나면 방문 체크 겸 순서 저장
            q.push({ r, c });

            while (!q.empty()) {                    // BFS 돌리면서 모든 영역에 대해 표시 ㄱㄱ
                int cur_r = q.front().first;
                int cur_c = q.front().second;
                q.pop();

                for (int d = 0; d < 4; d++) {
                    int R = cur_r + dr[d];
                    int C = cur_c + dc[d];
                    if (R >= 0 && R < len && C >= 0 && C < len && !map[R][C] && abs(land[R][C] - land[cur_r][cur_c]) <= height) {
                        map[R][C] = num;
                        q.push({ R, C });
                    }
                }
            }
        }
    }

    vector<pair<int, pair<int, int>>> edges;        // 서로 다른 표시가 되어 있는 영역별로 높이 차를 저장
    for (int r = 0; r < len; r++) {
        for (int c = 0; c < len; c++) {
            for (int d = 0; d < 4; d++) {           // 역시 모든 영역들을 살피며, 인접하면서 표시가 다른 영역과의 높이 차 저장
                int R = r + dr[d];
                int C = c + dc[d];
                if (R >= 0 && R < len && C >= 0 && C < len && map[R][C] != map[r][c])
                    edges.push_back({ abs(land[R][C] - land[r][c]), {map[R][C], map[r][c]} });
            }
        }
    }
    sort(edges.begin(), edges.end());               // 높이 차 오름차순으로 정렬

    for (int i = 1; i <= num; i++)
        parent[i] = i;

    int added_edge = 0;                             // 크루스칼 알고리즘
    for (auto& edge : edges) {                      // edges가 비어있을 수도(모든 영역이 표시가 같은 경우) 있으므로 반드시 for-each 문 활용
        if (Union(edge.second.first, edge.second.second)) {
            answer += edge.first;                   // 연결이 안돼 있었을 경우 연결하고 높이 차 answer에 추가
            added_edge++;
            if (added_edge == num - 1)
                break;
        }
    }

    return answer;                                  // 최종 answer 출력
}
