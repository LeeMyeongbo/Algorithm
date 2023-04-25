#include <queue>
#include <set>
#include <unordered_map>
using namespace std;

int n;
struct Locker {
    int len, start;

    bool operator<(const Locker& n) const {
        if (len < n.len) return true;
        else if (len == n.len)
            return start > n.start;
        else return false;
    }
};
set<int> locker;                // 사용중인 사물함 정렬하여 저장
priority_queue<Locker> pq;      // (길이, 시작 사물함 번호)으로 저장
unordered_map<int, int> user;   // (사용자 id : 사용중인 사물함 번호)

void init(int N) 
{
    while (!pq.empty())
        pq.pop();
    user.clear();
    locker.clear();

    n = N;
    pq.push({ N, 1 });

    return;
}

int arrive(int mId) 
{
    while (!pq.empty())
    {
        Locker l = pq.top();
        pq.pop();

        auto it = locker.lower_bound(l.start);    // 현재 구간 내에 이미 사물함이 위치해 있다면 이 구간은 버려야 됨
        if (it != locker.end() && *it <= l.len + l.start - 1)
            continue;

        if (l.start == 1)                         // 1번 자리가 비었을 경우
        {
            locker.insert(1);
            user.insert({ mId, 1 });
            pq.push({ l.len - 1, 2 });

            return 1;
        }
        else if (l.start + l.len - 1 == n)        // n번 자리가 비었을 경우
        {
            locker.insert(n);
            user.insert({ mId, n });
            pq.push({ l.len - 1, l.start });

            return n;
        }
        else                                      // 둘 다 비지 않았다면
        {
            int start = l.start, end = l.start + l.len - 1;
            int mid = (start + end) >> 1;

            locker.insert(mid);
            user.insert({ mId, mid });
            if (mid - start)
                pq.push({ mid - start, start });
            if (end - mid)
                pq.push({ end - mid, mid + 1 });

            return mid;
        }
    }

    return 0;
}

int leave(int mId) 
{
    int lockerNum = user[mId];
    user.erase(mId);
    
    auto it = locker.find(lockerNum);
    if (locker.size() == 1)                 // 남은 사물함이 단 하나일 경우
    {
        locker.clear();
        pq.push({ n, 1 });
    }
    else if (it == locker.begin())          // 맨 앞 사물함을 비울 경우
    {
        int next = *(++it);
        locker.erase(lockerNum);
        pq.push({ next - 1, 1 });
    }
    else if (it == --locker.end())          // 맨 뒤 사물함을 비울 경우
    {
        int pre = *(--it);
        locker.erase(lockerNum);
        pq.push({ n - pre, pre + 1 });
    }
    else
    {
        int pre = *(--locker.find(lockerNum)), next = *(++locker.find(lockerNum));
        locker.erase(lockerNum);
        pq.push({ next - pre - 1, pre + 1 });
    }

    return n - locker.size();
}
