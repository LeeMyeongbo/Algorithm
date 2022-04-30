#include <iostream>
using namespace std;

int D, P, ans = -1;

void dfs(int depth, int start, int cur, int jari, int d)    // 10 ^ (d-1) = jari
{
    if (depth == P && d <= D) {
        ans = max(ans, cur);
        return;
    }
    if (d > D) return;
    
    for (int num = start; num <= 9; num++) {                // 중복조합 활용
        int new_n = cur * num;
        if (new_n / jari >= 10)
            dfs(depth + 1, num, new_n, jari * 10, d + 1);
        else
            dfs(depth + 1, num, new_n, jari, d);
    }
}

int main()
{
    cin >> D >> P;
    dfs(0, 2, 1, 1, 1);

    cout << ans;
    return 0;
}