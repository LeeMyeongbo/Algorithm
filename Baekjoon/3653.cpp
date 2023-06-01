#include <iostream>
#include <vector>
#include <cstring>
#define S (1 << 18)
using namespace std;

int movieIdx[100001];   // movieIdx[i] : i번 영화가 몇 번 index에 위치하고 있는지 저장 (위로 갈수록 index가 커짐)
int cntTree[1 << 19];

int search(int index, int left, int right, int& r1, int& r2)
{
    if (left > r2 || right < r1)
        return 0;

    if (left >= r1 && right <= r2)
        return cntTree[index];

    int mid = (left + right) >> 1;
    return search(index << 1, left, mid, r1, r2) + search((index << 1) + 1, mid + 1, right, r1, r2);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    register int t, n, m, movie;
    cin >> t;

    while (t--)
    {
        cin >> n >> m;

        register int endIdx = n - 1;
        vector<int> ans;

        for (register int i = 1; i <= n; i++)
            movieIdx[i] = n - i;

        for (register int i = 0; i < n; i++)
        {
            register int index = S + i;
            while (index)
            {
                ++cntTree[index];
                index >>= 1;
            }
        }

        while (m--)
        {
            cin >> movie;
            ans.emplace_back(search(1, 0, S - 1, movieIdx[movie], endIdx) - 1);

            register int index = S + movieIdx[movie];
            while (index)
            {
                --cntTree[index];
                index >>= 1;
            }

            movieIdx[movie] = ++endIdx;

            index = S + endIdx;
            while (index)
            {
                ++cntTree[index];
                index >>= 1;
            }
        }

        for (int& a : ans)
            cout << a << ' ';
        cout << '\n';

        memset(cntTree, 0, sizeof(cntTree));
    }

    return 0;
}
