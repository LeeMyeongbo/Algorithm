#include <iostream>
#include <cstring>
#define MAX 1000000
using namespace std;

int N, parent[MAX + 1], know[MAX + 1], a, b;
char c;

int Find(int n)
{
	if (parent[n] == n)
		return n;
	return parent[n] = Find(parent[n]);
}

void Union(int n1, int n2) 
{
	n1 = Find(n1);
	n2 = Find(n2);					// n1�� n2�� ���� �θ� ����, ����
	if (n1 == n2)					// �׻� ���� �θ� ���ٸ� �̹� ���� ���տ� ���� ���̹Ƿ� �ٷ� �Լ� �����ϴ� ���� �ʿ�!
		return;
	if (n1 > n2)
		swap(n1, n2);				// �׻� n1 < n2 �� �����ǵ��� �ϱ�!
	parent[n2] = n1;
	know[n1] += know[n2];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;

	for (int i = 1; i <= MAX; i++) {
		parent[i] = i;
		know[i] = 1;
	}
	for (int i = 0; i < N; i++) {
		cin >> c;
		if (c == 'I') {
			cin >> a >> b;
			Union(a, b);
		}
		else {
			cin >> a;
			cout << know[Find(a)] << "\n";
		}
	}
	return 0;
}