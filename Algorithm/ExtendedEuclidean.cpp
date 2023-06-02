#include <iostream>
using namespace std;

struct Node {
    int gcd, s, t;
};

Node extendedEuclidean(int a, int b)
{
    register int s1 = 1, s2 = 0, t1 = 0, t2 = 1;

    while (b)
    {
        int q = a / b;

        int r = a - q * b;
        a = b, b = r;

        int s = s1 - q * s2;
        s1 = s2, s2 = s;

        int t = t1 - q * t2;
        t1 = t2, t2 = t;
    }

    return { a, s1, t1 };   // a = gcd(a, b), s1 = s, t1 = t
}

int main()                  // a*s + b*t = gcd(a, b)를 만족시키는 정수 s, t 탐색
{
    register int a, b;
    cin >> a >> b;

    Node ans = extendedEuclidean(a, b);

    cout << a << " * " << ans.s << " + " << b << " * " << ans.t << " = " << ans.gcd << endl;

    return 0;
}
