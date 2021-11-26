#include <iostream>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int M, N, map[700][700], one[1400], two[1400], num[3];		// one : 1�� �����ϴ� ��ġ��, two : 2�� �����ϴ� ��ġ�� +1��

void solve()									// ��� one, two �̷��� ������ ���� �׳� 1, 2�� �����ϴ� ��ġ�� +1�� �ؼ� Ǯ� ��
{
	for (int i = 0; i < 2 * M - 2; i++) {		// �� �� 1 �Ǵ� 2�� ���۵Ǹ� �� �ڷδ� ��� 1 �Ǵ� 2�� ������
		one[i + 1] += one[i];
		two[i + 1] += two[i];
	}
	for (int i = 0; i < 2 * M - 1; i++)			// 1�� 2�� �ߺ��Ǵ� ĭ�� ����
		one[i] -= two[i];
	
	for (int i = M - 1; i >= 0; i--) {
		map[i][0] += one[M - 1 - i];
		map[i][0] += two[M - 1 - i] * 2;
	}
	for (int i = 1; i < M; i++) {
		map[0][i] += one[i + M - 1];
		map[0][i] += two[i + M - 1] * 2;
	}

	for (int i = 1; i < M; i++)
		for (int j = 1; j < M; j++)
			map[i][j] = max(max(map[i][j - 1], map[i - 1][j]), map[i - 1][j - 1]);

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++)
			cout << map[i][j] << " ";
		cout << "\n";
	}
}

int main()
{
	FAST;
	cin >> M >> N;
	for (int i = 0; i < M; i++)
		fill(map[i], map[i] + M, 1);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 3; j++)
			cin >> num[j];
		one[num[0]]++;
		two[num[0] + num[1]]++;
	}

	solve();
	return 0;
}