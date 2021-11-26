#include <iostream>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, island1, island2, parent[300001];

int Find(int n)
{
	if (parent[n] == n)
		return n;
	return parent[n] = Find(parent[n]);
}
void Union(int n1, int n2)
{
	n1 = Find(n1);
	n2 = Find(n2);
	if (n1 > n2)
		swap(n1, n2);
	parent[n2] = n1;
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 1; i <= N; i++)
		parent[i] = i;

	for (int i = 0; i < N - 2; i++) {
		cin >> island1 >> island2;
		Union(island1, island2);
	}

	for (int i = 2; i <= N; i++) {
		if (Find(i) == Find(1))
			continue;
		cout << 1 << " " << i;
		return 0;
	}
}