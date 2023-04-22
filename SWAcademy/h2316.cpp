#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

struct Node {
    int mTime, mDelay;
    int channelID, newsID;

    bool operator<(const Node& n)const {
        if (mTime + mDelay > n.mTime + n.mDelay)
            return true;
        else if (mTime + mDelay < n.mTime + n.mDelay)
            return false;
        else
        {
            if (newsID > n.newsID)
                return true;
            else return false;
        }
    }
};
unordered_map<int, int> users, channels;		// users : (사용자 id, 사용자 번호), channels : (채널 id, 채널 번호)
unordered_map<int, bool> news;					// news : (뉴스 id, 삭제 여부)
vector<int> channel_user[501];			        // channel_user[n] : n번 채널이 뉴스를 제공하는 사용자들을 저장
vector<int> received_news[501];			        // received_news[n] : n번 사용자가 받은 뉴스들을 저장(삭제된 것도 포함)
priority_queue<Node> pq;
unsigned int u_idx, c_idx;

void init(int N, int K)
{
    u_idx = 0, c_idx = 0;
    users.clear();
    channels.clear();
    for (register unsigned int i = 0; i < 501; i++)
    {
        channel_user[i].clear();
        received_news[i].clear();
    }
    while (!pq.empty())
        pq.pop();
}

void registerUser(int mTime, int mUID, int mNum, int mChannelIDs[])
{
    //mTime 시각까지 보낼 알림 있을 경우 알림 먼저 보냄
    while (!pq.empty())
    {
        Node node = pq.top();
        if (node.mTime + node.mDelay > mTime)
            break;
        pq.pop();

        register unsigned int ch_index = channels[node.channelID];
        register unsigned int size = channel_user[ch_index].size();
        for (register unsigned int u = 0; u < size; u++)
            received_news[channel_user[ch_index][u]].emplace_back(node.newsID);
    }

    // 그리고 각 채널마다 사용자 저장!
    for (register unsigned int i = 0; i < mNum; i++)
    {
        if (!channels.count(mChannelIDs[i]))
            channels[mChannelIDs[i]] = c_idx++;
        if (!users.count(mUID))
            users[mUID] = u_idx++;

        channel_user[channels[mChannelIDs[i]]].emplace_back(users[mUID]);
    }
}

int offerNews(int mTime, int mNewsID, int mDelay, int mChannelID)
{
    pq.push({ mTime, mDelay, mChannelID, mNewsID });
    news[mNewsID] = true;

    return channel_user[channels[mChannelID]].size();
}

void cancelNews(int mTime, int mNewsID)
{
    news[mNewsID] = false;
}

int checkUser(int mTime, int mUID, int mRetIDs[])
{
    while (!pq.empty())
    {
        Node node = pq.top();
        if (node.mTime + node.mDelay > mTime)
            break;
        pq.pop();

        register unsigned int ch_index = channels[node.channelID];
        register unsigned int size = (int)channel_user[ch_index].size();
        for (register unsigned int u = 0; u < size; u++)
            received_news[channel_user[ch_index][u]].emplace_back(node.newsID);
    }

    int cnt = 0;
    register unsigned int u_index = users[mUID];
    register unsigned int size = (int)received_news[u_index].size();
    for (register int i = size - 1; i >= 0; i--)
    {
        if (news[received_news[u_index][i]])
        {
            if (cnt < 3)
                mRetIDs[cnt] = received_news[u_index][i];
            cnt++;
        }
        received_news[u_index].pop_back();
    }

    return cnt;
}
