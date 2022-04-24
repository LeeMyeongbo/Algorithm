#include <iostream>
#include <vector>
using namespace std;

vector<int> map[5][5];          // map[x][y] = {d} : (x, y)에 방향이 d인 물고기 존재
vector<pair<int, pair<int, int>>> copy_fish;
const int dx1[] = {0, -1, -1, -1, 0, 1, 1, 1}, dy1[] = {-1, -1, 0, 1, 1, 1, 0, -1};     // 물고기 이동
const int dx2[] = {-1, 0, 1, 0}, dy2[] = {0, -1, 0, 1};                                 // 상어 이동
int M, S, fx, fy, d, sx, sy, smell[5][5], fish_num[5][5], shark_move[3], Max = -1;

void move()                     // 물고기 이동 가즈아
{
    vector<int> temp[5][5];
    for (int x = 1; x <= 4; x++) {
        for (int y = 1; y <= 4; y++) {
            for (int f = map[x][y].size() - 1; f >= 0; f--) {

                // 그 전에 먼저 물고기들 복제
                copy_fish.push_back({map[x][y][f], {x, y}});

                bool flag = false;
                for (int d = 0; d < 8; d++) {
                    int new_dir = map[x][y][f] - d < 0 ? map[x][y][f] - d + 8 : map[x][y][f] - d;   // 반시계 방향으로 살핌
                    int X = x + dx1[new_dir], Y = y + dy1[new_dir];

                    // 범위 내부 + 물고기 냄새 x + 상어 없는 곳 있다면 이동
                    if (X > 0 && X <= 4 && Y > 0 && Y <= 4 && !smell[X][Y] && !(X == sx && Y == sy)) {
                        map[x][y].pop_back();
                        temp[X][Y].push_back(new_dir);
                        flag = true;
                        break;
                    }
                }

                // 이동에 실패했다면 위치 그대로
                if (!flag) {
                    temp[x][y].push_back(map[x][y][f]);
                    map[x][y].pop_back();
                }
            }
        }
    }
    for (int x = 1; x <= 4; x++)
        for (int y = 1; y <= 4; y++)
            map[x][y] = temp[x][y];
}

void find_max(int depth, int x, int y, int cnt)         // 현재 (x, y)에서 물고기를 최대한 많이 쳐먹을 수 있는 경로 찾음
{
    static int dir[3];
    if (depth == 3) {
        // 최댓값 갱신되면 경로 저장
        if (Max < cnt) {
            Max = cnt;
            shark_move[0] = dir[0], shark_move[1] = dir[1], shark_move[2] = dir[2];
        }
        return;
    }
    for (int d = 0; d < 4; d++) {
        int X = x + dx2[d];
        int Y = y + dy2[d];
        if (Y > 0 && Y <= 4 && X > 0 && X <= 4) {
            int tmp = fish_num[X][Y];
            fish_num[X][Y] = 0;
            dir[depth] = d;
            find_max(depth + 1, X, Y, cnt + tmp);
            dir[depth] = 0;
            fish_num[X][Y] = tmp;
        }
    }
}

void eat(int seq)                       // 물고기 쳐묵 (seq : 현재 시점)
{
    for (int r = 1; r <= 4; r++)
        for (int c = 1; c <= 4; c++)
            fish_num[r][c] = map[r][c].size();

    Max = -1;
    find_max(0, sx, sy, 0);

    for (int i = 0; i < 3; i++) {
        sy += dy2[shark_move[i]], sx += dx2[shark_move[i]];     // 저장된 경로대로 상어 이동하고
        if (map[sx][sy].size()) {                               // 물고기가 있다면
            map[sx][sy].clear();                                // 쳐묵
            smell[sx][sy] = seq;                                // 냄새 남김 (smell에 냄새가 남은 시점 저장)
        }
    }

    // 이미 두 번 전에 남은 냄새는 없앰
    for (int r = 1; r <= 4; r++)
        for (int c = 1; c <= 4; c++)
            if (smell[r][c] == seq - 2)
                smell[r][c] = 0;
}

void duplicate()                        // 물고기 복제
{
    for (int f = copy_fish.size() - 1; f >= 0; f--) {
        int dir = copy_fish[f].first;
        int x = copy_fish[f].second.first;
        int y = copy_fish[f].second.second;

        map[x][y].push_back(dir);
        copy_fish.pop_back();
    }
}

int main()
{
    cin >> M >> S;
    while (M--) {
        cin >> fx >> fy >> d;
        map[fx][fy].push_back(d - 1);
    }
    cin >> sx >> sy;

    for (int i = 1; i <= S; i++) {
        move();
        eat(i);
        duplicate();
    }
    int ans = 0;
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            ans += map[i][j].size();
    
    cout << ans;
    return 0;
}