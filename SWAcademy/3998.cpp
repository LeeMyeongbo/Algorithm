#include <iostream>
using namespace std;

int T, N, A[100000], tmp[100000];
long long ans;                          // 최대 100000개이므로 1+2+3+...+99999 계산 시 답이 int범위 초과 가능!

void mergesort(int start, int end)
{
    if (start == end)
        return;

    mergesort(start, (start + end) / 2);
    mergesort((start + end) / 2 + 1, end);

    int left = start, right = (start + end) / 2 + 1, t = start;

    while (left <= (start + end) / 2 && right <= end) {
        if (A[left] < A[right])
            tmp[t++] = A[left++];
        else {
            ans += ((long long)start + end) / 2 + 1 - left;     // 오른쪽 배열을 끌어올 때 아직 왼쪽 배열에 남아있는 숫자 개수만큼 더해줌
            tmp[t++] = A[right++];
        }
    }
    while (left <= (start + end) / 2)
        tmp[t++] = A[left++];
    while (right <= end) {
        ans += ((long long)start + end) / 2 + 1 - left;
        tmp[t++] = A[right++];
    }

    for (int i = start; i < t; i++)
        A[i] = tmp[i];
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N;
        for (int i = 0; i < N; i++)
            cin >> A[i];

        mergesort(0, N - 1);

        cout << '#' << test_case << ' ' << ans << '\n';
        ans = 0;
    }
    return 0;
}
