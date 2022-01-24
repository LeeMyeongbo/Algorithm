#include <iostream>
#include <vector>
using namespace std;

int N, M, a, b, w;
pair<int, long long> U[100001];			// (연결된 기준정점, 기준 정점과의 무게 차이)로 저장 (기준정점에서 멀어질수록 무게 한 번씩 증감)
char choice;							// U[i] = (j, w) ==> i번의 기준정점 = j번 && i번의 무게 = j번의 무게 + w

pair<int, long long> Update(int n)
{
	if (U[n].first == n)				// 기준정점에 도달 시 (U[n].second = 0) 바로 U[n] 리턴
		return U[n];
	
	pair<int, long long> p = Update(U[n].first);
	U[n].first = p.first, U[n].second += p.second;
	return U[n];
}

void Union(int v1, int v2, long long gap)		// v1의 기준정점 -> v2의 기준정점 연결
{
	pair<int, long long> r1 = Update(v1);		// r1 = (v1의 기준정점, v1의 무게 - v1의 기준정점의 무게)
	pair<int, long long> r2 = Update(v2);		// r2 = (v2의 기준정점, v2의 무게 - v2의 기준정점의 무게)

	U[r2.first] = { r1.first, r1.second - r2.second + gap };	// 항상 기준정점을 기준으로 무게 차이 계산해야 함!
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