#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) 
{
    vector<int> answer;
    stack<pair<int, int>> s;
    while (!progresses.empty()) {
        s.push({ progresses.back(), speeds.back() });
        progresses.pop_back();
        speeds.pop_back();
    }

    for (int day = 1; !s.empty(); day++) {
        int complete = 0;
        while (!s.empty() && s.top().first + s.top().second * day >= 100) {
            s.pop();
            complete++;
        }
        if (complete)
            answer.push_back(complete);
    }
    return answer;
}

int main()
{
    int N, C;
    cin >> N;

    vector<int> progresses, speeds;
    for (int i = 0; i < N; i++) {
        cin >> C;
        progresses.push_back(C);
    }
    for (int i = 0; i < N; i++) {
        cin >> C;
        speeds.push_back(C);
    }

    vector<int> ans = solution(progresses, speeds);
    for (int i : ans)
        cout << i << " ";
    return 0;
}