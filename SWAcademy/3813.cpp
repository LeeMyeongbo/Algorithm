#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int T, N, K, W[200000], S[200000];
bool visited[200001];

bool possible(int m)                    // 적합성 판단 (W[i] 전체를 순회하며 덩어리를 처리할 수 있는지 확인)
{
    int s_idx = 0;
    for (int i = 0; i < N; i++) {
        int cur_size = 0;
        while (i < N && W[i] <= m) {
            cur_size++;
            if (cur_size == S[s_idx]) {
                s_idx++;
                break;
            }
            i++;
        }
        if (s_idx == K)
            return true;
    }
    return false;
}

int solve(vector<int>& list)            // 이진 탐색을 이용한 parametric search 활용
{
    int left = 0, right = list.size() - 1, ans = 0;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (possible(list[mid])) {      // 만약 가능하다면 ans에다가 해당값 저장해두고 범위를 작은 쪽으로 반 줄임
            ans = list[mid];
            right = mid - 1;
        }
        else
            left = mid + 1;             // 불가능하면 범위를 큰 쪽으로 반 줄임
    }
    return ans;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        vector<int> w_list;
        cin >> N >> K;

        for (int i = 0; i < N; i++) {
            cin >> W[i];
            if (!visited[W[i]]) {
                w_list.push_back(W[i]);
                visited[W[i]] = true;
            }
        }
        for (int i = 0; i < K; i++)
            cin >> S[i];
        sort(w_list.begin(), w_list.end());         // wear level 정렬

        cout << '#' << test_case << ' ' << solve(w_list) << "\n";
        fill(visited, visited + 200000, false);
    }
    return 0;
}
