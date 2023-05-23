#include <string>
#include <cstring>
#include <unordered_map>
#define MAXDAY  1000000
using namespace std;

int lazyTree[1 << 21], cnt, depth[12001], anc[12001][11];   // depth[i] : 가계도 상에서 i의 깊이(선조가 0), anc[i][j] : i의 2^j번째 조상
unordered_map<string, int> microbeInfo;

void prop(int& index, int& left, int& right)
{
    if (lazyTree[index])
    {
        if (left != right)
        {
            lazyTree[index << 1] += lazyTree[index];
            lazyTree[(index << 1) + 1] += lazyTree[index];
            lazyTree[index] = 0;
        }
    }
}

void update(int index, int left, int right, int& r1, int& r2)
{
    prop(index, left, right);
    if (left > r2 || right < r1)
        return;

    if (left >= r1 && right <= r2)
    {
        lazyTree[index] += 1;
        if (left != right)
        {
            lazyTree[index << 1] += 1;
            lazyTree[(index << 1) + 1] += 1;
            lazyTree[index] = 0;
        }

        return;
    }

    int mid = (left + right) >> 1;
    update(index << 1, left, mid, r1, r2);
    update((index << 1) + 1, mid + 1, right, r1, r2);
}

int search(int index, int left, int right, int& r1, int& r2)
{
    prop(index, left, right);
    if (left > r2 || right < r1)
        return 0;

    if (left >= r1 && right <= r2)
        return lazyTree[index];

    int mid = (left + right) >> 1;
    return search(index << 1, left, mid, r1, r2) + search((index << 1) + 1, mid + 1, right, r1, r2);
}

int getlca(int v1, int v2)
{
    if (depth[v1] < depth[v2])
        swap(v1, v2);

    register int diff = depth[v1] - depth[v2];
    for (register int i = 0; diff; ++i)
    {
        if (diff & 1)
            v1 = anc[v1][i];
        diff >>= 1;
    }

    if (v1 == v2)
        return v1;

    for (register int i = 10; i >= 0; --i)
    {
        if (anc[v1][i] != anc[v2][i])
        {
            v1 = anc[v1][i];
            v2 = anc[v2][i];
        }
    }

    return anc[v1][0];
}

void init(char mAncestor[], int mDeathday)
{
    microbeInfo.clear();
    memset(lazyTree, 0, sizeof(lazyTree));
    memset(depth, 0, sizeof(depth));
    memset(anc, 0, sizeof(anc));
    cnt = 0;

    register int mBirthday = 0;
    microbeInfo.insert({ string(mAncestor), 0 });
    update(1, 0, MAXDAY, mBirthday, mDeathday);

    return;
}

int add(char mName[], char mParent[], int mBirthday, int mDeathday)
{
    string child(mName), parent(mParent);
    microbeInfo.insert({ child, ++cnt });

    register int pa = microbeInfo[parent], ch = microbeInfo[child];

    depth[ch] = depth[pa] + 1;
    anc[ch][0] = pa;

    for (register int i = 1; i < 11; ++i)
        anc[ch][i] = anc[anc[ch][i - 1]][i - 1];

    update(1, 0, MAXDAY, mBirthday, mDeathday);

    return depth[ch];
}

int distance(char mName1[], char mName2[])
{
    register int m1 = microbeInfo[string(mName1)], m2 = microbeInfo[string(mName2)];
    register int lca = getlca(m1, m2);

    return depth[m1] + depth[m2] - 2 * depth[lca];
}

int count(int mDay)
{
    return search(1, 0, MAXDAY, mDay, mDay);
}
