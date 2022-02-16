#include <iostream>
#include <queue>
using namespace std;

int N;
const int dr[] = {0, 0, 1, -1}, dc[] = {1, -1, 0, 0};
char map[5][6];
queue<pair<int, int>> q;

void break_wall(int total, int wall, int loc)
{
    if (wall == total) {
        bool visited[5][5] = {false, };

        for (int i = 0; i < N * N; i++) {
            if (map[i / N][i % N] == '.') {
                q.push({i / N, i % N});
                visited[i / N][i % N] = true;

                while(!q.empty()) {
                    int r = q.front().first;
                    int c = q.front().second;
                    q.pop();

                    for (int d = 0; d < 4; d++) {
                        int R = r + dr[d];
                        int C = c + dc[d];
                        if (R >= 0 && R < N && C >= 0 && C < N && !visited[R][C] && map[R][C] == '.') {
                            q.push({R, C});
                            visited[R][C] = true;
                        }
                    }
                }

                for (int j = 0; j < N * N; j++) {
                    if (map[j / N][j % N] == '.' && !visited[j / N][j % N])
                        return;
                }
                cout << wall;
                exit(0);
            }
        }
    }

    for (int l = loc; l < N * N; l++) {
        if (map[l / N][l % N] == '#') {
            map[l / N][l % N] = '.';
            break_wall(total, wall + 1, l + 1);
            map[l / N][l % N] = '#';
        }
    }
}

int main()
{
    cin >> N;
    for(int i = 0; i < N; i++)
        cin >> map[i];
    
    for (int w = 0; w < 7; w++)
        break_wall(w, 0, 0);

    cout << -1;
    return 0;
}