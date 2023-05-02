#include <map>
#include <cstring>
using namespace std;
#define MAXM	3

struct Message {
    int id, sentTime, recievedTime, sentUser, receivedUser;
} messageList[100001];
map<int, Message> sentList[1001];                       // 보낸 쪽지 목록 {보낸 시각 : 메세지}
map<pair<int, int>, Message> recievedList[1001];        // 받은 쪽지 목록 {(받은 시각, 메세지id) : 메세지}
bool read[100001];                                      // 받은 쪽지 읽음 여부
int n;

void init(int N)
{
    for (register int i = 1; i <= n; i++)
    {
        sentList[i].clear();
        recievedList[i].clear();
    }
    memset(messageList, 0, sizeof(messageList));
    memset(read, false, sizeof(read));

    n = N;
}

void sendMessage(int cTimestamp, int uID1, int uID2, int mID, int scheduleTimestamp)
{
    messageList[mID] = { mID, cTimestamp, scheduleTimestamp, uID1, uID2 };
    sentList[uID1].insert({ cTimestamp, messageList[mID]});
    recievedList[uID2].insert({ { scheduleTimestamp, mID }, messageList[mID] });
}

int retrieveSentbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM])
{
    register int cnt = 0;
    for (register auto it = sentList[uID].rbegin(); it != sentList[uID].rend(); it++)
    {
        mIDList[cnt] = it->second.id;
        uIDList[cnt] = it->second.receivedUser;
        readList[cnt] = read[mIDList[cnt]] ? 1 : 0;
        cnt++;

        if (cnt == 3) break;
    }

    return cnt;
}

int retrieveInbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM])
{
    register int cnt = 0;
    for (register auto it = recievedList[uID].rbegin(); it != recievedList[uID].rend(); it++)
    {
        if (it->first.first <= cTimestamp)
        {
            mIDList[cnt] = it->second.id;
            uIDList[cnt] = it->second.sentUser;
            readList[cnt] = read[mIDList[cnt]] ? 1 : 0;
            cnt++;
        }
        if (cnt == 3) break;
    }

    return cnt;
}

int readMessage(int cTimestamp, int uID, int mID)
{
    register bool r = false;
    register Message m = messageList[mID];

    if (sentList[uID].count(m.sentTime))
        r = true;

    if (recievedList[uID].count({ m.recievedTime, m.id }) && m.recievedTime <= cTimestamp)
    {
        read[m.id] = true;
        r = true;
    }

    return r ? 1 : 0;
}

int deleteMessage(int cTimestamp, int uID, int mID)
{
    register bool r = false;
    register Message m = messageList[mID];

    if (sentList[uID].count(m.sentTime))
    {
        sentList[uID].erase(m.sentTime);
        if (m.recievedTime > cTimestamp)
            recievedList[m.receivedUser].erase({ m.recievedTime, m.id });

        r = true;
    }

    if (m.recievedTime <= cTimestamp && recievedList[uID].count({ m.recievedTime, m.id }))
    {
        recievedList[uID].erase({ m.recievedTime, m.id });
        r = true;
    }

    return r ? 1 : 0;
}
