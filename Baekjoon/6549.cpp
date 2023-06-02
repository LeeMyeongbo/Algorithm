#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

int n, S;
unsigned int leftTree[1 << 18], rightTree[1 << 18];     // 최솟값을 저장하는 IndexedTree

int main()                                              // IndexedTree를 활용한 풀이
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    while (true)
    {
        cin >> n;
        if (!n)
            return 0;

        register long long rect = 0;
        memset(leftTree, UINT32_MAX, sizeof(leftTree));
        memset(rightTree, UINT32_MAX, sizeof(rightTree));
        S = 1 << (int)ceil(log2(n));
        
        for (register int h = 0; h < n; h++)
        {
            register int idx = S + h;
            cin >> rightTree[idx];
            
            idx >>= 1;
            while (idx)
            {
                rightTree[idx] = min(rightTree[idx << 1], rightTree[(idx << 1) + 1]);
                idx >>= 1;
            }
        }

        for (register int h = 0; h < n; h++)
        {
            register int idx = S + h;
            register unsigned int curHeight = rightTree[idx];

            leftTree[idx] = curHeight;
            idx >>= 1;
            while (idx)
            {
                leftTree[idx] = min(leftTree[idx << 1], leftTree[(idx << 1) + 1]);
                idx >>= 1;
            }

            // 현재 위치보다 왼쪽에 있는 직사각형들(현재 직사각형 포함) 중 현재 높이보다 작으면서 제일 오른쪽에 있는 직사각형 위치 구함
            idx = 1;
            if (leftTree[1] < curHeight)
            {
                while (idx < S)
                {
                    if (leftTree[(idx << 1) + 1] < curHeight)     // 오른쪽 서브트리로 우선적으로 이동
                        idx = (idx << 1) + 1;
                    else
                        idx <<= 1;
                }
            }
            register int leftEnd = idx == 1 ? -1 : idx - S;

            idx = S + h;
            rightTree[idx] = UINT32_MAX;
            idx >>= 1;
            while (idx)
            {
                rightTree[idx] = min(rightTree[idx << 1], rightTree[(idx << 1) + 1]);
                idx >>= 1;
            }

            // 현재 위치보다 오른쪽에 있는 직사각형들 중 현재 높이보다 작으면서 제일 왼쪽에 있는 직사각형 위치 구함
            idx = 1;
            if (rightTree[1] < curHeight)
            {
                while (idx < S)
                {
                    if (rightTree[idx << 1] < curHeight)          // 왼쪽 서브트리로 우선적으로 이동
                        idx <<= 1;
                    else
                        idx = (idx << 1) + 1;
                }
            }
            register int rightEnd = idx == 1 ? n : idx - S;

            rect = max(rect, (long long)curHeight * (rightEnd - leftEnd - 1));
        }

        cout << rect << '\n';
    }
}
