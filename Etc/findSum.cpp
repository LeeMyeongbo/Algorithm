#include <iostream>
#include <algorithm>
using namespace std;

bool find_Sum(int arr1[], int arr2[], int sum)
{
    sort(arr1, arr1 + 10);
    sort(arr2, arr2 + 10);

    int left = 0, right = 9;

    while (left < 10 && right >= 0)
    {
        if (arr1[left] + arr2[right] == sum)
        {
            cout << arr1[left] << " + " << arr2[right] << " = " << sum << '\n';
            return true;
        }
        else
        {
            if (arr1[left] + arr2[right] < sum)
                left++;
            else
                right--;
        }
    }

    return false;
}

int main()
{
    int arr1[10] = {0, };
    int arr2[10] = {0, };
    int sum;

    cout << "배열 2개 입력(크기 10)\n";

    for (int i = 0; i < 10; i++)
        cin >> arr1[i];
    
    for (int i = 0; i < 10; i++)
        cin >> arr2[i];

    cout << "찾으려는 합 : ";
    cin >> sum;

    find_Sum(arr1, arr2, sum) ? cout << "찾음!!\n" : cout << "못찾음 ㅠㅠ\n";

    return 0;
}