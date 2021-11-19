#include <stdlib.h>
#include "string.h"

// number of records
#define NUMDATA 2208

// define the flight data type for the flight records
typedef struct Flight
{
    char airline_code[3];
    int flight_number;
    char depart_airport[4];
    char arrival_airport[4];
    int depart_time;
    int arrival_time;
    int atlTime; // time at ATL airport (if depart from ATL, it's depart time, if arrive from ATL, it's arrvial time)
} flight;

// read the CSV file and store the data in an array of struct Flight
// array of flight and CSV file name as input
int readCSV(flight *flightData, char *file_name);

// compare the atl time of two flight records
// return 1 if f1 is greater than f2
// two flight variables as input
int compareTime(flight f1, flight f2);

// sort the flight using insertion algorithms
// array of flight as input
int insertSort(flight *flightData);

// quick sort the flights
// array of flight, start index, and end index as input
int quickSort(flight *flightData, int start, int end);

// sort the flights using heap sort
// array of flight as input
int heapSort(flight *flightData);

// find the min and max as the airplanes and gates needed and print the result
// array of flight as input
int printResult(flight *flightData);

// print the sorted array of flight
// array of flight as input
int printSort(flight *flightData);

// sort the flights based on the input, like quick, heap, and insertion
// the arguments and an array of flight as input
int sortFlights(int argc, char *argv[], flight *flightData);