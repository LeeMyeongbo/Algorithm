#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N, M, chk[2000][2000], f_num, parent[4000001];
const int dr[] = {0, 0, 1, -1}, dc[] = {1, -1, 0, 0};
char map[2000][2001];
pair<int, int> f_dist[2000][2000];              // f_dist[r][c] = {불 번호, 해당 불 번호가 있던 자리로부터 떨어진 최소 거리}
queue<pair<int, pair<int, int>>> fires;         // fires : {불 번호, {r, c}}
vector<pair<int, pair<int, int>>> edges;        // edges : {서로 다른 불이 만나는 시점, {해당 불 번호, 해당 불 번호}}

void checkFire()                // 불 번호 numbering (인접한 불끼리 같은 번호 부여, 1부터 시작)
{
    queue<pair<int, int>> q;
    for (register int i = 0; i < N; i++) {
        for (register int j = 0; j < M; j++) {
            if (!chk[i][j] && map[i][j] == '0') {
                chk[i][j] = ++f_num;
                q.push({i, j});

                while (!q.empty()) {
                    int r = q.front().first;
                    int c = q.front().second;
                    q.pop();

                    fires.push({f_num, {r, c}});
                    f_dist[r][c] = {f_num, 0};
                    for (int d = 0; d < 4; d++) {
                        int R = r + dr[d], C = c + dc[d];
                        if (R >= 0 && R < N && C >= 0 && C < M && !chk[R][C] && map[R][C] == '0') {
                            chk[R][C] = f_num;
                            q.push({R, C});
                        }
                    }
                }
            }
        }
    }

    for (int i = 1; i <= f_num; i++)        // 불 개수만큼 parent[i] = i 설정
        parent[i] = i;
}

void makeGraph()                // 불 퍼뜨리면서 만날 수 있는 불 번호끼리 만나는 시점 저장
{
    while (!fires.empty()) {
        int num = fires.front().first;
        int r = fires.front().second.first;
        int c = fires.front().second.second;
        fires.pop();

        for (int d = 0; d < 4; d++) {
            int R = r + dr[d], C = c + dc[d];
            if (R >= 0 && R < N && C >= 0 && C < M && map[R][C] != '2') {
                if (!f_dist[R][C].first) {                              // 불이 아직 퍼지지 않은 곳은 퍼뜨림
                    f_dist[R][C] = {num, f_dist[r][c].second + 1};
                    fires.push({num, {R, C}});
                }
                else if (f_dist[R][C].first != f_dist[r][c].first) {    // 불이 퍼질 곳에 이미 다른 번호의 불이 퍼졌다면 시점 저장
                    int Max = max(f_dist[R][C].second, f_dist[r][c].second);
                    edges.push_back({Max, {f_dist[R][C].first, f_dist[r][c].first}});
                }
            }
        }
    }
}

int Find(int v)
{
    if (parent[v] == v) return v;
    return parent[v] = Find(parent[v]);
}

bool Union(int v1, int v2)
{
    v1 = Find(v1);
    v2 = Find(v2);

    if (v1 == v2) return false;

    parent[v1] = v2;
    return true;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N >> M;

    for (register int i = 0; i < N; i++)
        cin >> map[i];
    
    checkFire();
    makeGraph();
    
    sort(edges.begin(), edges.end());

    int ans = 0, n = 0, num = 0;
    for (auto &e : edges) {
        if (Union(e.second.first, e.second.second)) {
            ans = max(ans, e.first);
            if (++n == f_num - 1) break;
        }
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (f_dist[i][j].second <= ans && map[i][j] != '2' && f_dist[i][j].first)   // 불이 있는 곳이어야 개수 헤아리기 가능!
                num++;

    cout << ans << ' ' << num;
    return 0;
}