#include "stdio.h"
#include "common.h"

// read the CSV file and store the data in an array of struct Flight
// array of flight and CSV file name as input
int readCSV(flight *flightData, char *file_name)
{
    // declare a buffer to store a line from the CSV file
    char buffer[30];
    // open file
    FILE *fp = fopen(file_name, "r");

    char *record;
    // the row # of the file
    int row = 0;

    if (fp == NULL)
    {
        // open file with error
        printf("Open Failed, check if there is a file\n");
        exit(0);
    }
    else
    {
        // open file successfully
        // iteratively scan each line of the CSV file until it becomes NULL
        while (fgets(buffer, sizeof(buffer), fp) != NULL)
        {
            // chage '\n' to '\0' to indicate the end of string
            if ((strlen(buffer) > 0) && (buffer[strlen(buffer) - 1] == '\n'))
                buffer[strlen(buffer) - 1] = '\0';
            // indicate which field of one record (airline code, flight number, etc.)
            int field = 0;
            // split the string based on ','
            record = strtok(buffer, ",");
            // loop the string to split it
            while (record != NULL)
            {
                switch (field)
                {
                case 0:
                    // set airline
                    strcpy(flightData[row].airline_code, record);
                    break;
                case 1:
                    // set flight number
                    flightData[row].flight_number = atoi(record);
                    break;
                case 2:
                    // set depart airport
                    strcpy(flightData[row].depart_airport, record);
                    break;
                case 3:
                    // set arrival airport
                    strcpy(flightData[row].arrival_airport, record);
                    break;
                case 4:
                    // set depart time
                    flightData[row].depart_time = atoi(record);
                    break;
                case 5:
                    // set arrival time
                    flightData[row].arrival_time = atoi(record);
                    // set the ATL time of the airplane
                    flightData[row].atlTime = strcmp(flightData[row].arrival_airport, "ATL") == 0 ? flightData[row].arrival_time : flightData[row].depart_time;
                    break;
                default:
                    break;
                }
                record = strtok(NULL, ",");
                field++;
            }
            row++;
        }
    }
    // close the file
    fclose(fp);
    return 1;
}

// compare the atl time of two flight records
// return 1 if f1 is greater than f2
// two flight variables as input
int compareTime(flight f1, flight f2)
{
    if ((f1.atlTime > f2.atlTime) || ((f1.atlTime == f2.atlTime) && strcmp(f1.depart_airport, "ATL") == 0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// sort the flights using insertion algorithms
// array of flight as input
int insertSort(flight *flightData)
{
    // loop the rest of data from index 1
    for (int i = 1; i < NUMDATA; i++)
    {
        // store current information
        flight record = flightData[i];
        int time = record.atlTime;
        int j;
        // loop to compare with the previous data
        for (j = i - 1; j >= 0 && (flightData[j].atlTime >= time); j--)
        {
            // if the ahead flight's arrival_airport is atlanta, don't need to change the order
            if ((flightData[j].atlTime == time) && strcmp(flightData[j].arrival_airport, "ATL") == 0)
            {
                break;
            }
            flightData[j + 1] = flightData[j];
        }
        flightData[j + 1] = record;
    }
    return 1;
}

// quick sort the flights
// array of flight, start index, and end index as input
int quickSort(flight *flightData, int start, int end)
{
    int i = start - 1;

    // set the ending condition
    if (start >= end)
    {
        return 1;
    }
    else
    {
        // still can do the partition process
        flight pivot = flightData[end];
        // loop all data except the last one as pivot
        for (int j = start; j < end; j++)
        {
            // check if the value is smaller than the pivot time or it is arrival airplane with the same value of time
            if (compareTime(pivot, flightData[j]))
            {
                i++;
                // swap the values
                flight temp = flightData[i];
                flightData[i] = flightData[j];
                flightData[j] = temp;
            }
        }
        i++;
        // swap the value
        flight temp = flightData[i];
        flightData[i] = flightData[end];
        flightData[end] = temp;
    }

    // divide the problem into subproblems
    quickSort(flightData, start, i - 1);
    quickSort(flightData, i + 1, end);
    return 1;
}

// sort the flights using heap sort
// array of flight as input
int heapSort(flight *flightData)
{
    // sort in place, loop the array to insert the data to build a max heap
    for (int i = 1; i < NUMDATA; i++)
    {
        int upIndex = i;
        // heapify up to build the max tree heap
        while (upIndex > 0)
        {
            // if the child is greater than the parent
            if (compareTime(flightData[upIndex], flightData[(int)((upIndex - 1) / 2)]) == 1)
            {
                // swap the data
                flight temp = flightData[upIndex];
                flightData[upIndex] = flightData[(int)((upIndex - 1) / 2)];
                flightData[(int)((upIndex - 1) / 2)] = temp;
                upIndex = (int)((upIndex - 1) / 2);
            }
            else
            {
                // end the heapifying process
                upIndex = 0;
            }
        }
    }

    // sort in place, loop the array to delete the max data from the heap
    for (int i = NUMDATA - 1; i > 0; i--)
    {
        // swap the last and the first
        flight temp = flightData[i];
        flightData[i] = flightData[0];
        flightData[0] = temp;

        int heapNum = i - 1;
        int downIndex = 0;
        // hepify down to make the max heap tree
        while ((downIndex * 2 + 1) <= heapNum)
        {
            int leftChild = downIndex * 2 + 1;
            int rightChild = downIndex * 2 + 2;
            // if the parent is the largest
            if (compareTime(flightData[downIndex], flightData[leftChild]) == 1 && compareTime(flightData[downIndex], flightData[rightChild]) == 1)
            {
                downIndex = heapNum;
            }
            // select the largest data and swap with its partent
            else if (compareTime(flightData[rightChild], flightData[leftChild]))
            {
                flight temp = flightData[rightChild];
                flightData[rightChild] = flightData[downIndex];
                flightData[downIndex] = temp;
                downIndex = rightChild;
            }
            else
            {
                flight temp = flightData[leftChild];
                flightData[leftChild] = flightData[downIndex];
                flightData[downIndex] = temp;
                downIndex = leftChild;
            }
        }
    }
    return 1;
}

// print the sorted array of flight
// array of flight as input
int printSort(flight *flightData)
{
    // loop the array to print the data
    for (int i = 0; i < NUMDATA; i++)
    {
        printf("%s,%d,%s,%s,%d,%d\n", flightData[i].airline_code, flightData[i].flight_number, flightData[i].depart_airport, flightData[i].arrival_airport, flightData[i].depart_time, flightData[i].arrival_time);
    }
    return 1;
}

// find the min and max as the airplanes and gates needed and print the result
// array of flight as input
int printResult(flight *flightData)
{
    int count = 0;
    int min = 0, max = 0;
    // loop the array to calculate the max and min
    // the gates needed should be the maximum number counted based on the sorted flights
    // the airplanes needed should be the minimum number counted based on the sorted flights
    for (int i = 0; i < NUMDATA; i++)
    {
        if (strcmp(flightData[i].arrival_airport, "ATL") == 0)
        {
            // arrive at atlanta, need to plus one
            count += 1;
            // max is the biggest of max and count
            max = count > max ? count : max;
        }
        else if (strcmp(flightData[i].depart_airport, "ATL") == 0)
        {
            // leave atlanta, need to minus one
            count -= 1;
            // min is the smallest of min and count
            min = count < min ? count : min;
        }
    }
    if (min < 0)
    {
        // min < 0 means we need airplane by midnight
        printf("The gates needed:%d\nThe airplanes needed at ATL by midnight:%d\n", max, -min);
    }
    else
    {
        // min < 0 means we do not need airplane by midnight
        printf("The gates needed:%d\nWe do not need airplanes parked at ATL by midnight\n", max);
    }
    return 1;
}

// sort the flights based on the input, like quick, heap, and insertion
// the arguments and an array of flight as input
int sortFlights(int argc, char *argv[], flight *flightData)
{
    char sortMethod;
    if (argc == 1)
    {
        // default is insertion sort
        printf("insertion sort\n");
        insertSort(flightData);
    }
    else if (argc == 2)
    {
        sortMethod = argv[1][0];

        switch (sortMethod)
        {
        case 'i':
            // insertion sort
            printf("insertion sort\n");
            insertSort(flightData);
            break;
        case 'q':
            // quick sort
            printf("quick sort\n");
            quickSort(flightData, 0, NUMDATA - 1);
            break;
        case 'h':
            // heap sort
            printf("heap sort\n");
            heapSort(flightData);
            break;
        default:
            printf("wrong input\n");
            return 0;
        }
    }
    return 1;
}

// *********************************************main*******************************************

int main(int argc, char *argv[])
{
    flight flightData[NUMDATA];
    // read the data from CSV file
    readCSV(flightData, "flights_file.csv");

    // sort the flights based on the arguments
    sortFlights(argc, argv, flightData);

    // you can uncomment these two lines if you want to check the sorted data
    // printf("This is the sorted record:\n");
    // printSort(flightData); // print the array of flight record

    // print the result
    printResult(flightData);
    return 0;
}
