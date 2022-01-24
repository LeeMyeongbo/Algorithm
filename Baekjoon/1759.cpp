#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int L, C;
char word, password[16];
vector<char> words;

/*	DFS 단계
	1. 체크인
	2. 목적지인지 확인
	3. 연결된 곳 순회
		4. 각 연결된 곳 갈 수 있는지 확인
			5. 갈 수 있으면 감
	6. 체크아웃
*/

void DFS(int depth, int cur, int consonant, int vowel)
{
	// 1. 체크인 (여기서는 전역변수에 현 탐색 중인 문자 저장)
	if (depth >= 0 && cur >= 0)
		password[depth] = words[cur];

	// 2. 목적지인지 확인 (여기서는 암호 길이가 L이 되기만 하면 목적지임!)
	if (depth == L - 1) {
		if (vowel >= 1 && consonant >= 2)	// 완성된 암호가 자음, 모음 조건 충족하면 출력
			printf("%s\n", password);
		return;
	}

	// 3 ~ 5. 연결된 곳 살피고 갈 수 있으면 감 (이 문제는 이미 정렬해 놓음, 자음 모음 개수만 따짐)
	for (int i = cur + 1; i < C; i++) {
		if (words[i] == 'a' || words[i] == 'e' || words[i] == 'i' || words[i] == 'o' || words[i] == 'u')
			DFS(depth + 1, i, consonant, vowel + 1);
		else
			DFS(depth + 1, i, consonant + 1, vowel);
	}

	// 6. 체크아웃 (여기서는 전역변수에 저장되었던 문자 지움)
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
	sort(words.begin(), words.end());		// 문자 오름차순 정렬

	/*
	for (int i = 0; i < C; i++) {			// starting point가 C개
		if (words[i] == 'a' || words[i] == 'e' || words[i] == 'i' || words[i] == 'o' || words[i] == 'u')
			DFS(0, i, 0, 1);
		else
			DFS(0, i, 1, 0);
	} */
	
	DFS(-1, -1, 0, 0);

	return 0;
}