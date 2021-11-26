#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
    int turn, r, c;
};
int N, start_r, start_c, Ans;
const int dr[] = {0, 0, 1, -1}, dc[] = {1, -1, 0, 0};
char map[7][8];
queue<Node> q;

int BFS()
{
    q.push({0, start_r, start_c});
    while (!q.empty()) {
        Node node = q.front();
        q.pop();

        int turn = node.turn + 1;
        for (int d = 0; d < 4; d++) {
            bool exploded = false;
            int R = node.r + dr[d];
            int C = node.c + dc[d];
            if (R >= 0 && R < N && C >= 0 && C < N && map[R][C] != '#') {
                bool visited[7][7] = {false, };
                queue<Node> move;

                move.push({0, R, C});
                visited[R][C] = true;
                while(!move.empty()) {
                    Node n = move.front();
                    move.pop();

                    if (n.turn == turn)
                        continue;

                    for (int s = 0; s < 4; s++) {
                        int new_r = n.r + dr[s];
                        int new_c = n.c + dc[s];
                        if (new_r >= 0 && new_r < N && new_c >= 0 && new_c < N && map[new_r][new_c] != '#') {
                            if (!visited[new_r][new_c]) {
                                visited[new_r][new_c] = true;
                                move.push({n.turn + 1, new_r, new_c});
                            }
                        }
                        else {
                            exploded = true;
                            Ans = max(Ans, turn);
                            break;
                        }
                    }
                    if (exploded)
                        break;
                }
            }
            else {
                exploded = true;
                Ans = max(Ans, turn);
            }
            if (!exploded) {
                q.push({turn, R, C});
            }
        }
    }
    return Ans;
}

int main()
{
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> map[i];
        for (int j = 0; j < N; j++) {
            if (map[i][j] == 'B') {
                start_r = i, start_c = j;
                map[i][j] = '.';
            }
        }
    }
    cout << BFS();
    return 0;
}