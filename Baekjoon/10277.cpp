#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

struct Node {
    int lazy, max, min;
};
vector<Node> tree;

void prop(int index, int left, int right)
{
    if (tree[index].lazy)
    {
        tree[index].max += tree[index].lazy;
        tree[index].min += tree[index].lazy;

        if (left != right)
        {
            tree[index << 1].lazy += tree[index].lazy;
            tree[(index << 1) + 1].lazy += tree[index].lazy;
        }
        tree[index].lazy = 0;
    }
}

Node update(int index, int left, int right, int r1, int r2, int diff)
{
    prop(index, left, right);
    if (left > r2 || right < r1)
        return tree[index];

    if (left >= r1 && right <= r2)
    {
        tree[index].max += diff;
        tree[index].min += diff;

        if (left != right)
        {
            tree[index << 1].lazy += diff;
            tree[(index << 1) + 1].lazy += diff;
        }

        return tree[index];
    }

    int mid = (left + right) >> 1;
    Node lnode = update(index << 1, left, mid, r1, r2, diff);
    Node rnode = update((index << 1) + 1, mid + 1, right, r1, r2, diff);

    return tree[index] = { 0, max(lnode.max, rnode.max), min(lnode.min, rnode.min) };
}

Node search(int index, int left, int right, int r1, int r2)
{
    prop(index, left, right);
    if (left > r2 || right < r1)
        return { 0, INT32_MIN, INT32_MAX };

    if (left >= r1 && right <= r2)
        return tree[index];

    int mid = (left + right) >> 1;
    Node lnode = search(index << 1, left, mid, r1, r2);
    Node rnode = search((index << 1) + 1, mid + 1, right, r1, r2);

    return { 0, max(lnode.max, rnode.max), min(lnode.min, rnode.min) };
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    register int C, N, O, S, x, a, b, s;
    register string query;

    cin >> C >> N >> O;

    S = 1 << (int)ceil(log2(C));
    tree = vector<Node>(S << 1);

    while (O--)
    {
        cin >> query;
        if (query == "state")
        {
            cin >> x;
            cout << search(1, 0, C - 1, x, x).max << '\n';
        }
        else if (query == "groupchange")
        {
            cin >> a >> b >> s;
            register Node node = search(1, 0, C - 1, a, b);

            if (node.max + s > N)
                s = N - node.max;
            else if (node.min + s < 0)
                s = -node.min;

            update(1, 0, C - 1, a, b, s);
            cout << s << '\n';
        }
        else
        {
            cin >> x >> s;
            register Node node = search(1, 0, C - 1, x, x);

            if (node.max + s > N)
                s = N - node.max;
            else if (node.min + s < 0)
                s = -node.min;

            update(1, 0, C - 1, x, x, s);
            cout << s << '\n';
        }
    }

    return 0;
}
