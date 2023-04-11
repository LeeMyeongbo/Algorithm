#include <iostream>
#include <cmath>
using namespace std;

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T, skillOfMasterA, skillOfMasterB;
    int not_prime[12] = {0, 1, 4, 6, 8, 9, 10, 12, 14, 15, 16, 18};
    double comb[] = {1, 18, 3060, 18564, 43758, 48620, 43758, 18564, 3060, 816, 153, 1};    // 각각 18C0, 18C1, 18C4,..., 18C16, 18C18
    
    // 가짓수가 많을 때에는 아래처럼 nCr = (n-1)C(r-1) + (n-1)Cr 이용하는게 좋음 
    /*double comb[19][19] = {0, };
    for (int i = 1; i <= 18; i++)
        comb[i][0] = comb[i][i] = 1;
    
    for (int i = 2; i <= 18; i++)
        for (int j = 1; j < i; j++)
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j]; */
    
	cin >> T;

	for (int test_case = 1; test_case <= T; ++test_case)
	{
        double ans = 0.0;
        cin >> skillOfMasterA >> skillOfMasterB;

        double sA = skillOfMasterA / 100.0;
        double sB = skillOfMasterB / 100.0;
        for (int A = 0; A < 12; A++)
        {
            double percentOfA = comb[A] * pow(sA, not_prime[A]) * pow(1 - sA, 18 - not_prime[A]);
            for (int B = 0; B < 12; B++)
            {
                double percentOfB = comb[B] * pow(sB, not_prime[B]) * pow(1 - sB, 18 - not_prime[B]);
                ans += percentOfA * percentOfB;
            }
        }
        ans = 1 - ans;

        cout << fixed;
        cout.precision(6);
        cout << '#' << test_case << ' ' << ans << '\n';
	}
	return 0;
}