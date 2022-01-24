#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct compare {
	bool operator()(pair<long long, long long> p1, pair<long long, long long> p2)
	{
		if (p1.second < p2.second || (p1.second == p2.second && p1.first > p2.first))
			return true;			// 가격 높은 순대로 나오도록 + 가격 같다면 무게 작은 순대로 나오도록 함
		return false;
	}
};
int N, K;
long long C[300000], m, v, Ans;
vector<pair<long long, long long>> jewel;		// (무게, 가격)으로 저장
priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, compare> pq;

long long solve()
{
	sort(C, C + K);
	sort(jewel.begin(), jewel.end());
	int jdx = 0;

	for (int i = 0; i < K; i++) {
		while (jdx < N && jewel[jdx].first <= C[i])
			pq.push(jewel[jdx++]);				// 현재 가방이 감당할 수 있는 무게면 계속 저장
		
		if (!pq.empty()) {
			Ans += pq.top().second;				// 반복문 돌며 pop할 때마다 현재 가방이 담을 수 있는 최대 가격이 나옴
			pq.pop();
		}
	}

	return Ans;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		cin >> m >> v;
		jewel.push_back({ m, v });
	}
	for (int i = 0; i < K; i++)
		cin >> C[i];

	cout << solve();
	return 0;
}