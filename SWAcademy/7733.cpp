#include <iostream>
//#include <fstream>
#include <vector>
#include <queue>
using namespace std;

int T, N, map[100][100], Max;
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };

int solve()
{
    for (int day = 0; day <= 100; day++) {      // 반드시 1번째 날부터 시작한다는 말은 없음...(아예 안 먹은 0번째 날부터 헤아려야 함!)
        // 먼저 요정이 X번째 날에 맛있는 정도가 X인 칸을 먹음 (먹은 칸은 0으로 처리)
        for (int r = 0; r < N; r++)
            for (int c = 0; c < N; c++) {
                if (map[r][c] == day)
                    map[r][c] = 0;
            }

        int lump = 0;       // 덩어리 개수
        queue<pair<int, int>> q;
        bool visited[100][100] = { false, };

        // 그리고 BFS를 반복하며 덩어리 개수 헤아림
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (!visited[r][c] && map[r][c]) {
                    q.push({ r, c });
                    visited[r][c] = true;

                    while (!q.empty()) {
                        int cur_r = q.front().first;
                        int cur_c = q.front().second;
                        q.pop();

                        for (int d = 0; d < 4; d++) {
                            int R = cur_r + dr[d];
                            int C = cur_c + dc[d];
                            if (R >= 0 && R < N && C >= 0 && C < N && !visited[R][C] && map[R][C]) {
                                q.push({ R, C });
                                visited[R][C] = true;
                            }
                        }
                    }
                    lump++;
                }
            }
        }

        Max = max(Max, lump);       // 덩어리 수 최댓값 갱신
    }
    return Max;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    //ifstream fin;
    //fin.open("C:/Users/myeon/Downloads/input.txt");
    //fin >> T;
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        //fin >> N;
        cin >> N;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                cin >> map[i][j];
                //fin >> map[i][j];

        cout << '#' << test_case << ' ' << solve() << "\n";
        Max = 0;
    }
    return 0;
}
