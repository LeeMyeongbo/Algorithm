#include <vector>
#include <unordered_map>
#include <map>
#include <string>
using namespace std;
#define MAXM (10)
#define MAXL (11)

int memberCnt;
unordered_map<string, pair<int, vector<int>>> meetings;           // (회의 이름 : (끝나는 시간, 회의 참석자 idx 목록))
unordered_map<string, int> membersIdx;                            // (멤버 이름 : 멤버 idx)
map<int, pair<int, string>> members[20000];                       // 각 멤버 idx별로 (끝나는 시간 : (시작 시간, 참석하려는 회의 이름)) 저장

void init()
{
    meetings.clear();
    membersIdx.clear();
    for (register int i = 0; i < memberCnt; i++)
        members[i].clear();

    memberCnt = 0;
}

int addMeeting(char mMeeting[MAXL], int M, char mMemberList[MAXM][MAXL], int mStartTime, int mEndTime)
{
    string meetingName(mMeeting);
    vector<int> attendance;

    for (register int i = 0; i < M; i++)
    {
        string memberName(mMemberList[i]);

        if (!membersIdx.count(memberName))
            membersIdx.insert({ memberName, memberCnt++ });

        register int memberIdx = membersIdx[memberName];
        register auto it = members[memberIdx].lower_bound(mStartTime);       // 끝나는 시간이 mStartTime 이상인 제일 빠른 일정 구함

        if (it == members[memberIdx].end() || it->second.first > mEndTime)   // 그 일정이 없거나 그 일정의 시작 시간이 mEndTime보다 커야지 추가 가능
        {
            attendance.push_back(memberIdx);
            members[memberIdx].insert({ mEndTime, {mStartTime, meetingName} });
        }
    }

    if (attendance.size())
        meetings.insert({ meetingName, {mEndTime, attendance} });

    return attendance.size();
}

int cancelMeeting(char mMeeting[MAXL])
{
    string meetingName(mMeeting);

    if (!meetings.count(meetingName))
        return 0;

    register int endTime = meetings[meetingName].first;
    for (int& memberIdx : meetings[meetingName].second)
        members[memberIdx].erase(endTime);
    
    meetings.erase(meetingName);

    return 1;
}

int changeMeetingMember(char mMeeting[MAXL], char mMember[MAXL])
{
    string meetingName(mMeeting);
    string memberName(mMember);

    if (!meetings.count(meetingName))
        return -1;

    if (!membersIdx.count(memberName))
        membersIdx.insert({ memberName, memberCnt++ });

    register int memberIdx = membersIdx[memberName], meeting_endTime = meetings[meetingName].first;
    vector<int>& v = meetings[meetingName].second;
    register int meeting_startTime = members[v[0]][meeting_endTime].first; 

    for (register int i = 0; i < v.size(); i++)
    {
        if (v[i] == memberIdx)
        {
            members[memberIdx].erase(meetings[meetingName].first);
            v.erase(v.begin() + i);
            
            if (!v.size()) meetings.erase(meetingName);

            return 0;
        }
    }

    register auto it = members[memberIdx].lower_bound(meeting_startTime);
    if (it == members[memberIdx].end() || it->second.first > meeting_endTime)
    {
        v.push_back(memberIdx);
        members[memberIdx].insert({ meeting_endTime, {meeting_startTime, meetingName} });

        return 1;
    }

    return 2;
}

int changeMeeting(char mMeeting[MAXL], int mStartTime, int mEndTime)
{
    string meetingName(mMeeting);
    if (!meetings.count(meetingName))
        return 0;

    register int meeting_endTime = meetings[meetingName].first;
    meetings[meetingName].first = mEndTime;
    vector<int> attendance;

    for (int memberIdx : meetings[meetingName].second)
    {
        members[memberIdx].erase(meeting_endTime);
        register auto it = members[memberIdx].lower_bound(mStartTime);
        if (it == members[memberIdx].end() || it->second.first > mEndTime)
        {
            attendance.push_back(memberIdx);
            members[memberIdx].insert({ mEndTime, {mStartTime, meetingName} });
        }
    }
    
    if (attendance.size())
        meetings[meetingName].second = attendance;
    else
        meetings.erase(meetingName);

    return attendance.size();
}

void checkNextMeeting(char mMember[MAXL], int mTime, char mResult[MAXL])
{
    mResult[0] = '\0';                              // 항상 매개변수로 들어오는 배열은 초기화!
    string memberName(mMember);
    if (!membersIdx.count(memberName))
        return;

    register int memberIdx = membersIdx[memberName];
    register auto it = members[memberIdx].lower_bound(mTime + 1);

    if (it != members[memberIdx].end())
    {
        if (it->second.first < mTime + 1)           // mTime 이전 또는 mTime 시간에 이미 시작된 회의가 있을 경우
            it++;
        if (it != members[memberIdx].end())
        {
            register string ans = it->second.second;
            memcpy(mResult, ans.c_str(), ans.size());
            mResult[ans.size()] = '\0';
        }
    }
}
