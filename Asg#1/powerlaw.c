/*
Assignment 1, Yunsong Zhang, GTID 903625647
Description: Using least squares to fit the two parameters of a power
law for the data set(bird speeds & masses)
*/
#include <stdio.h>
#include <math.h> // include the math library
#define NUM 29    // number of data

// variables are global
// mass of the data set
double mass[NUM] = {0.0965, 0.947, 1.14, 0.058, 4.2635, 0.0075, 1.11, 0.0044, 2.641,
                    0.3545, 6.75, 6.05, 9.35, 8.19, 0.78, 1.5, 4.49, 0.096, 1.02, 3,
                    0.366, 0.088, 10.55, 9.52, 0.0087, 3.869, 2.07, 3.51, 0.0646};
// speed of the data set
double speed[NUM] = {64, 82.08, 105, 91.8, 129, 40.32, 195, 56.16, 185, 136.8,
                     135, 67.68, 88, 127, 110, 153, 90, 170, 129, 100,
                     83.52, 46.8, 80, 82.08, 43.2, 142, 113, 127, 56.33};
// matrix entries for M and b
double m11 = NUM, m12 = 0, m21 = 0, m22 = 0, b1 = 0, b2 = 0;

// function to calculate log with input as two pointers to arrays
int convertToLog(double *arr1, double *arr2);

// function to calculate matrix entries with input as two pointers to arrays
int getEntries(double *massLog, double *speedLog);

// function to calculate k0 and k1 with the address of the calculated k as the output
double *getK();

// main funcion
int main()
{
    // get two arrays by using convertToLog function
    double massLog[NUM], speedLog[NUM];
    convertToLog(mass, massLog);
    convertToLog(speed, speedLog);

    // get the matrix entries
    getEntries(massLog, speedLog);

    // get k0 and k1
    double *k;
    k = getK();

    // write k0 and k1
    printf("%.3f+%.3f\n", k[0], k[1]);

    // log(speed)=log(c)+a*log(mass)
    float c = exp(k[0]);
    float a = k[1];

    // write the results
    printf("The power law exponent is %.3f and the coefficient is %.3f\n", a, c);
    return 0;
}

// detail of convertToLog
int convertToLog(double *arr1, double *arr2)
{
    for (int i = 0; i < NUM; i++)
    {
        arr2[i] = log(arr1[i]);
    }
    return 0;
}

// detail of getEntries
int getEntries(double *massLog, double *speedLog)
{
    for (int i = 0; i < NUM; i++)
    {
        m12 += massLog[i];
        m22 += massLog[i] * massLog[i];
        b1 += speedLog[i];
        b2 += massLog[i] * speedLog[i];
    }
    m21 = m12;
    return 0;
}

// detail of getK
double *getK()
{
    // get k = inverse(M)*b
    double denominator = m11 * m22 - m12 * m21;
    double k0 = (m22 * b1 - m12 * b2) / denominator;
    double k1 = (-1 * m21 * b1 + m11 * b2) / denominator;
    static double k[2];
    k[0] = k0;
    k[1] = k1;
    return k;
}