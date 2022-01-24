#include <iostream>
using namespace std;

int n, m, a, b, cal, U[1000001];

int Find(int v)
{
	if (v == U[v])
		return v;
	return U[v] = Find(U[v]);
}

void Union(int v1, int v2)
{
	v1 = Find(v1);
	v2 = Find(v2);
	U[v1] = U[v2];
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;
	for (int i = 0; i <= n; i++)
		U[i] = i;

	while (m--) {
		cin >> cal >> a >> b;
		if (!cal)
			Union(a, b);
		else {
			if (Find(a) == Find(b))		// 같은 집합에 속하는지 판별
				cout << "yes\n";
			else
				cout << "no\n";
		}
	}

	return 0;
}
