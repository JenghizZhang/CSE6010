// Individual Assignment#2 of CSE6010
// Author: Yunsong Zhang
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  //strcmp()
#include <stdbool.h> //bool type
#include <string.h>  //memcpy()

// define model parameters
#define f 0.05
#define k 0.063
#define ru 0.21
#define rv 0.105
// define numerical parameters
#define dx 1.6   //grid spacing
#define dt 0.5   //time spacing
#define nx 51    //number of grid points in each direction
#define nt 10000 //num of time steps

// initialize the graph with 2 arrays as input and output
void initializeGraph(float u[nx * nx], float v[nx * nx]);
// calculate the result after interation with two arrays and a boolean as input
void calculateGraph(float u[nx * nx], float v[nx * nx], bool isReflecting);
// calculate the result for boundary with two interger, four arrays and a boolean as input
void calBoundary(int i, int j, float u[nx * nx], float v[nx * nx], float uTemp[nx * nx], float vTemp[nx * nx], bool isReflecting);
// print the value with two arrays and a boolean as input
void printFinalVal(float u[nx * nx], float v[nx * nx], bool isReflecting);

// ******************** main ********************
int main(int argc, char *argv[])
{
    // default case is reflecting boundary condition
    bool isReflecting = true;
    // check whether it is periodic boundary condition
    // the command-line argument should be "p" or "-p"
    if (argc > 1 && (strcmp(argv[1], "p") || strcmp(argv[1], "-p")))
    {
        isReflecting = false;
    }

    float u[nx * nx];
    float v[nx * nx];

    // initialize the graph
    initializeGraph(u, v);
    // calculate the result
    calculateGraph(u, v, isReflecting);
    // print the result
    printFinalVal(u, v, isReflecting);
}

// *********************** Definitions ************************
// initialize the graph with 2 arrays as input and output
void initializeGraph(float u[nx * nx], float v[nx * nx])
{
    // loop the i axis
    for (int i = 0; i < nx; i++)
    {
        // loop the j axis
        for (int j = 0; j < nx; j++)
        {
            // chech whether in the box and set the corresponding values
            if (i >= 10 && i <= 20 && j >= 10 && j <= 20)
            {
                u[i * nx + j] = 0;
                v[i * nx + j] = 1;
            }
            else
            {
                u[i * nx + j] = 1;
                v[i * nx + j] = 0;
            }
        }
    }
}

// calculate the result for boundary with two interger, four arrays and a boolean as input
void calBoundary(int i, int j, float u[nx * nx], float v[nx * nx], float uTemp[nx * nx], float vTemp[nx * nx], bool isReflecting)
{
    // initiate two arrays for the neighboors of u and v
    // the value at index 0 means u_i+1,j or v_i+1,j
    // the value at index 1 means u_i-1,j or v_i-1,j
    // the value at index 2 means u_i,j+1 or v_i,j+1
    // the value at index 3 means u_i,j-1 or v_i,j-1
    float neighboorU[4];
    float neighboorV[4];

    if (isReflecting)
    {
        // for reflecting condition
        // i should be 1 when it reaches -1, which should be (i + 1) * nx + j
        if (i == 0)
        {
            neighboorU[0] = uTemp[(i + 1) * nx + j];
            neighboorV[0] = vTemp[(i + 1) * nx + j];
            neighboorU[1] = uTemp[(i + 1) * nx + j];
            neighboorV[1] = vTemp[(i + 1) * nx + j];
        }
        // i should be 1 when it reaches nx, which should be (i - 1) * nx + j
        else if (i == nx - 1)
        {
            neighboorU[0] = uTemp[(i - 1) * nx + j];
            neighboorV[0] = vTemp[(i - 1) * nx + j];
            neighboorU[1] = uTemp[(i - 1) * nx + j];
            neighboorV[1] = vTemp[(i - 1) * nx + j];
        }
        // i does not change, we should change the boundary condition at j axis
        else
        {
            neighboorU[0] = uTemp[(i - 1) * nx + j];
            neighboorV[0] = vTemp[(i - 1) * nx + j];
            neighboorU[1] = uTemp[(i + 1) * nx + j];
            neighboorV[1] = vTemp[(i + 1) * nx + j];
        }

        // j should be 1 when it reaches -1, which should be i * nx + j + 1
        if (j == 0)
        {
            neighboorU[2] = uTemp[i * nx + j + 1];
            neighboorV[2] = vTemp[i * nx + j + 1];
            neighboorU[3] = uTemp[i * nx + j + 1];
            neighboorV[3] = vTemp[i * nx + j + 1];
        }
        // j should be 1 when it reaches nx, which should be i * nx + j - 1
        else if (j == nx - 1)
        {
            neighboorU[2] = uTemp[i * nx + j - 1];
            neighboorV[2] = vTemp[i * nx + j - 1];
            neighboorU[3] = uTemp[i * nx + j - 1];
            neighboorV[3] = vTemp[i * nx + j - 1];
        }
        // j does not change, we should change the boundary condition at i axis
        else
        {
            neighboorU[2] = uTemp[i * nx + j - 1];
            neighboorV[2] = vTemp[i * nx + j - 1];
            neighboorU[3] = uTemp[i * nx + j + 1];
            neighboorV[3] = vTemp[i * nx + j + 1];
        }
    }
    else
    {
        // for periodic condition
        // i should be nx-1 when it reaches -1, which should be (nx - 1) * nx + j
        if (i == 0)
        {
            neighboorU[0] = uTemp[(nx - 1) * nx + j];
            neighboorV[0] = vTemp[(nx - 1) * nx + j];
            neighboorU[1] = uTemp[(i + 1) * nx + j];
            neighboorV[1] = vTemp[(i + 1) * nx + j];
        }
        // i should be 0 when it reaches nx, which should be j
        else if (i == nx - 1)
        {
            neighboorU[0] = uTemp[(i - 1) * nx + j];
            neighboorV[0] = vTemp[(i - 1) * nx + j];
            neighboorU[1] = uTemp[j];
            neighboorV[1] = vTemp[j];
        }
        // i does not change, we should change the boundary condition at j axis
        else
        {
            neighboorU[0] = uTemp[(i - 1) * nx + j];
            neighboorV[0] = vTemp[(i - 1) * nx + j];
            neighboorU[1] = uTemp[(i + 1) * nx + j];
            neighboorV[1] = vTemp[(i + 1) * nx + j];
        }

        // j should be nx-1 when it reaches -1, which should be i * nx + nx - 1
        if (j == 0)
        {
            neighboorU[2] = uTemp[i * nx + nx - 1];
            neighboorV[2] = vTemp[i * nx + nx - 1];
            neighboorU[3] = uTemp[i * nx + j + 1];
            neighboorV[3] = vTemp[i * nx + j + 1];
        }
        // j should be 0 when it reaches nx, which should be i * nx + 0
        else if (j == nx - 1)
        {
            neighboorU[2] = uTemp[i * nx + j - 1];
            neighboorV[2] = vTemp[i * nx + j - 1];
            neighboorU[3] = uTemp[i * nx + 0];
            neighboorV[3] = vTemp[i * nx + 0];
        }
        // j does not change, we should change the boundary condition at i axis
        else
        {
            neighboorU[2] = uTemp[i * nx + j - 1];
            neighboorV[2] = vTemp[i * nx + j - 1];
            neighboorU[3] = uTemp[i * nx + j + 1];
            neighboorV[3] = vTemp[i * nx + j + 1];
        }
    }

    // calculate the result
    u[i * nx + j] = uTemp[i * nx + j] + dt * (f * (1 - uTemp[i * nx + j]) - (uTemp[i * nx + j] * vTemp[i * nx + j] * vTemp[i * nx + j]) + ru * (neighboorU[0] + neighboorU[1] + neighboorU[2] + neighboorU[3] - 4 * uTemp[i * nx + j]) / dx / dx);
    v[i * nx + j] = vTemp[i * nx + j] + dt * (uTemp[i * nx + j] * vTemp[i * nx + j] * vTemp[i * nx + j] - (f + k) * vTemp[i * nx + j] + rv * (neighboorV[0] + neighboorV[1] + neighboorV[2] + neighboorV[3] - 4 * vTemp[i * nx + j]) / dx / dx);
}

// calculate the result after interation with two arrays and a boolean as input
void calculateGraph(float u[nx * nx], float v[nx * nx], bool isReflecting)
{
    float uTemp[nx * nx];
    float vTemp[nx * nx];

    // iterate several times
    for (int t = 0; t < nt; t++)
    {
        // copy the value from u and v to uTemp and vTemp
        memcpy(uTemp, u, sizeof(uTemp));
        memcpy(vTemp, v, sizeof(vTemp));

        // iterate i axis
        for (int i = 0; i < nx; i++)
        {
            // iterate j axis
            for (int j = 0; j < nx; j++)
            {
                // boundary that need to be considered
                if (i == 0 || i == nx - 1 || j == 0 || j == nx - 1)
                {
                    calBoundary(i, j, u, v, uTemp, vTemp, isReflecting);
                }
                else
                {
                    // u and v in next time step
                    // calculate the result
                    u[i * nx + j] = uTemp[i * nx + j] + dt * (f * (1 - uTemp[i * nx + j]) - (uTemp[i * nx + j] * vTemp[i * nx + j] * vTemp[i * nx + j]) + ru * (uTemp[(i + 1) * nx + j] + uTemp[(i - 1) * nx + j] + uTemp[i * nx + j + 1] + uTemp[i * nx + j - 1] - 4 * uTemp[i * nx + j]) / dx / dx);
                    v[i * nx + j] = vTemp[i * nx + j] + dt * (uTemp[i * nx + j] * vTemp[i * nx + j] * vTemp[i * nx + j] - (f + k) * vTemp[i * nx + j] + rv * (vTemp[(i + 1) * nx + j] + vTemp[(i - 1) * nx + j] + vTemp[i * nx + j + 1] + vTemp[i * nx + j - 1] - 4 * vTemp[i * nx + j]) / dx / dx);
                }
            }
        }
    }
}

// print the value with two arrays and a boolean as input
void printFinalVal(float u[nx * nx], float v[nx * nx], bool isReflecting)
{
    // print which condition we use
    if (isReflecting)
    {
        printf("****************** Using Reflecting Condition******************\n");
    }
    else
    {
        printf("****************** Using Periodic Condition******************\n");
    }

    // printf("****************** u(i,j) ******************\n");
    // for (int i = 0; i < nx; i++)
    // {
    //     for (int j = 0; j < nx; j++)
    //     {
    //         printf("%c", u[i* nx+j] > 0.25 ? 'X' : ' ');
    //     }
    //     printf("\n");
    // }

    printf("****************** v(i,j) ******************\n");
    // loop the i axis
    for (int i = 0; i < nx; i++)
    {
        // loop the j axis
        for (int j = 0; j < nx; j++)
        {
            // if it is greater than 0.25, it will print X
            printf("%s", v[i * nx + j] > 0.25 ? "X " : "  ");
        }
        printf("\n");
    }
}
