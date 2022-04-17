#include <iostream>
#include <tuple>
#include <cmath>
using namespace std;

tuple<int, int, int> tree[1 << 18];

tuple<int, int, int> getSum(int index, int start, int end, int left, int right)
{
    if (left > end || right < start)
        return {0, 0, 0};
    if (left >= start && right <= end)
        return tree[index];

    tuple<int, int, int> l = getSum(index * 2, start, end, left, (left + right) / 2);
    tuple<int, int, int> r = getSum(index * 2 + 1, start, end, (left + right) / 2 + 1, right);

    return {get<0>(l) + get<0>(r), get<1>(l) + get<1>(r), get<2>(l) + get<2>(r)};
}

int main(int argc, char** argv)
{
    int T, N, Q, S, k, s, e;
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> T;

	for (int test_case = 1; test_case <= T; ++test_case) {
        for (int i = 1; i < (1 << 18); i++)
            tree[i] = {0, 0, 0};
        
        cin >> N >> Q;

        S = 1 << (int)ceil(log2(N + 1));
        for (int i = 1; i <= N; i++) {
            cin >> k;
            k == 1 ? get<0>(tree[S + i])++ : k == 2 ? get<1>(tree[S + i])++ : get<2>(tree[S + i])++;
        }

        for (int i = S - 1; i > 0; i--) {
            get<0>(tree[i]) = get<0>(tree[i * 2]) + get<0>(tree[i * 2 + 1]);
            get<1>(tree[i]) = get<1>(tree[i * 2]) + get<1>(tree[i * 2 + 1]);
            get<2>(tree[i]) = get<2>(tree[i * 2]) + get<2>(tree[i * 2 + 1]);
        }

        cout << '#' << test_case << '\n';
        while (Q--) {
            cin >> s >> e;
            tuple<int, int, int> a = getSum(1, s, e, 0, S - 1);
            cout << get<0>(a) << ' ' << get<1>(a) << ' ' << get<2>(a) << '\n';
        }
	}

	return 0;
}