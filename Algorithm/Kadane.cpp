#include <iostream>
using namespace std;

int main()                      // 부분배열들 중 가장 큰 것의 합 구하기!
{
    int arr[10] = {0, }, ans = INT32_MIN;
    for (int i = 0; i < 10; i++)
        cin >> arr[i];

    int M[10] = {0, };          // M[i] : i번째로 끝나는 부분배열들 중 최대의 합
    M[0] = arr[0];

    for (int i = 1; i < 10; i++)
    {
        M[i] = max(M[i - 1] + arr[i], arr[i]);
        ans = max(ans, M[i]);
    }
    
    cout << "최대 합 : " << ans;
    return 0;
}