#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

int n, S, road[100000];
long long tree[262144];         // 2 ^ (ceil(log2(100000)) + 1)

long long build(int index, int left, int right)
{
    if (left == right)
        return tree[index];

    unsigned int mid = (left + right) >> 1;
    return tree[index] = build(index << 1, left, mid) + build((index << 1) + 1, mid + 1, right);
}

long long search(int index, int left, int right, int r1, int r2)
{
    if (left > r2 || right < r1)
        return 0;
    
    if (left >= r1 && right <= r2)
        return tree[index];

    unsigned int mid = (left + right) >> 1;
    return search(index << 1, left, mid, r1, r2) + search((index << 1) + 1, mid + 1, right, r1, r2);
}

void init(int N, int M, int mType[], int mTime[])
{
    n = N;
    for (register unsigned int i = 0; i < N - 1; i++)
        road[i] = mType[i];

    S = 1 << (int)ceil(log2(N - 1));
    for (register unsigned int i = 0; i < N - 1; i++)
        tree[i + S] = mTime[i];

    build(1, 1, S);
}

void destroy()
{
    memset(road, 0, sizeof(road));
    memset(tree, 0, sizeof(tree));
}

void update(int mID, int mNewTime)
{
    register unsigned int idx = S + mID;
    int diff = mNewTime - tree[idx];

    while (idx)
    {
        tree[idx] += diff;
        idx >>= 1;
    }
}

int updateByType(int mTypeID, int mRatio256)
{
    int sum = 0;
    for (register unsigned int i = 0; i < n - 1; i++)
    {
        if (road[i] == mTypeID)
        {
            int val = (tree[S + i] * mRatio256) >> 8;
            update(i, val);
            sum += val;
        }
    }
    return sum;
}

int calculate(int mA, int mB)
{
    if (mA > mB)
        swap(mA, mB);

    return search(1, 1, S, mA + 1, mB);
}
