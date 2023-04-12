#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T, N, P;
	cin >> T;

	for (int test_case = 1; test_case <= T; ++test_case)
	{
        cin >> N >> P;
        
        int num = N / P;        // 묶음 하나당 사탕 개수(나머지가 남으면 하나씩 더 담을 수도 있음)
        long long ans = 1;
        for (int i = 0; i < P; i++)
            ans = i < N % P ? ans * (num + 1) : ans * num;
        
        cout << '#' << test_case << ' ' << ans << '\n';
	}
	return 0;
}