#include <iostream>
#include <vector>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, C, S, Sum, partial_sum[200001], ans[200000];		// partial_sum[i] : 색깔이 i인 공들의 크기 합 (크기를 오름차순으로 정렬했을 때)
vector<pair<pair<int, int>, int>> balls, tmp;			// tmp : 크기 오름차순으로 정렬 후 같은 크기가 연속해서 나올 때 임시 저장용

int main()
{
	FAST;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> C >> S;
		balls.push_back({ {S, C}, i });					// ((크기, 색깔), 번호)로 저장
	}
	sort(balls.begin(), balls.end());					// 입력받은 공들을 크기 오름차순으로 정렬
	
	tmp.push_back(balls[0]);
	for (int i = 1; i < balls.size(); i++) {
		int size = balls[i].first.first;
		int color = balls[i].first.second;
		int index = balls[i].second;

		if (size != tmp.back().first.first) {			// 현재 공의 크기가 이전 공의 크기와 같지 않다면
			while (!tmp.empty()) {						// tmp 완전히 비우면서 전체 합 및 partial_sum 갱신
				int s = tmp.back().first.first;
				int c = tmp.back().first.second;
				partial_sum[c] += s;
				Sum += s;
				tmp.pop_back();
			}
		}
		ans[index] = Sum - partial_sum[color];			// 전체 크기 합에서 색깔이 같은 공들의 크기 합을 뺀 것이 답
		tmp.push_back(balls[i]);
	}
	for (int i = 0; i < N; i++)
		cout << ans[i] << "\n";
	
	return 0;
}