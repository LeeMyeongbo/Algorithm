#include <iostream>
#include <algorithm>
using namespace std;

int T, n;
pair<long long, long long> rail[200000];

bool cmp(const pair<long long, long long>& p1, const pair<long long, long long>& p2)  // a1*(a2*v+b2)+b1 > a2*(a1*v+b1)+b2 만족할 때
{                                                                                     // p1=(a1, b1)이 p2=(a2, b2)보다 앞에 위치해야 함
    return p2.second * (p1.first - 1) > p1.second * (p2.first - 1);                   // 위 식을 정리하면 a1*a2*v+a1*b2+b1 > a2*a1*v+a2*b1+b2 
}                                                                                     // a1*b2-b2 > a2*b1-b1
                                                                                      // 결론적으로 b2(a1-1) > b1(a2-1) 만족 시 p1이 p2보다 앞에 위치
int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> rail[i].first >> rail[i].second;

        sort(rail, rail + n, cmp);

        long long speed = 1;
        for (int i = 0; i < n; i++)
            speed = (rail[i].first * speed + rail[i].second) % 1000000007;

        cout << '#' << test_case << ' ' << speed << "\n";
    }
    return 0;
}
