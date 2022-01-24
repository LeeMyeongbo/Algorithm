#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int L, C;
char word, password[16];
vector<char> words;

/*	DFS �ܰ�
	1. üũ��
	2. ���������� Ȯ��
	3. ����� �� ��ȸ
		4. �� ����� �� �� �� �ִ��� Ȯ��
			5. �� �� ������ ��
	6. üũ�ƿ�
*/

void DFS(int depth, int cur, int consonant, int vowel)
{
	// 1. üũ�� (���⼭�� ���������� �� Ž�� ���� ���� ����)
	if (depth >= 0 && cur >= 0)
		password[depth] = words[cur];

	// 2. ���������� Ȯ�� (���⼭�� ��ȣ ���̰� L�� �Ǳ⸸ �ϸ� ��������!)
	if (depth == L - 1) {
		if (vowel >= 1 && consonant >= 2)	// �ϼ��� ��ȣ�� ����, ���� ���� �����ϸ� ���
			printf("%s\n", password);
		return;
	}

	// 3 ~ 5. ����� �� ���ǰ� �� �� ������ �� (�� ������ �̹� ������ ����, ���� ���� ������ ����)
	for (int i = cur + 1; i < C; i++) {
		if (words[i] == 'a' || words[i] == 'e' || words[i] == 'i' || words[i] == 'o' || words[i] == 'u')
			DFS(depth + 1, i, consonant, vowel + 1);
		else
			DFS(depth + 1, i, consonant + 1, vowel);
	}

	// 6. üũ�ƿ� (���⼭�� ���������� ����Ǿ��� ���� ����)
	if (depth >= 0 && cur >= 0)
		password[depth] = 0;
}

int main()
{
	cin >> L >> C;
	for (int i = 0; i < C; i++) {
		cin >> word;
		words.push_back(word);
	}
	sort(words.begin(), words.end());		// ���� �������� ����

	/*
	for (int i = 0; i < C; i++) {			// starting point�� C��
		if (words[i] == 'a' || words[i] == 'e' || words[i] == 'i' || words[i] == 'o' || words[i] == 'u')
			DFS(0, i, 0, 1);
		else
			DFS(0, i, 1, 0);
	} */
	
	DFS(-1, -1, 0, 0);

	return 0;
}