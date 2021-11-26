#include <iostream>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, a, b, w, parent[100001];
long long weight[100001];
char choice;

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

}

int main()
{
	FAST;
	while (1) {
		cin >> N >> M;
		if (!N)
			return 0;
		for (int i = 1; i <= N; i++)
			parent[i] = i;
		cin >> choice;
		if (choice == '!') {
			cin >> a >> b >> w;

		}
	}
}