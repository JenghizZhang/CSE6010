#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int elev1[20], elev2[20]; //destination array for each elevator
int cnt1 = 0, cnt2 = 0;   // num of passgeners for each elevator

// calc run time and avg time once
// input: pointer to the run time, pointer to the avg time
void scenario2(float *pElevTime, float *pAvgPasTime)
{
    int numPassenger = 0;
    int des[20];
    // generate number of passengers and their destinations
    genPasAndDes(&numPassenger, des);

    // assign passengers to two elevators randomly
    cnt1 = 0;
    cnt2 = 0;
    for (int i = 0; i < numPassenger; i++)
    {
        if (rand() % 2 == 1)
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
void scen2Repeat1000()
{
    float elevtime = 0;
    float avgPasTime = 0;
    float minElevTime = 65537, maxElevTime = 0, avgElevTime = 0, finalAvgPasTime = 0;
    for (int i = 0; i < 1000; i++)
    {
        scenario2(&elevtime, &avgPasTime);
        minElevTime = min(minElevTime, elevtime);
        maxElevTime = max(maxElevTime, elevtime);
        avgElevTime += elevtime;
        finalAvgPasTime += avgPasTime;
    }
    avgElevTime /= 1000;
    finalAvgPasTime /= 1000;
    printf("minimum time to complete the elevator run: %3f\n", minElevTime);
    printf("maximum time to complete the elevator run: %3f\n", maxElevTime);
    printf("average time to complete the elevator run: %3f\n", avgElevTime);
    printf("average time per passenger: %3f\n", finalAvgPasTime);
}