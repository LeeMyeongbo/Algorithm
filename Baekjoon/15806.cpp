#include <iostream>
#include <queue>
using namespace std;

int N, M, K, t, mx, my, map[2][301][301];   // map[0][x][y] : 곰팡이가 처음으로 (r, c)에 나타난 일차, map[1][x][y] : 두 번째로 나타난 일차
const int dx[] = {-1, -2, -2, -1, 1, 2, 2, 1}, dy[] = {-2, -1, 1, 2, 2, 1, -1, -2};
queue<pair<int, pair<int, int>>> q;
pair<int, int> K_pos[90000];

int main()      // 곰팡이가 퍼지는 방식 자체가 한 번 나타나면 기본적으로 이틀 뒤에 다시 나타남. 그걸 이용
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N >> M >> K >> t;
    t++;
    while (M--) {
        cin >> mx >> my;
        if (!map[0][mx][my]) {      // 곰팡이 위치가 중복될 수도 있으므로 새로운 위치의 곰팡이만 나타난 경우에만 큐에 추가
            map[0][mx][my] = 1;
            q.push({1, {mx, my}});
        }
    }
    for (register int i = 0; i < K; i++)
        cin >> K_pos[i].first >> K_pos[i].second;
    
    while (!q.empty()) {            // BFS로 곰팡이 퍼뜨리면서 처음 나타난 일차 + 두 번째 나타난 일차 이렇게 저장
        int day = q.front().first;
        int x = q.front().second.first;
        int y = q.front().second.second;
        q.pop();

        for (int d = 0; d < 8; d++) {
            int X = x + dx[d], Y = y + dy[d];
            if (X >= 1 && X <= N && Y >= 1 && Y <= N) {
                if (!map[0][X][Y]) {
                    map[0][X][Y] = day + 1;
                    q.push({day + 1, {X, Y}});
                }
                else if (!map[1][X][Y]) {
                    map[1][X][Y] = day + 1;
                    q.push({day + 1, {X, Y}});
                }
            }
        }
    }

    for (register int i = 0; i < K; i++) {
        int x = K_pos[i].first, y = K_pos[i].second;
        if (t >= map[0][x][y] && map[1][x][y]) {        // 검사 일차가 처음 나타난 일차 이상이면서 두 번째 나타난 일차가 존재할 경우
            if (map[1][x][y] - map[0][x][y] == 1 || (map[0][x][y] % 2 && t % 2) || (!(map[0][x][y] % 2) && !(t % 2))) {
                cout << "YES";
                return 0;
            }
        }
    }

    cout << "NO";
    return 0;
}