#include <stdio.h>
#include <stdlib.h>
#include "common.h"

// calc run time and avg time once
// input: pointer to the run time, pointer to the avg time
void scenario1(float *pElevTime, float *pAvgPasTime)
{
    int numPassenger = 0;
    int destination[20];
    // generate number of passengers and their destinations
    genPasAndDes(&numPassenger, destination);

    // calc run time
    calcTime(numPassenger, destination, pElevTime, pAvgPasTime);

    // printf("time to complete the elevator run: %f\n", *pElevTime);
    // printf("average time per passenger: %f\n", *pAvgPasTime);
}

// repeat 1000 times to calc run time and avg time
void scen1Repeat1000()
{
    float elevtime = 0, avgPasTime = 0;
    float minElevTime = 65537, maxElevTime = 0, avgElevTime = 0, finalAvgPasTime = 0;
    for (int i = 0; i < 1000; i++)
    {
        scenario1(&elevtime, &avgPasTime);
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
