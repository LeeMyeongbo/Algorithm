#include <set>
#include <unordered_map>
using namespace std;

set<int> buildings;                         // 건물 위치 정렬해서 저장
unordered_map<int, int> buildingIdx;        // {건물 id : 건물 위치}

void init(int N, int mId[], int mLocation[])
{
    buildings.clear();

    for (register unsigned int i = 0; i < N; i++)
    {
        buildings.insert(mLocation[i]);
        buildingIdx.insert({ mId[i], mLocation[i] });
    }

    return;
}

int add(int mId, int mLocation) 
{
    if (buildingIdx.count(mId))
    {
        register int pre_loc = buildingIdx[mId];
        buildings.erase(pre_loc);
    }
    buildingIdx[mId] = mLocation;
    buildings.insert(mLocation);

    return buildings.size();
}

int remove(int mStart, int mEnd) 
{
    register auto startIter = buildings.lower_bound(mStart);
    register auto endIter = buildings.upper_bound(mEnd);

    buildings.erase(startIter, endIter);

    return buildings.size();
}

int install(int M) 
{
    register unsigned int left = 1, right = 1000000000, ans = 0, mid;
    while (left <= right)
    {
        mid = (left + right) >> 1;

        register unsigned int tmp_cnt = 1;
        register int pre = *buildings.begin();

        for (const int& i : buildings)
            if (i - pre >= mid)
                tmp_cnt++, pre = i;

        if (tmp_cnt < M)
            right = mid - 1;
        else if (tmp_cnt > M)
            left = mid + 1;
        else
            ans = mid, left = mid + 1;
    }

    return ans;
}
