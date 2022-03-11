#include <iostream>
#include <algorithm>
using namespace std;

int T, n;
bool visited[100000];
pair<long long, long long> a[100000], b[100000];

bool cmp(const pair<long long, long long>& p1, const pair<long long, long long>& p2)     // (a1, b1), (a2, b2)가 있을 때
{                                                                                        // a1-a2-(b2-b1)과 a2-a1-(b1-b2) 값을 비교해서 더 큰 순서쌍을 앞으로
    return p1.first - p2.first - (p2.second - p1.second) > p2.first - p1.first - (p1.second - p2.second);
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i].first >> a[i].second;
            b[i].first = a[i].second;
            b[i].second = a[i].first;
        }
        sort(a, a + n, cmp);
        sort(b, b + n, cmp);

        int a_idx = 0, b_idx = 0;
        long long a_h = 0, b_h = 0;

        for (int i = 0; i < n; i++) {
            if (!(i % 2)) {
                while (a_idx < n && visited[a_idx])
                    a_idx++;

                a_h += a[a_idx].first;
                visited[a_idx] = true;
            }
            else {
                while (b_idx < n && visited[b_idx])
                    b_idx++;

                b_h += b[b_idx].first;
                visited[b_idx] = true;
            }
        }

        cout << '#' << test_case << ' ' << a_h - b_h << '\n';
        fill(visited, visited + n, false);
    }
    return 0;
}
