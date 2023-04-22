#include <map>
#include <unordered_map>
using namespace std;

unordered_map<int, int> buildingIdx;     // {건물 id : 건물 위치}
map<int, int> buildings;                 // {건물 위치 : 건물 id}

void init(int N, int mId[], int mLocation[])
{
    buildingIdx.clear();
    buildings.clear();

    for (register unsigned int i = 0; i < N; i++)
    {
        buildingIdx.insert({ mId[i], mLocation[i] });
        buildings.insert({ mLocation[i], mId[i] });
    }

    return;
}

int add(int mId, int mLocation) 
{
    if (buildingIdx.count(mId))
    {
        int pre_loc = buildingIdx[mId];
        buildings.erase(pre_loc);

        buildingIdx[mId] = mLocation;
        buildings.insert({ mLocation, mId });
    }
    else
    {
        buildingIdx.insert({ mId, mLocation });
        buildings.insert({ mLocation, mId });
    }

    return buildings.size();
}

int remove(int mStart, int mEnd) 
{
    register int left = 0, right = buildings.size() - 1, mid, start = left, end = right;

    while (left <= right)
    {
        mid = (left + right) >> 1;
        auto pos = buildings.begin();
        advance(pos, mid);

        if (pos->first < mStart)
            left = mid + 1;
        else
        {
            start = mid;
            right = mid - 1;
        }
    }

    left = 0, right = buildings.size() - 1, mid = right >> 1;
    while (left <= right)
    {
        mid = (left + right) >> 1;
        auto pos = buildings.begin();
        advance(pos, mid);

        if (pos->first > mEnd)
            right = mid - 1;
        else
        {
            end = mid;
            left = mid + 1;
        }
    }

    auto start_pos = buildings.begin(), end_pos = buildings.begin();
    advance(start_pos, start);
    advance(end_pos, end + 1);
    
    for (auto it = start_pos; it != end_pos; it++)
        buildingIdx.erase(it->second);

    buildings.erase(start_pos, end_pos);

    return buildings.size();
}

int install(int M) 
{
    register unsigned int left = 1, right = 1000000000, ans = 0, mid;
    
    while (left <= right)
    {
        mid = (left + right) >> 1;

        register unsigned int tmp_cnt = 1;
        auto pre = buildings.begin();
        for (register auto cur = ++(buildings.begin()); cur != buildings.end(); cur++)
            if (cur->first - pre->first >= mid)
            {
                tmp_cnt++;
                pre = cur;
            }

        if (tmp_cnt < M)
            right = mid - 1;
        else if (tmp_cnt > M)
            left = mid + 1;
        else
            ans = mid, left = mid + 1;
    }

    return ans;
}
