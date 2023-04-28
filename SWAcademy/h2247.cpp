#include <unordered_map>
#include <set>
#include <cstring>
using namespace std;

struct Machine {
    int id, produce;

    bool operator<(const Machine& m) const {
        if (produce > m.produce)
            return true;
        if (produce == m.produce)
            return id > m.id;
        return false;
    }
};
unordered_map<int, int> machineExist;
set<Machine> machines;
int producing[3001];

void init(int N, int mId[], int mTime[]) 
{
    memset(producing, 0, sizeof(producing));
    machineExist.clear();
    machines.clear();

    for (register int i = 0; i < N; i++)
    {
        machineExist.insert({ mId[i], mTime[i] });
        machines.insert({ mId[i], mTime[i] });
        producing[mTime[i]]++;
    }
}

int add(int mId, int mTime) 
{
    if (!machineExist.count(mId))
        machineExist.insert({ mId, mTime });
    else
    {
        register int mtime = machineExist[mId];
        machineExist[mId] = mTime;

        machines.erase({ mId, mtime });
        producing[mtime]--;
    }
    machines.insert({ mId, mTime });
    producing[mTime]++;

    return machineExist.size();
}

int remove(int K) 
{
    for (register int i = 0; i < K; i++)
    {
        register Machine machine = *machines.begin();

        machineExist.erase(machine.id);
        machines.erase(machine);
        producing[machine.produce]--;
    }

    return machines.begin()->id;
}

int produce(int M) 
{
    int max_p = machines.begin()->produce, start = 3, end = max_p * M, mid, ans = 0;

    while (start <= end)
    {
        mid = (start + end) >> 1;

        register int product = 0;
        for (int i = 3; i <= max_p && product < M; i++)
            if (producing[i])
                product += mid / i * producing[i];

        if (product < M)
            start = mid + 1;
        else
        {
            ans = mid;
            end = mid - 1;
        }
    }

    return ans;
}
