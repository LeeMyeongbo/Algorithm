#include <iostream>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define MAX 1000000000
using namespace std;

int TC, N, M, W, S, E, T, map[501][501];
long long weight_sum[501];

bool Bellman()				// �������� 1�� �����̶� ���� (2��, 3������ �ֵ� ��. �ϸ��� ����)
{
	fill(weight_sum, weight_sum + N + 1, MAX);
	weight_sum[1] = 0;		// �������� 0���� �ϰ� ����
												// edge relaxation ����
	for (int i = 0; i < N - 1; i++)				// start�� end ���� ���� ���� �� end ������ ����ġ �� �ּڰ����� ���� => N - 1�� �ݺ�
		for (int start = 1; start <= N; start++)
			for (int end = 1; end <= N; end++)	
				if (map[start][end] != MAX && weight_sum[start] != MAX)
					weight_sum[end] = min(weight_sum[end], weight_sum[start] + map[start][end]);
	
	for(int start = 1; start <= N; start++)		// ������ N��°�� end ������ ����ġ �� �ּҷ� ������ ��
		for (int end = 1; end <= N; end++) {
			if (map[start][end] != MAX) {
				long long Min = min(weight_sum[end], weight_sum[start] + map[start][end]);
				if (Min != weight_sum[end])		// end ������ ����ġ �� �ּڰ��� �� ���ŵ� ��� �ش� end ������ ����Ŭ�� ����
					return true;
			}
		}
	return false;
}

int main()
{
	FAST;
	cin >> TC;
	for (int t = 1; t <= TC; t++) {
		cin >> N >> M >> W;
		for (int i = 1; i <= N; i++)
			fill(map[i], map[i] + N + 1, MAX);

		for (int e = 0; e < M; e++) {
			cin >> S >> E >> T;
			map[S][E] = min(map[S][E], T);
			map[E][S] = min(map[E][S], T);
		}
		for (int w = 0; w < W; w++) {
			cin >> S >> E >> T;
			map[S][E] = -T;
		}
		if (Bellman())
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}