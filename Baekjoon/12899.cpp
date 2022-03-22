#include <iostream>
using namespace std;

int N, T, X, S = 1 << 21, tree[1 << 22];

int find()
{
    int index = 1, x = X;
    while (index < S) {
        if (tree[index + index] >= x)       // X번째로 작은 숫자가 왼쪽 서브트리에 존재 시
            index += index;
        else {                              // 오른쪽 서브트리에 존재 시
            x -= tree[index + index];
            index = index + index + 1;
        }
    }
    return index - S;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N;

    while (N--) {
        cin >> T >> X;
        if (T == 1) {
            int idx = S + X;
            while (idx) {
                tree[idx]++;
                idx /= 2;
            }
        }
        else {
            int ans = find();
            cout << ans << '\n';

            int idx = S + ans;
            while (idx) {
                tree[idx]--;
                idx /= 2;
            }
        }
    }
    return 0;
}
