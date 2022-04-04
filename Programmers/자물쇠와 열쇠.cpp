#include <cstring>
#include <vector>
using namespace std;

int M, N, map[60][60], key_map[20][20];

void rotate()                                       // 시게방향으로 회전
{
    int tmp[20][20] = { 0, };
    for (int r = 0; r < M; r++)
        for (int c = 0; c < M; c++)
            tmp[c][M - 1 - r] = key_map[r][c];      // 시계 방향 코드 기억!
    
    for (int r = 0; r < M; r++)
        for (int c = 0; c < M; c++)
            key_map[r][c] = tmp[r][c];
}

bool is_match(int r, int c)
{
    int tmp_map[60][60] = { 0, };
    memcpy(tmp_map, map, sizeof(map));

    for (int i = r; i < r + M; i++)
        for (int j = c; j < c + M; j++)
            tmp_map[i][j] += key_map[i - r][j - c];
    
    for (int r = M - 1; r < N + M - 1; r++)             // lock에서 진짜 자물쇠 영역이 모두 1이 되는지 확인
        for (int c = M - 1; c < N + M - 1; c++)
            if (tmp_map[r][c] != 1)                     // 빈 부분이 있거나(0) 겹치는 부분(2)이 있다면 안 되는거
                return false;

    return true;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    M = key[0].size(), N = lock[0].size();
    for (int r = M - 1; r < N + M - 1; r++)             // 자물쇠에서 위, 아래, 오른쪽, 왼쪽 각각 M-1칸씩 여유 두고 저장
        for (int c = M - 1; c < N + M - 1; c++)
            map[r][c] = lock[r - M + 1][c - M + 1];

    for (int r = 0; r < M; r++)
        for (int c = 0; c < M; c++)
            key_map[r][c] = key[r][c];                  // key는 뭐 그대로 저장

    for (int r = 0; r < N + M - 1; r++) {
        for (int c = 0; c < N + M - 1; c++) {
            for (int d = 0; d < 4; d++) {               // 같은 자리에서 총 4번 돌려가며 꼭 들어맞는지 확인!
                if (is_match(r, c))
                    return true;

                rotate();
            }
        }
    }
    return false;
}
