#include <iostream>
#include <queue>
using namespace std;

int N, W[300], P[300][300], parent[300];
bool done[300];					// ���� ��� true
priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> q;

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

	parent[n2] = n1;
	if (done[n2])
		done[n1] = true;		// n2 ���տ� ���� ��� �ִٸ� n1 ���տ��� ���� ����
	return true;
}

int Solve()
{
	int ans = 0;
	while (!q.empty()) {
		int weight = q.top().first;
		int n1 = q.top().second.first;
		int n2 = q.top().second.second;
		q.pop();

		bool complete = true;
		// n1 �Ǵ� n2 ���տ� ���� ��� ���� �ʰ� n1�� n2�� ���ų� ���� �ٸ� ���տ� ���� ���¿��� ���� �������� �Ǿ��ٸ�
		if ((!done[Find(n1)] || !done[Find(n2)]) && (n1 == n2 || Union(n1, n2))) {
			ans += weight;
			if (n1 == n2)
				done[Find(n1)] = true;
		}

		for(int i = 0; i < N; i++)
			if (!done[Find(i)]) {		// i�� �칰�� ���� ���տ��� ���� ���� ���� �ʾ��� ���
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
	for (int i = 0; i < N; i++) {
		cin >> W[i];
		parent[i] = i;
	}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			cin >> P[i][j];
			if (i == j)
				P[i][j] = W[i];
		}
	for (int i = 0; i < N; i++)
		for (int j = i; j < N; j++)
			q.push({ P[i][j], {i, j} });
	cout << Solve();

	return 0;
}