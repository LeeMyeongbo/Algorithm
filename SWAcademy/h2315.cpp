#include <cstring>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

struct Rect {
    int y, x, front, height, width, id;
} rect[10001];
struct hash_pair {
    size_t operator()(const pair<int, int>& p) const {
        return p.first * 10000 + p.second;
    }
};
int n, front;       // front : 현재 좌표상에 존재하는 사각형 중 가장 앞에 있는 것(숫자가 클수록 앞임)
unordered_map<pair<int, int>, map<int, int>, hash_pair> rmap;      // {(y, x) : (front : id)}로 저장

void init(int N)
{
    n = N;
    rmap.clear();
    front = 0;
    memset(rect, 0, sizeof(rect));
}

void addRect(int mID, int mY, int mX, int mHeight, int mWidth)
{
    rect[mID] = {mY, mX, ++front, mHeight, mWidth, mID};

    register unsigned int max_y = min(n, rect[mID].y + rect[mID].height);
    register unsigned int max_x = min(n, rect[mID].x + rect[mID].width);
    for (register unsigned int y = rect[mID].y; y < max_y; y++)
        for (register unsigned int x = rect[mID].x; x < max_x; x++)
            rmap[{y, x}][rect[mID].front] = mID;
}

void selectAndMove(int y1, int x1, int y2, int x2)
{
    if (!rmap[{y1, x1}].size())
        return;
    
    int mID = rmap[{y1, x1}].rbegin()->second;
    register unsigned int max_y = min(n, rect[mID].y + rect[mID].height);
    register unsigned int max_x = min(n, rect[mID].x + rect[mID].width);
    for (register unsigned int y = rect[mID].y; y < max_y; y++)
        for (register unsigned int x = rect[mID].x; x < max_x; x++)
            rmap[{y, x}].erase(rect[mID].front);
    
    rect[mID].y = y2, rect[mID].x = x2;
    max_y = min(n, rect[mID].y + rect[mID].height);
    max_x = min(n, rect[mID].x + rect[mID].width);
    for (register unsigned int y = rect[mID].y; y < max_y; y++)
        for (register unsigned int x = rect[mID].x; x < max_x; x++)
            rmap[{y, x}][rect[mID].front] = mID;
}

int moveFront(int mID)
{
    if (rect[mID].front)
    {
        int id = 0, f = 0;
        register unsigned int max_y = min(n, rect[mID].y + rect[mID].height);
        register unsigned int max_x = min(n, rect[mID].x + rect[mID].width);
        for (register unsigned int y = rect[mID].y; y < max_y; y++)
            for (register unsigned int x = rect[mID].x; x < max_x; x++)
            {
                rmap[{y, x}].erase(rect[mID].front);
                rmap[{y, x}][front + 1] = mID;

                auto it = ++(rmap[{y, x}].rbegin());
                if (rmap[{y, x}].size() > 1 && it->first > f)
                {
                    f = it->first;
                    id = it->second;
                }
            }
        rect[mID].front = ++front; 

        return id;
    }
    return 0;
}

int selectAndErase(int mY, int mX)
{
    if (!rmap[{mY, mX}].size())
        return 0;
    
    int mID = rmap[{mY, mX}].rbegin()->second;
    register unsigned int max_y = min(n, rect[mID].y + rect[mID].height);
    register unsigned int max_x = min(n, rect[mID].x + rect[mID].width);
    for (register unsigned int y = rect[mID].y; y < max_y; y++)
        for (register unsigned int x = rect[mID].x; x < max_x; x++)
            rmap[{y, x}].erase(rect[mID].front);
    rect[mID] = {0, 0, 0, 0, 0, mID};

    return mID;
}

int check(int mY, int mX)
{
    if (!rmap[{mY, mX}].size())
        return 0;
    
    return rmap[{mY, mX}].rbegin()->second;
}
