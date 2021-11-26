#include <iostream>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, a, b, A[100001], ans[2][400004];		// ans[0][i] : �ּڰ�, ans[1][i] : �ִ�

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
	if (start > b || end < a)				// ������ ��� ��쿡�� 10^9 + 1 ��� (1 <= n <= 1000000000)
		return 1000000001;
	if (start >= a && end <= b)				// ���� ���ο� �����ϸ� �ٷ� �ش� ������ �ּڰ� ���
		return ans[0][index];
	return min(get_Min(index * 2, start, (start + end) / 2), get_Min(index * 2 + 1, (start + end) / 2 + 1, end));
}

int get_Max(int index, int start, int end)
{
	if (start > b || end < a)				// ���� ��� ��쿡�� 0 ��� (1 <= n <= 1000000000)
		return 0;
	if (start >= a && end <= b)				// ���� ���ο� ���� �� �ٷ� �ִ�
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