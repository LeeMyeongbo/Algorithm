#include <iostream>
#include <cmath>
#define VAL 1000000001
using namespace std;

int N, M, Q, i;
long long a;
pair<long long, long long> tree[1 << 19];           // (합, 최솟값)으로 저장

pair<long long, long long> Find(int index, int start, int end, int left, int right)
{
    if (left > end || right < start)
        return { 0, VAL };
    if (left >= start && right <= end)
        return tree[index];

    pair<long long, long long> left_p = Find(index * 2, start, end, left, (left + right) / 2);
    pair<long long, long long> right_p = Find(index * 2 + 1, start, end, (left + right) / 2 + 1, right);

    return { left_p.first + right_p.first, min(left_p.second, right_p.second) };
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    int S = 1 << (int)ceil(log2(N));

    for (int n = 0; n < N; n++) {
        cin >> a;
        tree[S + n] = { a, a };
    }
    for (int n = N; n < S; n++)
        tree[S + n] = { 0, VAL };

    for (int n = S - 1; n > 0; n--)                             // 트리 형성
        tree[n] = { tree[n * 2].first + tree[n * 2 + 1].first, min(tree[n * 2].second, tree[n * 2 + 1].second) };
    
    cin >> M;
    while (M--) {
        cin >> Q >> i >> a;
        i--;
        if (Q == 1) {
            int idx = S + i;
            long long diff = a - tree[idx].first;
            tree[idx] = { tree[idx].first + diff, a };
            idx /= 2;

            while (idx) {                                       // bottom-up 방식으로 합과 최솟값 갱신
                tree[idx] = { tree[idx].first + diff, min(tree[idx * 2].second, tree[idx * 2 + 1].second) };
                idx /= 2;
            }
        }
        else {
            int left = 0, right = i, l_length = 0;              // 왼쪽 먼저 살핌 -> 최소 길이 0, 최대 길이 i (0 <= i <= N-1)
            while (left <= right) {
                int mid = (left + right) / 2;
                pair<long long, long long> p = Find(1, i - mid, i, 0, S - 1);   // [i - mid, i] 구간에서 최솟값이 a 이상인지 확인
                if (p.second >= a) {                            // 최솟값이 a 이상이라면 mid를 더 크게 잡아봄
                    l_length = mid;
                    left = mid + 1;
                }
                else
                    right = mid - 1;
            }
            left = 0, right = N - 1 - i;

            int r_length = 0;                                   // 그리고 오른쪽 -> 최소 길이 0, 최대 길이 N - 1 - i
            while (left <= right) {
                int mid = (left + right) / 2;
                pair<long long, long long> p = Find(1, i, i + mid, 0, S - 1);   // [i, i + mid] 구간에서 최솟값이 a 이상인지 확인
                if (p.second >= a) {                            // 최솟값이 a 이상이라면 mid 더 크게 잡아봄
                    r_length = mid;
                    left = mid + 1;
                }
                else
                    right = mid - 1;
            }

            pair<long long, long long> p = Find(1, i - l_length, i + r_length, 0, S - 1);     // 최종적으로 구한 [l, r] 구간에서 구간합 구함
            cout << p.first << '\n';
        }
    }
    return 0;
}
