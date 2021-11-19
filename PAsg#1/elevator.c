#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//externally defined functions
extern void scen1Repeat1000();
extern void scen2Repeat1000();
extern void scen3FindOptFloor();
extern void scen4FindOptFloors();

int main()
{
    printf("scenario1 results: \n\n");
    scen1Repeat1000();

    printf("\n\nscenario2 results: \n\n");
    scen2Repeat1000();

    printf("\n\nscenario3 results: \n\n");
    scen3FindOptFloor();

    printf("\n\nscenario4 results: \n\n");
    scen4FindOptFloors();

    return 0;
}
