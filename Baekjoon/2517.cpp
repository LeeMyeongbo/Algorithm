#include <iostream>
#include <algorithm>
using namespace std;

int N;
pair<int, pair<int, int>> arr[500000];      // arr[n] = {index, {현재 실력, 더 앞에 위치해 있으면서 현재 실력보다 실력이 작은 선수들의 수}}

void mergesort(int start, int end)
{
    if (start == end)
        return;

    mergesort(start, (start + end) / 2);
    mergesort((start + end) / 2 + 1, end);

    int left = start, right = (start + end) / 2 + 1, i = start;
    static pair<int, pair<int, int>> tmp[500000];

    while (left <= (start + end) / 2 && right <= end) {
        if (arr[left].second.first < arr[right].second.first) // 왼쪽 배열의 값이 더 작을 때는 그대로 복사
            tmp[i++] = arr[left++];
        else {
            arr[right].second.second += left - start;         // 오른쪽 배열의 값이 더 작을 땐 현재까지 복사된 왼쪽 배열의 값 개수만큼 더함
            tmp[i++] = arr[right++];
        }
    }
    while (left <= (start + end) / 2)
        tmp[i++] = arr[left++];
    while (right <= end) {
        arr[right].second.second += left - start;
        tmp[i++] = arr[right++];
    }

    for (int n = start; n < i; n++)
        arr[n] = tmp[n];
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N;

    for (int i = 0; i < N; i++) {
        arr[i].first = i;
        cin >> arr[i].second.first;
    }
    
    mergesort(0, N - 1);
    sort(arr, arr + N);

    for (int i = 0; i < N; i++)
        cout << i + 1 - arr[i].second.second << "\n";

    return 0;
}
