#include <stdio.h>
#include <stdlib.h>
#include "common.h"

// global variable; theses are after 1000 runs for a given maxFloor1!!
float minElevTime = 65537, maxElevTime = 0, avgElevTime = 0, finalAvgPasTime = 0;

// calc run time and avg time once
// input: pointer to the run time, pointer to the avg time, maxFoor1
void scenario3(float *pElevTime, float *pAvgPasTime, int maxFloor1)
{
    int numPassenger = 0;
    int des[20];

    int elev1[20], elev2[20]; // floors that elevator1 and elevator2 goes to, respectively
    int cnt1 = 0, cnt2 = 0;   // num of people on elev1 or elev2
    // generate number of passengers and their destinations
    genPasAndDes(&numPassenger, des);

    // assign passengers to two elevators based on their service
    for (int i = 0; i < numPassenger; i++)
    {
        if (des[i] <= maxFloor1)
        {
            elev1[cnt1++] = des[i];
        }
        else
        {
            elev2[cnt2++] = des[i];
        }
    }
    float elevTime1 = 0, elevTime2 = 0;
    float avgPasTime1 = 0, avgPasTime2 = 0;

    // calc time
    calcTime(cnt1, elev1, &elevTime1, &avgPasTime1);
    calcTime(cnt2, elev2, &elevTime2, &avgPasTime2);

    *pElevTime = max(elevTime1, elevTime2);
    *pAvgPasTime = (avgPasTime1 * cnt1 + avgPasTime2 * cnt2) / numPassenger;

    // printf("time to complete the elevator run: %3f\n", *pElevTime);
    // printf("average time per passenger: %3f\n", *pAvgPasTime);
}

// repeat 1000 times to calc run time and avg time
// input: maxFoor1
void scen3Repeat1000(int maxFloor1)
{
    float elevtime = 0;
    float avgPasTime = 0;
    // update global variables
    minElevTime = 65537, maxElevTime = 0, avgElevTime = 0, finalAvgPasTime = 0;

    for (int i = 0; i < 1000; i++)
    {
        scenario3(&elevtime, &avgPasTime, maxFloor1);
        minElevTime = min(minElevTime, elevtime);
        maxElevTime = max(maxElevTime, elevtime);
        avgElevTime += elevtime;
        finalAvgPasTime += avgPasTime;
    }
    avgElevTime /= 1000;
    finalAvgPasTime /= 1000;

    // printf("minimum time to complete the elevator run for maxFloor1 = %d: %3f\n", maxFloor1, minElevTime);
    // printf("maximum time to complete the elevator run for maxFloor1 = %d: %3f\n", maxFloor1, maxElevTime);
    // printf("average time to complete the elevator run for maxFloor1 = %d: %3f\n", maxFloor1, avgElevTime);
    // printf("average time per passenger for maxFloor1 = %d: %3f\n", maxFloor1, finalAvgPasTime);
}

// calc the value of maxFloor1 and determine the optimum value
void scen3FindOptFloor()
{
    float optTotalTime = 65537, optAvgPasTime = 65537, optMaximumTime = 65537, optMinimumTime = 65537;
    int optTotalTimeF = 1, optMaxTimeF = 1, optAvgPasTimeF = 1, optMinTimeF = 1;

    for (int maxFloor1 = 1; maxFloor1 <= floors; maxFloor1++)
    {
        // vary the value of maxfoor1 to get the optimum value
        scen3Repeat1000(maxFloor1);
        if (avgElevTime < optTotalTime)
        {
            optTotalTime = avgElevTime;
            optTotalTimeF = maxFloor1;
        }
        if (maxElevTime < optMaximumTime)
        {
            optMaximumTime = maxElevTime;
            optMaxTimeF = maxFloor1;
        }
        if (finalAvgPasTime < optAvgPasTime)
        {
            optAvgPasTime = finalAvgPasTime;
            optAvgPasTimeF = maxFloor1;
        }
        if (minElevTime < optMinimumTime)
        {
            optMinimumTime = minElevTime;
            optMinTimeF = maxFloor1;
        }
    }
    printf("in terms of reducing the total time, optimized maxFloor1 is: %d, and the result is: %3f\n", optTotalTimeF, optTotalTime);
    printf("in terms of reducing the maximum time, optimized maxFloor1 is: %d, and the result is: %3f\n", optMaxTimeF, optMaximumTime);
    printf("in terms of reducing the minimum time, optimized maxFloor1 is: %d, and the result is: %3f\n", optMinTimeF, optMinimumTime);
    printf("in terms of reducing the average passenger time, optimized maxFloor1 is: %d, and the result is: %3f\n", optAvgPasTimeF, optAvgPasTime);
}