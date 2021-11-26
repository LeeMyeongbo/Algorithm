#include <iostream>
#include <map>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

map<string, int> m;
int T, F, parent[300001], relation[300001];
string str1, str2;

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
	if (n1 == n2)
		return;
	if (n1 > n2)
		swap(n1, n2);
	parent[n2] = n1;
	relation[n1] += relation[n2];
}

int main()
{
	FAST;
	cin >> T;
	for (int t = 0; t < T; t++) {
		cin >> F;
		int num = 0;
		for (int i = 0; i <= 300000; i++) {
			parent[i] = i;
			relation[i] = 1;
		}

		for (int f = 0; f < F; f++) {
			cin >> str1 >> str2;
			if (!m.count(str1))
				m.insert({ str1, num++ });		// 사람 이름을 key로 하는 map을 통해 해당 친구가 이미 있는지 확인
			if (!m.count(str2))
				m.insert({ str2, num++ });

			Union(m[str1], m[str2]);
			cout << relation[Find(m[str1])] << "\n";
		}
		m.clear();
	}
	return 0;
}