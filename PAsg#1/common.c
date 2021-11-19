#include "common.h"

// function for qsort function
// sort from the smallest to the biggest
int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b; // for sorting
}

// generate passengers and destinations
// input: pointer to the number of passengers, an array of destination
void genPasAndDes(int *pNumPassenger, int destination[])
{
    int numPassenger = rand() % capacity + 1; // 1-18

    // generate destination floor for all passengers
    for (int i = 0; i < numPassenger; i++)
    {
        destination[i] = rand() % floors + 1; // 1-20
    }

    // sorting destinations
    qsort(destination, numPassenger, sizeof(int), cmp);

    // pass the value out
    *pNumPassenger = numPassenger;
}

// calc running time
// input: num of passengers, an array of destination floors, pointer to elevator run time, pointer to average passenger time
void calcTime(int numPassenger, int destination[], float *pElevTime, float *pAvgPasTime)
{
    // check if there is no passenger in this elevator
    if (numPassenger == 0)
    {
        *pAvgPasTime = 0;
        *pElevTime = 0;
        return;
    }

    float elevTime = destination[numPassenger - 1] * movePerFloorTime; // elevator's running time
    float *timeIdv = (float *)malloc(numPassenger * sizeof(float));    // individual passenger's time cost
    timeIdv[0] = destination[0] * movePerFloorTime;                    // time cost of the fisrt passenger to leave
    int timesStopped = 1;                                              // num of times that the elevator stopped
    float avgPasTime = 0;                                              // average passenger time cost

    for (int i = 1; i < numPassenger; i++)
    {
        if (destination[i] != destination[i - 1])
        {
            // if arrive at a new floor
            timeIdv[i] = destination[i] * movePerFloorTime + stopTime * timesStopped;
            timesStopped += 1;
        }
        else
        {
            // multiple people arriving at the same floor
            timeIdv[i] = timeIdv[i - 1];
        }
        avgPasTime += timeIdv[i];
    }

    elevTime += (timesStopped - 1) * stopTime; // total elev time
    avgPasTime = avgPasTime / numPassenger;    // final average passenger time

    *pAvgPasTime = avgPasTime;
    *pElevTime = elevTime;

    free(timeIdv);
}