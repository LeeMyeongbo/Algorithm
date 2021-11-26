#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>			// 우선순위 큐 2개를 활용하여 해결

using namespace std;

int N, num, ans[100000];
priority_queue<int> q1;									// 내림차순으로 수를 뽑아내는 우선순위 큐 q1
priority_queue<int, vector<int>, greater<int>> q2;		// 오름차순으로 수를 뽑아내는 우선순위 큐 q2

int main()
{
	if (!scanf("%d", &N))
		return 1;
	for (int i = 0; i < N; i++) {
		if (!scanf("%d", &num))
			return 1;
		if (q1.empty())
			q1.push(num);					// 맨 처음 q1이 비어있다면 수 삽입
		else {
			if (num > q1.top())				// 입력받은 num이 q1에서 가장 큰 숫자보다 크다면 q2에 삽입
				q2.push(num);
			else
				q1.push(num);
			int s = q1.size() - q2.size();

			if (s > 1) {					// q1의 크기가 q2의 크기 + 1 보다 클 경우 q1에서 가장 큰 숫자를 빼서 q2에 삽입
				int tmp = q1.top();
				q1.pop();
				q2.push(tmp);
			}
			else if (s * (-1) >= 1) {		// q2의 크기가 q1의 크기 + 1보다 크거나 같을 경우 q2에서 가장 작은 숫자를 빼서 q1에 삽입
				int tmp = q2.top();
				q2.pop();
				q1.push(tmp);
			}
		}
		ans[i] = q1.top();					// q1에서 가장 큰 숫자가 바로 동생이 말해야 하는 중간값에 해당
	}

	for (int i = 0; i < N; i++)
		printf("%d\n", ans[i]);

	return 0;
}