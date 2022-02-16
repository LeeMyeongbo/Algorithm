#include <iostream>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, a, b, A[100001], ans[2][400004];		// ans[0][i] : 최솟값, ans[1][i] : 최댓값

int init_Min(int index, int start, int end)
{
	if (start == end)
		return ans[0][index] = A[start];
	
	return ans[0][index] = min(init_Min(index * 2, start, (start + end) / 2), init_Min(index * 2 + 1, (start + end) / 2 + 1, end));
}

int init_Max(int index, int start, int end)
{
	if (start == end)
		return ans[1][index] = A[start];

	return ans[1][index] = max(init_Max(index * 2, start, (start + end) / 2), init_Max(index * 2 + 1, (start + end) / 2 + 1, end));
}

int get_Min(int index, int start, int end)
{
	if (start > b || end < a)				// 구간을 벗어난 경우에는 10^9 + 1 출력 (1 <= n <= 1000000000)
		return 1000000001;
	if (start >= a && end <= b)				// 구간 내부에 존재하면 바로 해당 구간의 최솟값 출력
		return ans[0][index];
	return min(get_Min(index * 2, start, (start + end) / 2), get_Min(index * 2 + 1, (start + end) / 2 + 1, end));
}

int get_Max(int index, int start, int end)
{
	if (start > b || end < a)				// 구간 벗어난 경우에는 0 출력 (1 <= n <= 1000000000)
		return 0;
	if (start >= a && end <= b)				// 구간 내부에 존재 시 바로 최댓값
		return ans[1][index];
	return max(get_Max(index * 2, start, (start + end) / 2), get_Max(index * 2 + 1, (start + end) / 2 + 1, end));
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
		cin >> A[i];
	init_Min(1, 1, N);
	init_Max(1, 1, N);

	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		cout << get_Min(1, 1, N) << " " << get_Max(1, 1, N) << "\n";
	}
	return 0;
}