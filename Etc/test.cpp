#include<cmath>
#include<vector>
#include<queue>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<unordered_map>
using namespace std;
int tree[400000];
int tree2[400000];
int lazy[400000];
struct node {
    int s;
    int e;
};
node nd[8001];
priority_queue<pair<int, int>>pq;
int cnt;
int tot;
unordered_map<int, int>m;

void lazyu(int node, int l, int r) 
{
    if (lazy[node] != 0) {
        tree[node] += lazy[node];
        tree2[node] += lazy[node];
        if (l != r) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void upd(int node, int l, int r, int rl, int rr, int diff) 
{
    lazyu(node, l, r);
    if (r < rl || rr < l) return;
    if (rl <= l && r <= rr) {
        tree[node] += diff;
        tree2[node] += diff;
        if (l != r) {
            lazy[2 * node] += diff;
            lazy[2 * node + 1] += diff;
        }
        return;
    }
    int mid = (l + r) / 2;
    upd(node * 2, l, mid, rl, rr, diff);
    upd(node * 2 + 1, mid + 1, r, rl, rr, diff);
    tree[node] = min(tree[node * 2 + 1], tree[node * 2]);
    tree2[node] = max(tree2[node * 2 + 1], tree2[node * 2]);
}

void find(int node, int l, int r, int minn) 
{
    lazyu(node, l, r);
    if (tree2[node] < minn) return;
    if (tree[node] >= minn) {
        pq.push(make_pair(-l, r));
        return;
    }
    if (l == r) return;
    int mid = (l + r) / 2;
    find(node * 2, l, mid, minn);
    find(node * 2 + 1, mid + 1, r, minn);
}
void init() 
{
    cnt = 0;
    memset(tree, 0, sizeof(tree));
    memset(tree2, 0, sizeof(tree2));
    memset(lazy, 0, sizeof(lazy));
    tot = 0;
    return;
}

int add(int mId, int mStart, int mEnd) 
{
    if (m[mId] == 0) {
        cnt++;
        m[mId] = cnt;
        upd(1, 0, 399999, mStart, mEnd, 1);
        nd[cnt].s = mStart;
        nd[cnt].e = mEnd;
        tot++;
    }
    else {
        int tempcnt = m[mId];
        int a = nd[tempcnt].s;
        int b = nd[tempcnt].e;
        upd(1, 0, 399999, a, b, -1);
        nd[tempcnt].s = mStart;
        nd[tempcnt].e = mEnd;
        upd(1, 0, 399999, mStart, mEnd, 1);
    }
    return tot;
}

int remove(int mId) 
{
    if (m[mId] != 0) {
        tot--;
        int tempcnt = m[mId];
        int a = nd[tempcnt].s;
        int b = nd[tempcnt].e;
        upd(1, 0, 399999, a, b, -1);
        m[mId] = 0;
    }
    return tot;
}

int announce(int mDuration, int M) 
{
    while (!pq.empty())pq.pop();
    find(1, 0, 399999, M);
    int aa = 0;
    int preb = -2;
    while (!pq.empty()) {
        int a = -pq.top().first;
        int b = pq.top().second;
        pq.pop();
        if (preb + 1 != a) aa = a;
        if (b - aa + 1 >= mDuration)
            return aa;
        preb = b;

    }
    return -1;
}
