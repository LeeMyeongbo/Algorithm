#include <iostream>
#include <cstring>
using namespace std;

int N, ans = 1000000000, dp[20][200][200];       // dp[i][j][k] : 현재 정점 i에서 가중치 1 합이 j, 가중치 2 합이 k일 때 1로 갈 수 있으면 1, 못가면 0, 아직 살피지 않은 곳은 -1
char weight1[20][21], weight2[20][21];

int dfs(int cur, int w1, int w2)
{
    int& can_go = dp[cur][w1][w2];
    if (can_go != -1)
        return can_go;                           // 이미 살핀 곳은 다시 살필 필요 x

    if (cur == 1)
        return can_go = 1;                       // 1에 도착했을 경우에는 dp[1][w1][w2]를 1로 체크
    
    can_go = 0;
    for (int i = 0; i < N; i++)
        if (weight1[cur][i] != '.' && w1 + weight1[cur][i] - '0' < 200 && w2 + weight2[cur][i] - '0' < 200)
            can_go = max(can_go, dfs(i, w1 + weight1[cur][i] - '0', w2 + weight2[cur][i] - '0'));

    return can_go;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> weight1[i];

    for (int i = 0; i < N; i++)
        cin >> weight2[i];
    
    memset(dp, -1, sizeof(dp));

    if (!dfs(0, 0, 0))
        cout << -1;
    else {
        for (int i = 0; i < 200; i++) {
            for (int j = 0; j < 200; j++)
                if (dp[1][i][j] == 1)
                    ans = min(ans, i * j);
        }
        cout << ans;
    }
    return 0;
}
