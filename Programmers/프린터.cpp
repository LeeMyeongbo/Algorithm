#include <string>
#include <vector>

using namespace std;

int solution(vector<int> priorities, int location) 
{
    int answer = 0, seq = 0;
    vector<pair<int, int>> print_que;
    for (int i : priorities)
        print_que.push_back({ i, seq++ });

    while (true) {
        pair<int, int> p = print_que.front();
        bool complete = true;
        print_que.erase(print_que.begin());

        for (pair<int, int>& pr : print_que) {
            if (pr.first > p.first) {
                print_que.push_back(p);
                complete = false;
                break;
            }
        }
        if (complete) {
            answer++;
            if (p.second == location)
                break;
        }
    }
    return answer;
}