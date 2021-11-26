#include <iostream>
#include <stack>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, height;
long long ans;
stack<pair<int, int>> s;			// (Ű, ��� ��)�� ����

int main()
{
	FAST;
	cin >> N >> height;
	s.push({ height, 1 });

	for (int i = 1; i < N; i++) {	// ��� ����� ����(�ε����� ���� ����)�� �ٶ󺸰� �ִٰ� �����ϰ� ����
		cin >> height;
		while (!s.empty() && s.top().first < height) {	// stack top�� ��ġ�� ����� Ű�� height���� ���� ��� 
			ans += s.top().second;						// stack top�� �ִ� ����� ���� ����
			s.pop();									// Ű�� ���� ���� ����� ��Ÿ���ų� stack�� �� ������ �ݺ�
		}
		if (!s.empty() && s.top().first == height) {	// ���� stack top�� ��ġ�� ����� Ű�� height�� ���� ���
			ans += s.top().second;						// �� ����� ����ŭ ������
			s.top().second++;							// top�� ��� �� +1
			if (s.size() > 1)							// ���ʿ� Ű�� �� ū ����� �ִٸ� �� ������� �� �� �����Ƿ� +1
				ans++;
		}
		else {							// �� ���� ��� (stack�� ����ų� stack top�� ��ġ�� ��� Ű�� height���� Ŭ ���)
			if (!s.empty())				// ������ ���� �ʾҴٸ� stack top�� ��ġ�� ��� Ű�� height���� ũ�ٴ� �ǹ�
				ans++;					// �̷� ���� �ٷ� ���� ��� 1��ۿ� �� ���� ����̹Ƿ� +1
			s.push({ height, 1 });
		}
	}
	cout << ans;
	return 0;
}