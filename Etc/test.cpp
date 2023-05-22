#include <iostream>
#define abs(x, y) (x - y > 0 ? x - y : y - x)
using namespace std;

int main()
{
    cout << abs(5, 6);

    return 0;
}
