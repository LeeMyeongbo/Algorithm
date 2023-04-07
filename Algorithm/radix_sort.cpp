#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> numbers;
vector<string> strings;
int choice;

void str_radix_sort()                   // 문자열 radixSort
{
    int max_len = -1;
    queue<string> bucket[27];           // 특정 자리에 문자가 없을 수도 있으므로 [27]로 지정

    for (string& str : strings)         // 먼저 가장 긴 문자열의 길이 저장
        if ((int)str.length() > max_len)
            max_len = str.length();
    
    for (int i = max_len; i > 0; i--)                       // 가장 끝자리에 있는 문자부터 차례로 저장
    {
        int idx = 0;
        for (string& str : strings)
        {
            if (str.length() < i)
                bucket[0].push(str);                        // 길이가 짧은 문자열은 [0]에 저장
            else
                bucket[str[i - 1] - 'a' + 1].push(str);     // 그렇지 않으면 a는 [1], b는 [2], ...에 저장
        }
        for (int i = 0; i < 27; i++)
            while (!bucket[i].empty())
            {
                strings[idx++] = bucket[i].front();
                bucket[i].pop();
            }
    }
}

void num_radix_sort()                       // 숫자 radixSort(음수가 포함되면 안됨)
{
    queue<int> bucket[10];                  // 숫자는 0~9까지이므로 크기 10이면 충분
    int max = INT32_MIN;

    for (int& n : numbers)
        if (n > max)
            max = n;

    for (int i = 1; i <= max; i *= 10)      // 1의 자리 숫자, 10의 자리 숫자, 100의 자리 숫자... 순으로 살핌
    {
        int idx = 0;
        for (int& n : numbers)
            bucket[n / i % 10].push(n);
        
        for (int num = 0; num < 10; num++)
            while (!bucket[num].empty())
            {
                numbers[idx++] = bucket[num].front();
                bucket[num].pop();
            }
    }
}

int main()
{
    cout << "0 입력 시 숫자, 그 외엔 문자 : ";
    cin >> choice;

    if (!choice) 
    {
        int num;
        while (true)
        {
            cin >> num;
            if (cin.eof()) break;

            numbers.push_back(num);
        }

        num_radix_sort();

        cout << "정렬 결과\n";
        for (int& n : numbers)
            cout << n << '\n';
    }
    else
    {
        string str;
        while (true)
        {
            cin >> str;
            if (cin.eof()) break;

            strings.push_back(str);
        }

        str_radix_sort();

        cout << "정렬 결과\n";
        for (string& str : strings)
            cout << str << '\n';
    }

    return 0;
}