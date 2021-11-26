#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Ball {
    bool destroyed;
    int dir, r, c;
};
const int dr[] = {1, 0, -1, 0}, dc[] = {0, -1, 0, 1};
int n, size_of_3, Ans, map[10][10], balls[40];
pair<int, int> three[5];

int simul()
{
    int get_out = 0;
    vector<int> loc_ball[10][10];
    Ball b[40];
    
    for (int ball = 0; ball < 4 * n; ball++) {
        if (balls[ball]) {
            b[ball] = {false, ball / n, 0, 0};
            if (ball < n)
                b[ball].r = -1, b[ball].c = ball;
            else if (ball < 2 * n)
                b[ball].r = ball - n, b[ball].c = n;
            else if (ball < 3 * n)
                b[ball].r = n, b[ball].c = 3 * n - ball - 1;
            else
                b[ball].r = 4 * n - ball - 1, b[ball].c = -1;
        }
    }
    while (1) {
        bool finish = true;
        for (int ball = 0; ball < 4 * n; ball++) {
            if (balls[ball] && !b[ball].destroyed) {
                finish = false;
                if (b[ball].r >= 0 && b[ball].r < n && b[ball].c >= 0 && b[ball].c < n) {
                    for (int i = 0; i < loc_ball[b[ball].r][b[ball].c].size(); i++) {
                        if (loc_ball[b[ball].r][b[ball].c].at(i) == ball) {
                            loc_ball[b[ball].r][b[ball].c].erase(loc_ball[b[ball].r][b[ball].c].begin() + i);
                            break;
                        }
                    }
                }
                
                b[ball].r += dr[b[ball].dir];
                b[ball].c += dc[b[ball].dir];
                if (b[ball].r < 0 || b[ball].r >= n || b[ball].c < 0 || b[ball].c >= n) {
                    get_out++;
                    b[ball].destroyed = true;
                }
                else
                    loc_ball[b[ball].r][b[ball].c].push_back(ball);

                if (map[b[ball].r][b[ball].c] == 1) {
                    if (b[ball].dir == 0)
                        b[ball].dir = 1;
                    else if (b[ball].dir == 1)
                        b[ball].dir = 0;
                    else if (b[ball].dir == 2)
                        b[ball].dir = 3;
                    else
                        b[ball].dir = 2;
                }
                else if (map[b[ball].r][b[ball].c] == 2) {
                    if (b[ball].dir == 0)
                        b[ball].dir = 3;
                    else if (b[ball].dir == 1)
                        b[ball].dir = 2;
                    else if (b[ball].dir == 2)
                        b[ball].dir = 1;
                    else
                        b[ball].dir = 0;
                }
            }
        }
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (loc_ball[r][c].size() > 1) {
                    while (!loc_ball[r][c].empty()) {
                        int number = loc_ball[r][c].front();
                        b[number].destroyed = true;
                        loc_ball[r][c].erase(loc_ball[r][c].begin());
                    }
                }
            }
        }
        if (finish)
            break;
    }
    return get_out;
}

void dfs(int depth) 
{
    if (depth == size_of_3) {
        int temp = simul();
        Ans = max(Ans, temp);
        return;
    }
    for (int choice = 0; choice < 3; choice++) {
        map[three[depth].first][three[depth].second] = choice;
        dfs(depth + 1);
        map[three[depth].first][three[depth].second] = 3;
    }
}

int main()
{
    cin >> n;
    for (int i = 0; i < n * n; i++) {
        cin >> map[i / n][i % n];
        if (map[i / n][i % n] == 3)
            three[size_of_3++] = {i / n, i % n};
    }

    for (int i = 0; i < 4 * n; i++)
        cin >> balls[i];

    dfs(0);
    cout << Ans;
    return 0;
}