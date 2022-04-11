#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

int T, N, K, X, t;

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        vector<int> w_list[1 << 7];
        priority_queue<int> tree[1 << 8];                   // 말단 노드의 index : [2^N] ~ [2^(N+1)-1]

        cin >> N >> K >> X;
        int S = 1 << N, ans = 0, max = 0;
        
        for (int i = 0; i < S; i++) {
            for (int j = 0; j < K; j++) {
                cin >> t;
                w_list[i].push_back(t);
                max += t;
            }
        }

        for (int day = 0; day <= X; day++) {
            for (int i = 1; i < S + S; i++) {               // 각 노드마다 일을 처리해서 부모노드에 전달 (항상 최상위 노드부터 처리함을 유의)
                int start_day = N - (int)log2(i) + 1;
                if (start_day <= day && !tree[i].empty()) {
                    int work = tree[i].top();
                    tree[i].pop();
                    if (i / 2 == 0)
                        ans += work;
                    else
                        tree[i / 2].push(work);
                }
            }

            for (int i = 0; i < S; i++) {                   // 말단 노드에서 다음 날에 처리할 일 미리 받아놓음
                if (w_list[i].size() > day)
                    tree[S + i].push(w_list[i][day]);
            }

            if (ans == max)
                break;
        }

        cout << '#' << test_case << ' ' << ans << '\n';
    }
    return 0;
}
