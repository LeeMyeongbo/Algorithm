#include <iostream>
#include <cmath>
#define MAX 1048576                 // 2^20
using namespace std;

int S, N, M, K;
long long tree[MAX << 1];

// left와 right는 현재 살피고 있는 범위(제일 왼쪽에 있는 리프가 1번, 제일 오른쪽에 있는 리프가 S번)
long long init(int left, int right, int index)
{
    if (left == right) 
        return tree[index];
    
    int mid = left + right >> 1;
    return tree[index] = init(left, mid, index << 1) + init(mid + 1, right, (index << 1) + 1);  // 비트 연산 우선순위 유의
}

// range1 ~ range2 구간의 합을 구한다 가정
long long search(int left, int right, int range1, int range2, int index)
{
    if (left > range2 || right < range1)
        return 0;
    
    if (left >= range1 && right <= range2)
        return tree[index];
    
    int mid = left + right >> 1;
    return search(left, mid, range1, range2, index << 1) + search(mid + 1, right, range1, range2, (index << 1) + 1);
}

// init, search와 달리 buttom-up 방식으로 트리 갱신 (diff는 새로운 값과 기존 값과의 차이)
void update(int index, int diff)
{
    while (index)
    {
        tree[index] += diff;
        index = index >> 1;
    }
}

int main()                          // 인덱스 트리는 포화 이진트리 구조!
{
    cin >> N;
    S = 1 << (int)log2(N) + 1;      // N 이상이면서 N과 가장 가까운 2^k 자연수로 S를 설정
    for (int i = 0; i < N; i++)     // tree[1] ~ tree[S-1] : 내부노드, tree[S] ~ tree[2*S-1] : 리프노드
        cin >> tree[S + i];         // 항상 리프에다가 데이터 저장
    
    init(1, S, 1);

    int choice;
    while (true)
    {
        cout << "1 입력 시 구간합, 2 입력 시 트리 수정 : ";
        cin >> choice;

        if (cin.eof())
            return 0;
        
        if (choice == 1)
        {
            int r1, r2;
            cout << "구간 입력 : ";
            cin >> r1 >> r2;

            cout << search(1, S, r1, r2, 1) << '\n';
        }
        else
        {
            int pos, val;
            cout << "수정할 위치와 값 입력 : ";
            cin >> pos >> val;

            update(pos + S - 1, val - tree[pos + S - 1]);
        }
    }
}