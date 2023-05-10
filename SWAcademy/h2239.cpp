#include <set>
#include <unordered_map>
#include <cmath>
#include <vector>
using namespace std;

struct Car {
    int carNum;
    int timeDiff;           // 바로 직전 대기열에 추가된 차량과의 기다린 시간 차
    int arriveTime;         // 대기열에 도착한 시각
    int waitTime;           // 이전 대기열에서 기다렸던 시간 (기다린 적 없으면 0)
    int startTime;          // 주차 시작한 시각
    int totalparkingTime;   // 총 주차 시간
    bool isparked;          // 현재 주차되었는지 여부

    bool operator<(const Car& car) const {
        if (timeDiff + waitTime - totalparkingTime > car.timeDiff + car.waitTime - car.totalparkingTime)
            return true;

        if (timeDiff + waitTime - totalparkingTime == car.timeDiff + car.waitTime - car.totalparkingTime)
            return arriveTime < car.arriveTime;

        return false;
    }
};
vector<pair<int, int>> arriveList;                                  // (대기열에 도착한 시간, 바로 전에 도착한 차량과의 시간 차이) 저장
int baseTime, baseFee, unitTime, unitFee, capacity, curCapacity;
unordered_map<int, Car> carInfo;
set<Car> waiting;                                                   // 대기 차량 저장

void init(int mBaseTime, int mBaseFee, int mUnitTime, int mUnitFee, int mCapacity) 
{
    curCapacity = 0;
    arriveList.clear();
    carInfo.clear();
    waiting.clear();

    baseTime = mBaseTime, baseFee = mBaseFee, unitTime = mUnitTime, unitFee = mUnitFee, capacity = mCapacity;
}

int arrive(int mTime, int mCar)
{
    if (!carInfo.count(mCar))
        carInfo.insert({ mCar, {mCar, 0, mTime, 0, 0, 0, false} });

    if (capacity > curCapacity)                                     // 주차 가능할 경우
    {
        curCapacity++;
        carInfo[mCar].startTime = mTime, carInfo[mCar].isparked = true;
    }
    else                                                            // 주차 공간이 가득찼을 경우
    {
        if (arriveList.empty())
            arriveList.emplace_back(make_pair(mTime, 0));
        else
            arriveList.emplace_back(make_pair(mTime, arriveList.back().second + (arriveList.back().first - mTime)));
        carInfo[mCar].timeDiff = arriveList.back().second;
        carInfo[mCar].arriveTime = mTime;

        waiting.insert(carInfo[mCar]);
    }

    return waiting.size();
}

int leave(int mTime, int mCar) 
{
    if (carInfo[mCar].isparked)
    {
        carInfo[mCar].totalparkingTime += mTime - carInfo[mCar].startTime;
        carInfo[mCar].isparked = false;
        curCapacity--;

        register int fee = mTime - carInfo[mCar].startTime <= baseTime ? baseFee
            : baseFee + (int)ceil(((double)mTime - carInfo[mCar].startTime - baseTime) / unitTime) * unitFee;

        if (!waiting.empty())
        {
            register int carNum = waiting.begin()->carNum;
            waiting.erase(waiting.begin());

            carInfo[carNum].startTime = mTime;
            carInfo[carNum].waitTime += mTime - carInfo[carNum].arriveTime;
            carInfo[carNum].isparked = true;

            curCapacity++;
        }

        return fee;
    }

    waiting.erase(carInfo[mCar]);
    carInfo[mCar].waitTime += mTime - carInfo[mCar].arriveTime;

    return -1;
}
