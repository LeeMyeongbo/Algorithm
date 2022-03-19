#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#define MAX 131072
using namespace std;

int N, M, Q, i, j, k;
long long v, tree[MAX * 2];
vector<pair<int, long long>> ans, query1;                   // ans : (index, 답)으로, query1 : (i, v)로 저장
vector<pair<pair<int, int>, pair<int, int>>> query2;        // query2 : ((k, index), (i, j))로 저장

long long getSum(int index, int start, int end, int left, int right)
{
    if (left > end || right < start)
        return 0;
    if (left >= start && right <= end)
        return tree[index];

    return getSum(index * 2, start, end, left, (left + right) / 2) + getSum(index * 2 + 1, start, end, (left + right) / 2 + 1, right);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    int S = 1 << (int)ceil(log2(N));

    for (int n = 0; n < N; n++)
        cin >> tree[S + n];

    for (int n = S - 1; n > 0; n--)
        tree[n] = tree[n * 2] + tree[n * 2 + 1];        // 인덱스 트리 형성

    int idx = 0;

    cin >> M;
    while (M--) {                                       // 2번 쿼리를 순서대로 하는 게 아닌, k가 작은 2번 쿼리부터 처리! (오프라인 쿼리)
        cin >> Q;
        if (Q == 1) {
            cin >> i >> v;
            query1.push_back({ i, v });
        }
        else {
            cin >> k >> i >> j;
            query2.push_back({ {k, idx++}, {i, j} });
        }
    }
    sort(query2.begin(), query2.end());                 // k 기준 오름차순으로, k가 같을 때는 index 오름차순으로 2번 쿼리 정렬

    idx = 0;
    for (auto& q : query2) {
        while (idx < q.first.first) {
            pair<int, long long> q1 = query1[idx++];
            int index = S + q1.first - 1;
            long long diff = q1.second - tree[index];

            while (index) {                     // 인덱스 트리 업데이트
                tree[index] += diff;
                index /= 2;
            }
        }
        long long sum = getSum(1, q.second.first - 1, q.second.second - 1, 0, S - 1);
        ans.push_back({ q.first.second, sum });
    }

    sort(ans.begin(), ans.end());
    for (auto& a : ans)
        cout << a.second << '\n';
    
    return 0;
}
