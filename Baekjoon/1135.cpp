#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N, people[50];			// people : 각 직원마다 저장된 상사 번호

int Solve(int upper)		// upper : 상사 번호
{
	vector<int> tmp;
	for (int i = 1; i < N; i++) {
		if (people[i] == upper)			// 매개 변수로 전달받은 상사 번호랑 현재 직원의 상사 번호가 같을 경우
			tmp.push_back(Solve(i));	// 현재 직원을 상사로 삼는 부하 직원 탐색 및 tmp에 반환값 저장
	}

	// 각 자식 트리의 값(=각 부하 직원들 및 그 예하 직원들에게 전하는 데 걸리는 시간) 내림차순으로 정렬 (가장 많은 시간이 걸리는 쪽으로 우선 전함)
	sort(tmp.begin(), tmp.end(), greater<int>());

	int Max = 0;
	for (int i = 0; i < tmp.size(); i++) {
		tmp[i] += (i + 1);		// 부하 직원들마다 한 명씩 전하는 데 1분씩 딜레이가 발생
		if (Max < tmp[i])
			Max = tmp[i];		// 딜레이 시간까지 합쳐서 가장 오랜 시간이 걸리는 자식 트리 값이 바로 최종 반환값
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