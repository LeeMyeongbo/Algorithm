#include <iostream>
#include <string>
#include <stdlib.h>
#include <queue>
#include <set>
#define MAX_N 10000
using namespace std;

int Storage[MAX_N];							// 현재 상태의 Storage
int StorageExpected[MAX_N];					// 이동 예상도 
int IsOccupied[MAX_N];						// 관리자가 배치도
int InputN, InputM, WorkingOfficer, CurTStamp;
struct SEvent
{
    int tStamp;
    int type;
    int city;
    int tax;
};
struct compare {
    bool operator()(const SEvent a, const SEvent b) const {
        if (a.tStamp == b.tStamp)
            return a.type > b.type;     // EXPECT -> ADD -> ARRIVE -> COMEBACK

        return a.tStamp > b.tStamp;     // time 이 큰거 
    }
};
struct compExpected {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
        if (a.first == b.first)
            return a.second < b.second;			// 곡물의 양이 같으면 도시 ID가 작은 창고가 우선

        return a.first > b.first;				// 곡물의 양이 많은 순서 
    }
};
set <pair<int, int>, compExpected> ExpectPQ;
set <pair<int, int>>::iterator ExpectIter[MAX_N];
priority_queue<SEvent, vector<SEvent>, compare> EventQueue;
enum {
    EXPECT,
    ADD,
    ARRIVE,
    COMEBACK
};

void init(int N, int M)
{
    ExpectPQ.clear();
    EventQueue = {};

    // 도시의 개수 맞큼만 초기화함 
    for (int i = 0; i < N; ++i)
    {
        Storage[i] = 0;
        StorageExpected[i] = 0;
        IsOccupied[i] = 0;
        ExpectIter[i] = ExpectPQ.end();
    }

    InputN = N;
    InputM = M;

    CurTStamp = 0;
    WorkingOfficer = 0;
}

void destroy()
{ }

// 관리 파견을 위한 함수 (tStamp 기준으로 그동안 처리 못한것을 처리함)
void SendOfficer(int tStamp)
{
    while (true)
    {
        if (WorkingOfficer >= InputM) 
            break;
        if (ExpectPQ.empty()) 
            break;

        auto iter = ExpectPQ.begin();
        int city = iter->second;

        ExpectPQ.erase(iter);
        ExpectIter[city] = ExpectPQ.end();

        IsOccupied[city] = 1;
        EventQueue.push({ tStamp + city,ARRIVE, city , });
        ++WorkingOfficer;
    }
}

void UpdateExpectPq(int city, int tax)
{
    if (ExpectIter[city] != ExpectPQ.end())
        ExpectPQ.erase(ExpectIter[city]);

    ExpectIter[city] = ExpectPQ.end();
    StorageExpected[city] += tax;
    if (IsOccupied[city] != 1)
        ExpectIter[city] = ExpectPQ.insert(ExpectPQ.begin(), { StorageExpected[city] ,city });
}

// tStamp 시간에 맞도록 처리해야할 일들을 함.  
void DoProcess(int tStamp)
{
    while (true)
    {
        if (EventQueue.empty()) 
            break;
        SEvent event = EventQueue.top();
        if (event.tStamp > tStamp) 
            break;
        EventQueue.pop();

        if (CurTStamp < event.tStamp)
        {
            SendOfficer(CurTStamp);
            CurTStamp = event.tStamp;
        }
        switch (event.type)
        {
        case EXPECT:
            UpdateExpectPq(event.city, event.tax);
            break;
        case ADD:
            Storage[event.city] += event.tax;
            break;
        case ARRIVE:
            EventQueue.push({ event.tStamp + event.city ,COMEBACK, event.city ,Storage[event.city] });
            StorageExpected[event.city] -= Storage[event.city];
            Storage[event.city] = 0;
            break;
        case COMEBACK:
            Storage[0] += event.tax;
            IsOccupied[event.city] = 0;
            if (StorageExpected[event.city] > 0)
                ExpectIter[event.city] = ExpectPQ.insert(ExpectPQ.begin(), { StorageExpected[event.city] ,event.city });
            --WorkingOfficer;
            break;
        default:
            break;
        }
    }

    if (CurTStamp < tStamp)
    {
        SendOfficer(CurTStamp);
        CurTStamp = tStamp;
    }
}

int order(int tStamp, int mCityA, int mCityB, int mTax)
{
    DoProcess(tStamp);

    register int tGap = abs(mCityA - mCityB);
    register int eventStamp = tStamp + tGap - mCityB;
    if (eventStamp <= tStamp)
        UpdateExpectPq(mCityB, mTax);
    else
        EventQueue.push({ eventStamp ,EXPECT, mCityB ,mTax });
    EventQueue.push({ tStamp + tGap ,ADD, mCityB ,mTax });

    SendOfficer(tStamp);
    CurTStamp = tStamp;

    return Storage[0];
}

int check(int tStamp)
{
    DoProcess(tStamp);
    SendOfficer(tStamp);
    CurTStamp = tStamp;

    return Storage[0];
}
