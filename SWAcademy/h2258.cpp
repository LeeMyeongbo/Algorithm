#include <map>
#include <unordered_map>
#include <cstring>
#include <string>
#define MAXL		(11)
using namespace std;

struct RESULT
{
    char mTitle[MAXL];
    int mStartDay, mEndDay;
};
map<int, pair<int, string>> schedule;           // (끝나는 날짜 : (시작 날짜, 제목))으로 저장
unordered_map<string, int> getEndDaybyTitle;
int n;

void init(int N)
{
    schedule.clear();
    getEndDaybyTitle.clear();
    n = N;
}

int addSchedule(char mTitle[], int mStartDay, int mEndDay, int mForced)
{
    while (true)
    {
        register auto it = schedule.lower_bound(mStartDay);         // 끝나는 날이 mStartDay보다 크거나 같은 가장 빠른 일정 구함
        if (it != schedule.end() && it->second.first <= mEndDay)    // 그 일정의 시작일이 mEndDay 이하일 경우 -> 겹치는 상황임!
        {
            if (!mForced)
                return 0;

            getEndDaybyTitle.erase(it->second.second);
            schedule.erase(it);
        }
        else break;
    }

    register string title(mTitle);
    schedule.insert({ mEndDay, {mStartDay, title} });
    getEndDaybyTitle.insert({ title, mEndDay });

    return 1;
}

RESULT getSchedule(int mDay)
{
    RESULT ret = { '\0', -1, -1 };

    register auto it = schedule.lower_bound(mDay);
    if (it != schedule.end() && it->second.first <= mDay)
    {
        strcpy_s(ret.mTitle, it->second.second.c_str());
        ret.mStartDay = it->second.first, ret.mEndDay = it->first;
    }

    return ret;
}

int deleteSchedule(char mTitle[])
{
    register string title(mTitle);
    
    if (!getEndDaybyTitle.count(title))
        return 0;

    register int endDay = getEndDaybyTitle[title];
    getEndDaybyTitle.erase(title);
    schedule.erase(endDay);

    return 1;
}

int findEmptySchedule()
{
    if (schedule.empty())
        return n;

    register int len = 0, pre = 0;
    for (register auto it = schedule.begin(); it != schedule.end(); it++)
    {
        len = max(len, it->second.first - pre - 1);
        pre = it->first;
    }
    len = max(len, n - pre);

    return len;
}
