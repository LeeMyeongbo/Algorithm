#include <iostream>
#include <map>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, card, ans[500000];
map<int, int> m;

int main()
{
	FAST;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> card;
		if (!m.count(card))
			m.insert({ card, 1 });
		else
			m[card]++;
	}

	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> card;
		ans[i] = m[card];
	}
	for (int i = 0; i < M; i++)
		cout << ans[i] << " ";

	return 0;
}