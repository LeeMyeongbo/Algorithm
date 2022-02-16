#include <iostream>
#include <stack>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, height;
long long ans;
stack<pair<int, int>> s;			// (키, 사람 수)로 저장

int main()
{
	FAST;
	cin >> N >> height;
	s.push({ height, 1 });

	for (int i = 1; i < N; i++) {	// 모든 사람이 왼쪽(인덱스가 작은 방향)을 바라보고 있다고 생각하고 접근
		cin >> height;
		while (!s.empty() && s.top().first < height) {	// stack top에 위치한 사람의 키가 height보다 작은 경우 
			ans += s.top().second;						// stack top에 있는 사람의 수를 더함
			s.pop();									// 키가 작지 않은 사람이 나타나거나 stack이 빌 때까지 반복
		}
		if (!s.empty() && s.top().first == height) {	// 이후 stack top에 위치한 사람의 키가 height와 같을 경우
			ans += s.top().second;						// 그 사람의 수만큼 더해줌
			s.top().second++;							// top의 사람 수 +1
			if (s.size() > 1)							// 왼쪽에 키가 더 큰 사람이 있다면 그 사람까지 볼 수 있으므로 +1
				ans++;
		}
		else {							// 그 외의 경우 (stack이 비었거나 stack top에 위치한 사람 키가 height보다 클 경우)
			if (!s.empty())				// 스택이 비지 않았다면 stack top에 위치한 사람 키가 height보다 크다는 의미
				ans++;					// 이런 경우는 바로 앞의 사람 1명밖에 못 보는 경우이므로 +1
			s.push({ height, 1 });
		}
	}
	cout << ans;
	return 0;
}