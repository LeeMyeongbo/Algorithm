#include <string>
#include <list>
#include <unordered_map>
using namespace std;

unordered_map<string, int> user[1000];            // 사용자별로 {일정 이름 : 그룹 id} 형태로 저장
unordered_map<string, list<int>> group[100];      // 그룹 별로 {일정 이름 : 사용자 id 목록} 형태로 저장

void init()
{
    for (register int i = 0; i < 1000; i++)
        user[i].clear();

    for (register int i = 0; i < 100; i++)
        group[i].clear();
}

void addEvent(int uid, char ename[], int groupid)
{
    string name(ename);
    user[uid].insert({ name, groupid });
    
    if (!group[groupid].count(name))
    {
        list<int> l;
        l.push_back(uid);
        group[groupid].insert({ name, l });       // 항상 master 일정을 맨 앞에 저장
    }
    else
        group[groupid][name].push_back(uid);
}

int deleteEvent(int uid, char ename[])
{
    string name(ename);
    if (!user[uid].count(name))
        return 0;

    register int groupid = user[uid][name], size = group[groupid][name].size();
    register auto it = group[groupid][name].begin();

    if (*it == uid)                                     // 삭제되는 일정이 master인 경우 같은 이름의 일정들 모두 삭제
    {
        for (int& userid : group[groupid][name])
            user[userid].erase(name);
        group[groupid].erase(name);

        return size;
    }
    else                                                // normal이면 하나하나 순회하며 uid 찾고 해당 일정만 삭제
    {
        for (; it != group[groupid][name].end(); it++)
        {
            if (*it == uid)
            {
                user[uid].erase(name);
                group[groupid][name].erase(it);

                return 1;
            }
        }
    }

    return 0;
}

int changeEvent(int uid, char ename[], char cname[])
{
    string name(ename), new_name(cname);
    if (!user[uid].count(name))
        return 0;

    register int groupid = user[uid][name], size = group[groupid][name].size();
    register auto it = group[groupid][name].begin();

    if (*it == uid)                                         // 변경되는 일정이 master인 경우
    {
        list<int> l = group[groupid][name];
        for (int& userid : l)
        {
            user[userid].erase(name);
            user[userid].insert({ new_name, groupid });
        }
        group[groupid].erase(name);
        group[groupid].insert({ new_name, l });

        return size;
    }
    else                                                    // normal인 경우 삭제하고 변경된 일정의 맨 앞에 저장
    {
        for (; it != group[groupid][name].end(); it++)
        {
            if (*it == uid)
            {
                user[uid].erase(name);
                user[uid].insert({ new_name, groupid });
                group[groupid][name].erase(it);

                list<int> l;
                l.push_back(uid);
                group[groupid].insert({ new_name, l });

                return 1;
            }
        }
    }

    return 0;
}

int getCount(int uid)
{
    return user[uid].size();
}
