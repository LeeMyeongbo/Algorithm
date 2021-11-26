#include <iostream>
#include <vector>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, C, S, Sum, partial_sum[200001], ans[200000];		// partial_sum[i] : ������ i�� ������ ũ�� �� (ũ�⸦ ������������ �������� ��)
vector<pair<pair<int, int>, int>> balls, tmp;			// tmp : ũ�� ������������ ���� �� ���� ũ�Ⱑ �����ؼ� ���� �� �ӽ� �����

int main()
{
	FAST;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> C >> S;
		balls.push_back({ {S, C}, i });					// ((ũ��, ����), ��ȣ)�� ����
	}
	sort(balls.begin(), balls.end());					// �Է¹��� ������ ũ�� ������������ ����
	
	tmp.push_back(balls[0]);
	for (int i = 1; i < balls.size(); i++) {
		int size = balls[i].first.first;
		int color = balls[i].first.second;
		int index = balls[i].second;

		if (size != tmp.back().first.first) {			// ���� ���� ũ�Ⱑ ���� ���� ũ��� ���� �ʴٸ�
			while (!tmp.empty()) {						// tmp ������ ���鼭 ��ü �� �� partial_sum ����
				int s = tmp.back().first.first;
				int c = tmp.back().first.second;
				partial_sum[c] += s;
				Sum += s;
				tmp.pop_back();
			}
		}
		ans[index] = Sum - partial_sum[color];			// ��ü ũ�� �տ��� ������ ���� ������ ũ�� ���� �� ���� ��
		tmp.push_back(balls[i]);
	}
	for (int i = 0; i < N; i++)
		cout << ans[i] << "\n";
	
	return 0;
}