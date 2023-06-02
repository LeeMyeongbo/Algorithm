#include <iostream>
#include <stack>
using namespace std;

long long height[100000];

int main()                                          // stack을 활용한 풀이
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    while (true)
    {
        register int n;
        cin >> n;

        if (!n)
            return 0;

        stack<int> pos;                             // 각 직사각형의 위치 저장하는 스택
        register long long ans = 0;
        for (register int p = 0; p < n; ++p)
            cin >> height[p];

        for (register int p = 0; p < n; ++p)
        {
            register int right = p - 1;                                 // right : 현재 직사각형의 바로 앞 위치
            while (!pos.empty() && height[pos.top()] > height[p])       // 이 조건에 걸릴 경우 여태 진행한 직사각형들을 이용해 넓이 갱신
            {
                register long long h = height[pos.top()];
                pos.pop();

                register int left = pos.empty() ? 0 : pos.top() + 1;    // left : 스택이 비었으면 0, 아니면 현 top의 다음 위치
                ans = max(ans, h * (right - left + 1));
            }
            pos.emplace(p);
        }

        register int right = n - 1;                                     // 이제 right는 히스토그램 끝까지로 설정 가능
        while (!pos.empty())                                            // 아직 스택에 위치가 남았을 경우 마저 갱신 진행
        {
            register long long h = height[pos.top()];
            pos.pop();

            register int left = pos.empty() ? 0 : pos.top() + 1;
            ans = max(ans, h * (right - left + 1));
        }

        cout << ans << '\n';
    }
}
