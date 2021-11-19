#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdlib.h>
#define max(a, b) (((a) > (b)) ? (a) : (b)) //calc the maximum number
#define min(a, b) (((a) < (b)) ? (a) : (b)) //calc the minimum number

#define capacity 18          // Maximum number of people a single elevator can fit
#define floors 20            // Number of floors above the ground floor
#define stopTime 15.0        // Total time for an elevator to stop on a visited floor (in seconds)
#define movePerFloorTime 3.0 // Time for the elevator to move one floor (in seconds)

// function for qsort function
// sort from the smallest to the biggest
int cmp(const void *a, const void *b);

// generate passengers and destinations
// input: pointer to the number of passengers, an array of destination
void genPasAndDes(int *pNumPassenger, int destination[]);

// calc running time
// input: num of passengers, an array of destination floors, pointer to elevator run time, pointer to average passenger time
void calcTime(int numPassenger, int destination[], float *pElevTime, float *pAvgPasTime);

#endif