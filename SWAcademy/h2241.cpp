#include <vector>
#include <map>
#include <set>
using namespace std;

struct Room {
    int roomid, region, bed, type, view, price;
};
vector<Room> hotels[1001];
map<int, int> reservation[100001];              // reservation[i] : ID가 i인 룸의 {체크 아웃 전 날짜 : 체크인 날짜}
set<pair<int, int>> roomFilter[11][11][5][5];   // roomFilter[지역][침대 수][룸 타입][조망 타입] : {가격, 룸 id}
int hotelCnt, roomCnt;

void init(int N, int mRoomCnt[])
{
    for (register int i = 1; i <= hotelCnt; i++)
        hotels[i].clear();

    for (register int i = 1; i <= roomCnt; i++)
        reservation[i].clear();

    for (register int region = 1; region <= 10; region++)
        for (register int bed = 2; bed <= 10; bed++)
            for (register int type = 1; type <= 4; type++)
                for (register int view = 1; view <= 4; view++)
                    roomFilter[region][bed][type][view].clear();

    hotelCnt = N, roomCnt = 0;
    for (register int i = 0; i < N; i++)
        roomCnt += mRoomCnt[i];
}

void addRoom(int mHotelID, int mRoomID, int mRoomInfo[])
{
    hotels[mHotelID].push_back({ mRoomID, mRoomInfo[0], mRoomInfo[1], mRoomInfo[2], mRoomInfo[3], mRoomInfo[4] });
    roomFilter[mRoomInfo[0]][mRoomInfo[1]][mRoomInfo[2]][mRoomInfo[3]].insert({ mRoomInfo[4], mRoomID });
}

int findRoom(int mFilter[])
{
    set<pair<int, int>>& room = roomFilter[mFilter[2]][mFilter[3]][mFilter[4]][mFilter[5]];
    for (register auto it = room.begin(); it != room.end(); it++)
    {
        register int roomID = it->second;
        register auto reserve = reservation[roomID].lower_bound(mFilter[0]);
        if (reserve == reservation[roomID].end() || reserve->second >= mFilter[1])
        {
            reservation[roomID].insert({ mFilter[1] - 1, mFilter[0] });
            return roomID;
        }
    }

    return -1;
}

int riseCosts(int mHotelID)
{
    register int ans = 0;

    for (Room& r : hotels[mHotelID])
    {
        roomFilter[r.region][r.bed][r.type][r.view].erase({ r.price, r.roomid });

        r.price *= 1.1;
        roomFilter[r.region][r.bed][r.type][r.view].insert({ r.price, r.roomid });

        ans += r.price;
    }

    return ans;
}
