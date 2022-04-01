#include <iostream>
#include <queue>
#include <cmath>
#define M 1000000000
using namespace std;

int T, N, S[16][16], Min = M;

void dfs(int depth, int start) 
{
    static bool chosen[16];

    if (depth == N / 2) {
        int chosen_A[8] = { 0, }, chosen_B[8] = { 0, }, a = 0, b = 0;
        for (int i = 0; i < N; i++) {
            if (chosen[i])
                chosen_A[a++] = i;                  // 실제로 뽑은 음식 재료 번호는 A에 저장하고
            else
                chosen_B[b++] = i;                  // 뽑지 않은 음식 재료는 B에 저장
        }

        int A = 0, B = 0;
        for (int i = 0; i < N / 2; i++) {
            for (int j = 0; j < N / 2; j++) {
                A += S[chosen_A[i]][chosen_A[j]];   // 그리고 시너지를 더함 (S[n][n] = 0이므로 이렇게 해도 됨)
                B += S[chosen_B[i]][chosen_B[j]];
            }
        }
        Min = min(Min, abs(A - B));                 // 그리고 차의 최솟값 갱신
        return;
    }

    for (int i = start + 1; i < N; i++) {           // 조합(Combination) 활용 (N개 중에 N/2개 뽑는 경우의 수)
        chosen[i] = true;
        dfs(depth + 1, i);
        chosen[i] = false;
    }
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                cin >> S[i][j];
        
        dfs(0, -1);

        cout << '#' << test_case << ' ' << Min << "\n";
        Min = M;
    }
    return 0;
}
