#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int dr[] = { 1, -1, 0, 0 }, dc[] = { 0, 0, 1, -1 };
bool board_visited[50][50], table_visited[50][50];

vector<vector<pair<int, pair<int, int>>>> getPuzzle(vector<vector<int>>& board, int size, bool visited[][50], int chk)
{
    queue<pair<int, int>> q;
    vector<vector<pair<int, pair<int, int>>>> ret;

    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            if (!visited[r][c] && board[r][c] == chk) {
                vector<pair<int, pair<int, int>>> pos;
                int max_r = -1, min_r = 51, max_c = -1, min_c = 51;
                q.push({ r, c });
                visited[r][c] = true;

                while (!q.empty()) {                            // BFS 방식으로 인접한 격자 찾으며 퍼즐 조각 탐색
                    int cur_r = q.front().first;
                    int cur_c = q.front().second;
                    q.pop();

                    pos.push_back({ 0, {cur_r, cur_c} });
                    max_r = max(max_r, cur_r);
                    min_r = min(min_r, cur_r);
                    max_c = max(max_c, cur_c);
                    min_c = min(min_c, cur_c);
                    
                    for (int d = 0; d < 4; d++) {
                        int R = cur_r + dr[d];
                        int C = cur_c + dc[d];
                        if (R >= 0 && R < size && C >= 0 && C < size && !visited[R][C] && board[R][C] == chk) {
                            q.push({ R, C });
                            visited[R][C] = true;
                        }
                    }
                }

                int M = max(max_r - min_r, max_c - min_c);      // M = 탐색한 퍼즐 조각을 담는데 필요한 최소 정사각형 영역의 한 변 길이 - 1
                for (int i = 0; i < pos.size(); i++)            // 퍼즐 조각의 각 격자마다 좌표를 왼쪽 위로 옮김
                    pos[i] = { M, {pos[i].second.first - min_r, pos[i].second.second - min_c} };
                
                ret.push_back(pos);
            }
        }
    }
    return ret;
}

void rotate(vector<pair<int, pair<int, int>>>& puzzle)              // table의 각 퍼즐들을 시계방향으로 회전
{
    int size = puzzle.size(), min_r = 51, min_c = 51;
    for (int i = 0; i < size; i++) {
        int M = puzzle[i].first;
        int r = puzzle[i].second.first, c = puzzle[i].second.second;

        puzzle[i] = { M, {c, M - r} };
        min_r = min(min_r, c);
        min_c = min(min_c, M - r);
    }

    for (int i = 0; i < size; i++)                                  // 역시나 마찬가지로 각 격자마다 좌표를 왼쪽 위로 옮김
        puzzle[i].second.first -= min_r, puzzle[i].second.second -= min_c;
}

bool is_match(vector<pair<int, pair<int, int>>> board, vector<pair<int, pair<int, int>>> puzzle)
{
    sort(board.begin(), board.end());
    sort(puzzle.begin(), puzzle.end());                         // board 상의 좌표와 puzzle의 좌표를 1:1로 비교하기 위한 정렬

    int size = board.size();
    for (int i = 0; i < size; i++)
        if (board[i] != puzzle[i])
            return false;

    return true;
}

int solution(vector<vector<int>> game_board, vector<vector<int>> table) {
    int answer = 0, size = table[0].size();
    vector<vector<pair<int, pair<int, int>>>> gboard, puzzle;   // (퍼즐 당 최소 필요한 정사각 영역의 한 변 길이, 실제 퍼즐 영역의 좌표)로 저장

    gboard = getPuzzle(game_board, size, board_visited, 0);     // game_board에서 0으로 표현된 공간들의 좌표 저장
    puzzle = getPuzzle(table, size, table_visited, 1);          // table에서 1로 표현된 공간들의 좌표 저장

    bool added[2500] = { false, };                              // 이미 퍼즐 조각이 놓인 곳은 true로 처리 (game_board에서)
    for (int i = 0; i < puzzle.size(); i++) {
        for (int rot = 0; rot < 4; rot++) {                     // 각 퍼즐 조각을 회전시킨 횟수
            bool flag = false;
            for (int j = 0; j < gboard.size(); j++) {
                if (gboard[j].size() != puzzle[i].size())       // 기본적으로 격자 수가 같지 않다면 불가능
                    continue;

                if (!added[j] && is_match(gboard[j], puzzle[i])) {  // 아직 퍼즐이 추가되지 않았으면서 해당 퍼즐과 딱 맞는 곳을 추가
                    answer += gboard[j].size();
                    added[j] = flag = true;
                    break;
                }
            }
            if (flag)
                break;

            rotate(puzzle[i]);                                  // 맞는 영역이 없다면 한 번씩 회전(총 4번)시키면서 맞는 영역 탐색
        }
    }

    return answer;
}
