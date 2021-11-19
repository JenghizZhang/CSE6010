#include <stdio.h>
#include <stdlib.h>
#include "common.h"

// global variable; theses are after 1000 runs for a given maxFloor1!!
extern float minElevTime, maxElevTime, avgElevTime, finalAvgPasTime;

// calc run time and avg time once
// input: pointer to the run time, pointer to the avg time, maxFoor1, maxFloor2
void scenario4(float *pElevTime, float *pAvgPasTime, int maxFloor1, int maxFloor2)
{
    int numPassenger = 0;
    int des[20];

    int elev1[20], elev2[20], elev3[20]; // floors that each elevator goes to, respectively
    int cnt1 = 0, cnt2 = 0, cnt3 = 0;    // num of people for each elevator

    // generate number of passengers and their destinations
    genPasAndDes(&numPassenger, des);

    // assign passengers to three elevators based on their service
    for (int i = 0; i < numPassenger; i++)
    {
        if (des[i] <= maxFloor1)
        {
            elev1[cnt1++] = des[i];
        }
        else if (des[i] <= maxFloor2)
        {
            elev2[cnt2++] = des[i];
        }
        else
        {
            elev3[cnt3++] = des[i];
        }
    }
    float elevTime1 = 0, elevTime2 = 0, elevTime3 = 0;
    float avgPasTime1 = 0, avgPasTime2 = 0, avgPasTime3 = 0;

    // calc time
    calcTime(cnt1, elev1, &elevTime1, &avgPasTime1);
    calcTime(cnt2, elev2, &elevTime2, &avgPasTime2);
    calcTime(cnt3, elev3, &elevTime3, &avgPasTime3);

    float temp = max(elevTime1, elevTime2);
    *pElevTime = max(temp, elevTime3);
    *pAvgPasTime = (avgPasTime1 * cnt1 + avgPasTime2 * cnt2 + avgPasTime3 * cnt3) / numPassenger;

    // printf("time to complete the elevator run: %3f\n", *pElevTime);
    // printf("average time per passenger: %3f\n", *pAvgPasTime);
}

// repeat 1000 times to calc run time and avg time
// input: maxFoor1, maxFloor2
void scen4Repeat1000(int maxFloor1, int maxFloor2)
{
    float elevtime = 0;
    float avgPasTime = 0;
    // update global variables
    minElevTime = 65537, maxElevTime = 0, avgElevTime = 0, finalAvgPasTime = 0;

    for (int i = 0; i < 1000; i++)
    {
        scenario4(&elevtime, &avgPasTime, maxFloor1, maxFloor2);
        minElevTime = min(minElevTime, elevtime);
        maxElevTime = max(maxElevTime, elevtime);
        avgElevTime += elevtime;
        finalAvgPasTime += avgPasTime;
    }
    avgElevTime /= 1000;
    finalAvgPasTime /= 1000;

    // printf("minimum time to complete the elevator run for maxFloor1=%d & maxFloor2=%d: %3f\n", maxFloor1, maxFloor2, minElevTime);
    // printf("maximum time to complete the elevator run for maxFloor1=%d & maxFloor2=%d: %3f\n", maxFloor1, maxFloor2, maxElevTime);
    // printf("average time to complete the elevator run for maxFloor1=%d & maxFloor2=%d: %3f\n", maxFloor1, maxFloor2, avgElevTime);
    // printf("average time per passenger for maxFloor1 = %d: %3f\n", maxFloor1, finalAvgPasTime);
}

// calc the value of maxFloor1 and determine the optimum value
void scen4FindOptFloors()
{
    float optTotalTime = 65537, optAvgPasTime = 65537, optMaximumTime = 65537, optMinimumTime = 65537;
    int optTotalTimeF1 = 1, optMaxTimeF1 = 1, optAvgPasTimeF1 = 1, optMinTimeF1 = 1,
        optTotalTimeF2 = 2, optMaxTimeF2 = 2, optAvgPasTimeF2 = 2, optMinTimeF2 = 2;

    for (int maxFloor1 = 1; maxFloor1 < floors; maxFloor1++)
        for (int maxFloor2 = maxFloor1 + 1; maxFloor2 <= floors; maxFloor2++)
        {
            scen4Repeat1000(maxFloor1, maxFloor2);
            if (avgElevTime < optTotalTime)
            {
                optTotalTime = avgElevTime;
                optTotalTimeF1 = maxFloor1;
                optTotalTimeF2 = maxFloor2;
            }
            if (maxElevTime < optMaximumTime)
            {
                optMaximumTime = maxElevTime;
                optMaxTimeF1 = maxFloor1;
                optMaxTimeF2 = maxFloor2;
            }
            if (finalAvgPasTime < optAvgPasTime)
            {
                optAvgPasTime = finalAvgPasTime;
                optAvgPasTimeF1 = maxFloor1;
                optAvgPasTimeF2 = maxFloor2;
            }
            if (minElevTime < optMinimumTime)
            {
                optMinimumTime = minElevTime;
                optMinTimeF1 = maxFloor1;
                optMinTimeF2 = maxFloor2;
            }
        }
    printf("in terms of reducing the total time, optimized maxFloor1 is: %d, maxFloor2 is: %d. The result is: %3f\n",
           optTotalTimeF1, optTotalTimeF2, optTotalTime);
    printf("in terms of reducing the maximum time, optimized maxFloor1 is: %d maxFloor2 is: %d. The result is: %3f\n",
           optMaxTimeF1, optMaxTimeF2, optMaximumTime);
    printf("in terms of reducing the minimum time, optimized maxFloor1 is: %d maxFloor2 is: %d. The result is: %3f\n",
           optMinTimeF1, optMinTimeF2, optMinimumTime);
    printf("in terms of reducing the average passenger time, optimized maxFloor1 is: %d maxFloor2 is: %d. The result is: %3f\n",
           optAvgPasTimeF1, optAvgPasTimeF2, optAvgPasTime);
}