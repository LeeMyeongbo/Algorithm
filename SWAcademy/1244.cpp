#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int Max, T, change;
string arr;

void dfs(int index, int depth)
{
    if (depth == change) 
    {
        Max = max(Max, stoi(arr));
        return;
    }
    for (int first = index; first < arr.length() - 1; first++)              // 중복조합
    {
        for (int second = first + 1; second < arr.length(); second++) 
        {
            swap(arr[first], arr[second]);
            dfs(first, depth + 1);
            swap(arr[first], arr[second]);
        }
    }
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    cin >> T;
    for (int test_case = 1; test_case <= T; ++test_case) 
    {
        cin >> arr >> change;
        if (change > arr.length())		    // 교환 횟수가 문자 길이보다 길 경우
        {
            if (change % 2 && arr.length() % 2 || !(change % 2) && !(arr.length() % 2))
                change = arr.length();		// 문자 길이와 교환 횟수 모두 짝수 혹은 홀수라면 문자 길이만큼만 교환하면 답 나옴
            else
                change = arr.length() + 1;	// 그게 아니라면 최대 문자길이+1 만큼만 교환해줘도 충분!
        }
        dfs(0, 0);
        cout << "#" << test_case << " " << Max << endl;
        Max = 0;
    }
    return 0;
}
