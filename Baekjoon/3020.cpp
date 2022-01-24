#include <iostream>
#include <algorithm>
using namespace std;

int N, H, h, seok[500001], jong[500001], height[500001], Ans;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> H;

	for (int i = 0; i < N; i++) {
		cin >> h;
		if (i % 2)
			jong[H - h + 1]++;			// ������ -> �ε��� �� �ִ� �ּ� ���̿��ٰ� +1
		else							// ��) H=5, ������ ����=2 �� ��, �ּ� ���� 5-2+1=4�� ������ �ε��� �� �����Ƿ� [4]�� +1
			seok[h]++;					// ���� -> �ε��� �� �ִ� �ִ� ���̿��ٰ� +1
	}									// ��) H=5, ���� ����=2�� ��, �ִ� ���� 2�϶������� �ε��� �� �����Ƿ� [2]�� +1

	for (int i = H; i > 1; i--)
		seok[i - 1] += seok[i];			// ������ �ε����� �۾������� ������ ����
	for (int i = 1; i < H; i++)
		jong[i + 1] += jong[i];			// �������� �ε����� Ŀ������ ������ ����

	for (int i = 1; i <= H; i++)
		height[i] = seok[i] + jong[i];

	sort(height + 1, height + H + 1);

	cout << height[1] << ' ';
	for (int i = 1; i <= H; i++)
		if (height[i] == height[1])
			Ans++;
	
	cout << Ans;
	return 0;
}