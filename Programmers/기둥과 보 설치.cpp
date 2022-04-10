#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

bool map[2][101][101];       // map[0][r][c] = true일 때 (r, c)~(r + 1, c)로 기둥 설치, map[1][r][c] = true일 때 (r, c)~(r, c + 1)로 보 설치
list<pair<int, int>> gidung, bo;

bool g_satisfied(bool g, int r, int c)      // (r, c)의 구조물을 지웠을 때 모든 기둥들이 조건을 만족하는지 살핌
{
    for (auto it = gidung.begin(); it != gidung.end(); ) {
        int y = it->first, x = it->second;
        if (g && y == r && x == c)
            it = gidung.erase(it);
        else if (!(!y || map[1][y][x - 1] || map[1][y][x] || map[0][y - 1][x]))
            return false;
        else
            it++;
    }
    return true;
}

bool b_satisfied(bool b, int r, int c)      // (r, c)의 구조물을 지웠을 때 모든 보들이 조건을 만족하는지 살핌
{
    for (auto it = bo.begin(); it != bo.end(); ) {
        int y = it->first, x = it->second;
        if (b && y == r && x == c)
            it = bo.erase(it);
        else if (!(map[0][y - 1][x] || map[0][y - 1][x + 1] || (map[1][y][x + 1] && x - 1 >= 0 && map[1][y][x - 1])))
            return false;
        else
            it++;
    }
    return true;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;
    
    for (auto& build : build_frame) {
        int r = build[1], c = build[0], a = build[2], b = build[3];
        if (!a && !b) {                                         // (r, c)~(r + 1, c)의 기둥 삭제 시
            map[0][r][c] = false;
            if (!g_satisfied(true, r, c) || !b_satisfied(false, r, c)) {
                map[0][r][c] = true;
                gidung.push_back({ r, c });
            }
        }
        else if (!a && b) {                                     // (r, c)~(r + 1, c)에 기둥 설치 시
            if (!r || map[1][r][c - 1] || map[1][r][c] || map[0][r - 1][c]) {
                map[0][r][c] = true;
                gidung.push_back({ r, c });                     // 바닥이거나 보의 한 쪽 끝 위에 있거나 다른 기둥 위에 있는 거라면 가능
            }
        }
        else if (a && !b) {                                     // (r, c)~(r, c + 1)의 보 삭제 시
            map[1][r][c] = false;
            if (!g_satisfied(false, r, c) || !b_satisfied(true, r, c)) {
                map[1][r][c] = true;
                bo.push_back({ r, c });
            }
        }
        else {                                                  // (r, c)~(r, c + 1)에 보 설치 시
            if (map[0][r - 1][c] || map[0][r - 1][c + 1] || (map[1][r][c + 1]) && (c - 1 >= 0 && map[1][r][c - 1])) {
                map[1][r][c] = true;
                bo.push_back({ r, c });                         // 어느 한 곳에 기둥이 있거나 양쪽에 보가 설치되어 있을 경우 가능
            }
        }
    }

    for (int a = 0; a < 2; a++)
        for (int r = 0; r <= n; r++)
            for (int c = 0; c <= n; c++)
                if (map[a][r][c]) {
                    vector<int> tmp;
                    tmp.push_back(c);
                    tmp.push_back(r);
                    tmp.push_back(a);
                    answer.push_back(tmp);
                }

    sort(answer.begin(), answer.end());
    return answer;
}

int main()
{
    int n, f, x, y, a, b;
    vector<vector<int>> build_frame;
    cin >> n >> f;

    while (f--) {
        vector<int> tmp;
        cin >> x >> y >> a >> b;
        tmp.push_back(x);
        tmp.push_back(y);
        tmp.push_back(a);
        tmp.push_back(b);
        build_frame.push_back(tmp);
    }

    vector<vector<int>> ans = solution(n, build_frame);

    for (auto& a : ans)
        cout << a[0] << ' ' << a[1] << ' ' << a[2] << '\n';

    return 0;
}
