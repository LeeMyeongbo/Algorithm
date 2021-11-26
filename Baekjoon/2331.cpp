#include <iostream>
#include <vector>
#include <cmath>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int A, P, ans;
vector<int> D;
bool visited[250000];

int Solve()						// 어느 시점에서 사이클이 형성될 수밖에 없음
{
	D.push_back(A);
	visited[A] = true;

	while (1) {
		int cur = D.back();
		int n = 0;
		while (cur) {
			int now = cur % 10;
			n += (int)pow(now, P);
			cur /= 10;
		}
		if (visited[n]) {
			for (int i : D) {
				if (i == n) return ans;
				ans++;
			}
		}
		D.push_back(n);
		visited[n] = true;
	}
}

int main()
{
	FAST;
	cin >> A >> P;
	
	cout << Solve();
	return 0;
}