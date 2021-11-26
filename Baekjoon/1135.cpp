#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N, people[50];			// people : �� �������� ����� ��� ��ȣ

int Solve(int upper)		// upper : ��� ��ȣ
{
	vector<int> tmp;
	for (int i = 1; i < N; i++) {
		if (people[i] == upper)			// �Ű� ������ ���޹��� ��� ��ȣ�� ���� ������ ��� ��ȣ�� ���� ���
			tmp.push_back(Solve(i));	// ���� ������ ���� ��� ���� ���� Ž�� �� tmp�� ��ȯ�� ����
	}

	// �� �ڽ� Ʈ���� ��(=�� ���� ������ �� �� ���� �����鿡�� ���ϴ� �� �ɸ��� �ð�) ������������ ���� (���� ���� �ð��� �ɸ��� ������ �켱 ����)
	sort(tmp.begin(), tmp.end(), greater<int>());

	int Max = 0;
	for (int i = 0; i < tmp.size(); i++) {
		tmp[i] += (i + 1);		// ���� �����鸶�� �� �� ���ϴ� �� 1�о� �����̰� �߻�
		if (Max < tmp[i])
			Max = tmp[i];		// ������ �ð����� ���ļ� ���� ���� �ð��� �ɸ��� �ڽ� Ʈ�� ���� �ٷ� ���� ��ȯ��
	}

	return Max;
}

int main()
{
	if (!scanf("%d", &N))
		return 1;
	for (int i = 0; i < N; i++)
		if (!scanf("%d", people + i))
			return 1;
	
	printf("%d\n", Solve(0));
	return 0;
}