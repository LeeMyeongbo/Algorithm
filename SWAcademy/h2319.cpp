#include <unordered_map>
#include <set>
#include <queue>
using namespace std;

struct Info {
    int start, end, id;                     // 출근 시간, 퇴근 시간, id

    bool operator<(const Info& i) const {
        if (start == i.start)
        {
            if (end == i.end)
                return id < i.id;

            return end < i.end;
        }

        return start < i.start;
    }
};
unordered_map<int, pair<int, int>> empInfo;
set<Info> schedule;                         // 출근 시간 오름차순 -> 출근 시간 같으면 퇴근 시간 오름차순 -> 그 마저도 같으면 id 오름차순

void init()
{
    schedule.clear();
    empInfo.clear();
}

int add(int mId, int mStart, int mEnd)
{
    if (empInfo.count(mId))
    {
        register pair<int, int> time = empInfo[mId];
        schedule.erase({ time.first, time.second, mId });
    }
    empInfo[mId] = { mStart, mEnd };
    schedule.insert({ mStart, mEnd, mId });

    return empInfo.size();
}

int remove(int mId)
{
    if (empInfo.count(mId))
    {
        register pair<int, int> time = empInfo[mId];
        empInfo.erase(mId);
        schedule.erase({ time.first, time.second, mId });
    }

    return empInfo.size();
}

int announce(int mDuration, int M)          // sweeping
{
    if (schedule.empty())
        return -1;

    register auto iter = schedule.begin();

    // 최소 힙 생성
    priority_queue<int, vector<int>, greater<int>> pq;

    // 출근 시간이 가장 빠른 사원의 퇴근 시간을 힙에 저장
    pq.push(iter->end);

    // 그 다음 사원부터 출근 시간 순서대로 차례로 살핌
    for (register auto it = ++iter; it != schedule.end(); it++) 
    {
        // 현재 사원의 출근 시간이 현재 힙에 있는 가장 빠른 퇴근시간보다 크다면 현재 사원의 일정은 절대 그 퇴근 시간에 퇴근하는 사원과 겹칠 수 없음 -> 제거!
        // 또한 겹치더라도 이미 힙의 크기가 M 이상이라면 역시 가장 빠른 퇴근 시간의 사원은 무시 -> 제거
        while (!pq.empty() && (pq.top() < it->start || pq.size() >= M))
            pq.pop();

        // 현재 사원의 퇴근 시간 힙에 저장
        pq.push(it->end);

        // 힙에 저장된 퇴근 시간 개수가 정확히 M이고 힙 내 가장 빠른 퇴근 시간과 현재 사원의 출근 시간과의 차이가 mDuration 이상이면 조건 만족
        if (pq.top() - it->start + 1 >= mDuration && pq.size() == M)    
            return it->start;
    }

    return -1;
}
