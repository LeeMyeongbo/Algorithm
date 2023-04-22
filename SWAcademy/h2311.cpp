#include <cmath>
#include <vector>
#include <queue>
#include <set>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct Student {
    int id, dist;

    bool operator<(const Student& s) const {
        if (dist < s.dist)
            return true;                                // 학교와의 최대 거리(우선순위)가 가장 낮은 학생부터 먼저 빼냄
        else if (dist == s.dist)
            return id > s.id;                           // 그게 같다면 id가 높은 학생을 먼저 빼냄
        else
            return false;
    }
};

pair<int, int> schoolPos[10], priority[8000][10];       // schoolPos : 학교 위치, priority : 각 학생들의 (거리, 학교 id)를 저장 후 정렬
int n, cnt, capacity, assignedStudent[8000];            // i번 index의 학생이 몇 번 index의 학교에 배정되었는지 저장
unordered_map<int, int> studentHash;                    // (학생 id : 학생 순서(index))로 저장
set<Student> school[10];

Student assignSchool(Student s, int schoolID, int schoolidx)           // 어떤 학생도 배정된 학교에서 도로 나오지 않으면 {0, 0}을 반환
{
    Student ret = { 0, 0 };
    school[schoolID].insert(s);
    assignedStudent[studentHash[s.id]] = schoolidx;
    if (school[schoolID].size() > capacity)
    {
        ret = *(school[schoolID].begin());
        school[schoolID].erase(school[schoolID].begin());
    }
    
    return ret;
}

void init(int C, int N, int mX[], int mY[]) 
{
    capacity = C, n = N;
    for (int i = 0; i < N; i++)
        schoolPos[i] = { mX[i], mY[i] };

    return;
}

int add(int mStudent, int mX, int mY) 
{
    int ans = 0;

    if (!studentHash.count(mStudent))
        studentHash[mStudent] = ++cnt;

    int s_index = studentHash[mStudent];

    // 먼저 각 학교와의 거리 다 계산 + 정렬
    for (int i = 0; i < n; i++)
        priority[s_index][i] = { abs(mX - schoolPos[i].first) + abs(mY - schoolPos[i].second), i };
    sort(priority[s_index], priority[s_index] + n);

    // 그리고 현재 학생부터 학교에 배정
    int cur_student = mStudent, dist = priority[s_index][n - 1].first, school_idx = 0;
    while (true)
    {
        Student s = assignSchool({ cur_student, dist }, priority[studentHash[cur_student]][school_idx].second, school_idx);
        if (s.id == cur_student)                // 배정했던 학생이 도로 튕겨나온 경우
            school_idx++;
        else if (s.id)                          // 학생은 배정하고 다른 학생이 튕겨나온 경우
        {
            if (cur_student == mStudent)
                ans = priority[studentHash[cur_student]][school_idx].second;
            cur_student = s.id;
            dist = s.dist;
            school_idx = 0;
        }
        else                                    // 학생 배정을 모두 끝마쳤을 경우
        {
            if (cur_student == mStudent)
                ans = priority[studentHash[cur_student]][school_idx].second;
            break;
        }
    }
    return ans;
}

int remove(int mStudent)
{
    int student_idx = studentHash[mStudent];
    int school_idx = assignedStudent[student_idx];
    int schoolID = priority[student_idx][school_idx].second;
    school[schoolID].erase({ mStudent, priority[student_idx][n - 1].first });

    
    return schoolID;
}

int status(int mSchool) 
{
    return school[mSchool].size();
}
