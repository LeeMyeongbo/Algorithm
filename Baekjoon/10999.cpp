#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<pair<long long, long long>> tree;

long long init(int index, int left, int right)
{
    if (left == right)
        return tree[index].first;
    
    int mid = (left + right) >> 1;
    return tree[index].first = init(index << 1, left, mid) + init((index << 1) + 1, mid + 1, right);
}

void prop(int index, int left, int right)       // 현재 노드에 변화 반영하고 자식 노드들에게도 물려주는 과정
{
    if (tree[index].second)
    {
        tree[index].first += (right - left + 1) * tree[index].second;
        if (left != right)
        {
            tree[index << 1].second += tree[index].second;
            tree[(index << 1) + 1].second += tree[index].second;
        }
        tree[index].second = 0;
    }
}

long long search(int index, int left, int right, int r1, int r2)
{
    prop(index, left, right);
    if (left > r2 || right < r1)
        return 0;
    
    if (left >= r1 && right <= r2)
        return tree[index].first;
    
    int mid = (left + right) >> 1;
    return search(index << 1, left, mid, r1, r2) + search((index << 1) + 1, mid + 1, right, r1, r2);
}

void update(int index, int left, int right, int r1, int r2, long long diff)
{
    prop(index, left, right);
    if (left > r2 || right < r1)
        return;
    
    if (left >= r1 && right <= r2)
    {
        tree[index].first += (right - left + 1) * diff;
        if (left != right)
        {
            tree[index << 1].second += diff;
            tree[(index << 1) + 1].second += diff;
        }
        return;
    }

    int mid = (left + right) >> 1;
    update(index << 1, left, mid, r1, r2, diff);
    update((index << 1) + 1, mid + 1, right, r1, r2, diff);
    tree[index].first = tree[index << 1].first + tree[(index << 1) + 1].first;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    int N, M, K, S, a, b, c;
    long long d;

    cin >> N >> M >> K;
    S = 1 << (int)ceil(log2(N));
    tree.resize(S << 1);

    for (int i = 0; i < N; i++)
        cin >> tree[S + i].first;
    
    init(1, 1, S);
    for (int q = 0; q < M + K; q++)
    {
        cin >> a;
        if (a == 1)
        {
            cin >> b >> c >> d;
            update(1, 1, S, b, c, d);
        }
        else
        {
            cin >> b >> c;
            cout << search(1, 1, S, b, c) << '\n';
        }
    }

    return 0;
}