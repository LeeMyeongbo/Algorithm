#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>			// �켱���� ť 2���� Ȱ���Ͽ� �ذ�

using namespace std;

int N, num, ans[100000];
priority_queue<int> q1;									// ������������ ���� �̾Ƴ��� �켱���� ť q1
priority_queue<int, vector<int>, greater<int>> q2;		// ������������ ���� �̾Ƴ��� �켱���� ť q2

int main()
{
	if (!scanf("%d", &N))
		return 1;
	for (int i = 0; i < N; i++) {
		if (!scanf("%d", &num))
			return 1;
		if (q1.empty())
			q1.push(num);					// �� ó�� q1�� ����ִٸ� �� ����
		else {
			if (num > q1.top())				// �Է¹��� num�� q1���� ���� ū ���ں��� ũ�ٸ� q2�� ����
				q2.push(num);
			else
				q1.push(num);
			int s = q1.size() - q2.size();

			if (s > 1) {					// q1�� ũ�Ⱑ q2�� ũ�� + 1 ���� Ŭ ��� q1���� ���� ū ���ڸ� ���� q2�� ����
				int tmp = q1.top();
				q1.pop();
				q2.push(tmp);
			}
			else if (s * (-1) >= 1) {		// q2�� ũ�Ⱑ q1�� ũ�� + 1���� ũ�ų� ���� ��� q2���� ���� ���� ���ڸ� ���� q1�� ����
				int tmp = q2.top();
				q2.pop();
				q1.push(tmp);
			}
		}
		ans[i] = q1.top();					// q1���� ���� ū ���ڰ� �ٷ� ������ ���ؾ� �ϴ� �߰����� �ش�
	}

	for (int i = 0; i < N; i++)
		printf("%d\n", ans[i]);

	return 0;
}