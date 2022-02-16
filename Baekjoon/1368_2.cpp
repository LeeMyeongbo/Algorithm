#include <iostream>
#include <queue>
using namespace std;

int N, P[301][301], parent[301];			// 우물을 직접 파는 경우를 0번 우물에 연결하는 것으로 생각
priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> q;
											// 간선을 가중치 오름차순으로 뽑기 위해 우선순위 큐 활용
int Find(int n)
{
	if (parent[n] == n)
		return n;
	return parent[n] = Find(parent[n]);
}

bool Union(int n1, int n2)
{
	n1 = Find(n1);
	n2 = Find(n2);
	if (n1 == n2)
		return false;
	if (n1 > n2)
		swap(n1, n2);
	parent[n2] = n1;
	return true;
}

int Solve()
{
	int ans = 0;
	while (!q.empty()) {
		bool complete = true;
		int weight = q.top().first;
		pair<int, int> p = q.top().second;
		q.pop();

		if (Union(p.first, p.second))
			ans += weight;

		for (int i = 1; i <= N; i++)
			if (Find(i)) {				// i번 우물이 속한 집합의 최고 조상 우물 번호가 0이 아닌 경우는 아직 물을 대지 않은 것!
				complete = false;
				break;
			}
		if (complete)
			return ans;
	}
	return -1;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> P[0][i];
		parent[i] = i;
	}
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			cin >> P[i][j];

	for (int i = 0; i < N; i++)
		for (int j = i + 1; j <= N; j++)
			q.push({ P[i][j], {i, j} });

	cout << Solve();

	return 0;
}