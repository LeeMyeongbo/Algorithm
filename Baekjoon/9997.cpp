#include <iostream>
using namespace std;

int N, str_bit[25], ans;
string str;

void dfs(int cur, int sum)
{
    if (sum == (1 << 26) - 1) {         // 마지막 cur번째 뽑아서 문장이 완성된다면
        ans += 1 << (N - cur);          // 그 뒤의 단어들 뽑는 가짓수(부분집합 개수) 더해주면 됨
        return;
    }
    for (int i = cur; i < N; i++)
        dfs(i + 1, sum | str_bit[i]);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    
    for (int i = 0; i < N; i++) {
        cin >> str;
        for (char c : str) {
            str_bit[i] = str_bit[i] | (1 << c - 'a');
        }
    }
    dfs(0, 0);
    
    cout << ans;
    return 0;
}