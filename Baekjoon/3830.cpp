#include <iostream>
#include <vector>
using namespace std;

int N, M, a, b, w;
pair<int, long long> U[100001];			// (����� ��������, ���� �������� ���� ����)�� ���� (������������ �־������� ���� �� ���� ����)
char choice;							// U[i] = (j, w) ==> i���� �������� = j�� && i���� ���� = j���� ���� + w

pair<int, long long> Update(int n)
{
	if (U[n].first == n)				// ���������� ���� �� (U[n].second = 0) �ٷ� U[n] ����
		return U[n];
	
	pair<int, long long> p = Update(U[n].first);
	U[n].first = p.first, U[n].second += p.second;
	return U[n];
}

void Union(int v1, int v2, long long gap)		// v1�� �������� -> v2�� �������� ����
{
	pair<int, long long> r1 = Update(v1);		// r1 = (v1�� ��������, v1�� ���� - v1�� ���������� ����)
	pair<int, long long> r2 = Update(v2);		// r2 = (v2�� ��������, v2�� ���� - v2�� ���������� ����)

	U[r2.first] = { r1.first, r1.second - r2.second + gap };	// �׻� ���������� �������� ���� ���� ����ؾ� ��!
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	while (1) {
		cin >> N >> M;
		if (!N)
			return 0;

		for (int i = 1; i <= N; i++)
			U[i] = { i, 0 };

		while (M--) {
			cin >> choice;
			if (choice == '!') {
				cin >> a >> b >> w;
				Union(a, b, (long long)w);
			}
			else {
				cin >> a >> b;
				if (Update(a).first == Update(b).first)
					cout << U[b].second - U[a].second << "\n";
				else
					cout << "UNKNOWN\n";
			}
		}
	}
}