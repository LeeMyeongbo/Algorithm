#include <iostream>
#include <vector>
using namespace std;

int test_case, T, N, x, y, pre[1001], cycle_start;		// cycle_start : ����Ŭ�� ���ʷ� ���۵Ǵ� ����, pre[i] : i�� ������ ���� ����
bool cycle[1001];							// ����Ŭ�� �̷�� ���� true�� ǥ��
vector<int> graph[1001];

bool dfs(int c, int p)						// c : ���� ����, p : �ٷ� ���� ����
{
	pre[c] = p;
	bool is_cycle = false;

	for (int i : graph[c]) {
		if (pre[i] == -1) {					// �湮�� �� ���� ���� �湮 ��
			bool cycling = dfs(i, c);
			if (cycling)
				cycle[c] = is_cycle = true;
		}
		else if (pre[i] > -1 && i != p && !cycle[i]) {	// �湮�� ���� �ִµ� �ٷ� ������ �湮�� ������ �ƴ� �� -> ����Ŭ �߰�!
			cycle[c] = is_cycle = true;					// cycle�� ���Ѵٰ� ǥ���� �� ���� �����̾���� cycle_start�� ���� �ȵ�!
			cycle_start = i;				// ����Ŭ ���� ���� ����
		}
	}
	if (cycle_start == c)					// ����Ŭ ���� ���� �������� ��� ���������� ����Ŭ Ž�� �Ϸ�!
		is_cycle = false;
	return is_cycle;
}

int main(int argc, char** argv)
{
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		cin >> N;
		fill(pre, pre + N + 1, -1);
		fill(cycle, cycle + N + 1, false);

		for (int i = 0; i < N; i++) {
			cin >> x >> y;
			graph[x].push_back(y);
			graph[y].push_back(x);
		}
		dfs(1, 0);

		int ans = 0;
		for (int i = 1; i <= N; i++)
			if (cycle[i])
				ans++;

		cout << "#" << test_case << " " << ans << endl;
		cycle_start = 0;
		for (int i = 1; i <= N; i++)
			graph[i].clear();
	}
	return 0;
}