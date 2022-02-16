#include <iostream>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int M, N, map[700][700], one[1400], two[1400], num[3];		// one : 1이 시작하는 위치에, two : 2가 시작하는 위치에 +1씩

void solve()									// 사실 one, two 이렇게 나누지 말고 그냥 1, 2가 시작하는 위치에 +1씩 해서 풀어도 됨
{
	for (int i = 0; i < 2 * M - 2; i++) {		// 한 번 1 또는 2가 시작되면 그 뒤로는 모두 1 또는 2가 있으니
		one[i + 1] += one[i];
		two[i + 1] += two[i];
	}
	for (int i = 0; i < 2 * M - 1; i++)			// 1과 2가 중복되는 칸은 제거
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