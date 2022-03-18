#include <iostream>
using namespace std;

int N, A, idx[1000001], B, machine[500000], tmp[500000];
long long ans;

void mergesort(int start, int end)
{
    if (start == end)
        return;

    mergesort(start, (start + end) / 2);
    mergesort((start + end) / 2 + 1, end);

    int left = start, mid = (start + end) / 2, right = mid + 1, t = start;

    while (left <= mid && right <= end) {
        if (machine[left] < machine[right])
            tmp[t++] = machine[left++];
        else {
            ans += (long long)mid + 1 - left;
            tmp[t++] = machine[right++];
        }
    }
    while (left <= mid)
        tmp[t++] = machine[left++];
    while (right <= end) {
        ans += (long long)mid + 1 - left;
        tmp[t++] = machine[right++];
    }

    for (int i = start; i < t; i++)
        machine[i] = tmp[i];
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N;

    for (int i = 1; i <= N; i++) {
        cin >> A;
        idx[A] = i;
    }
    for (int i = 0; i < N; i++) {
        cin >> B;
        machine[i] = idx[B];
    }
    mergesort(0, N - 1);
    
    cout << ans;
    return 0;
}
