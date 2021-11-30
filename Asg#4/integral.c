// gcc-11 -o integral -fopenmp integral.c -lm
// time ./integral
#include <stdio.h>
#include <math.h>
#include <omp.h>
// set the parameters including a, b, m, chunk size, and number of thread
#define a 0.0
#define b 20.0
#define m 100000000
#define NUM_THREAD 8 // number of threads
#define CHUNK 4      // chunk size

// calculate the sum of f(x_i) and f(x_i+1)
// two double parameters as input and the return type is double
double sinFloorSum(double i, double h)
{
	double x_i = a + i * h;
	return x_i * sin(floor(x_i)) + (x_i + h) * sin(floor(x_i + h));
}

// *************************** main ***************************

int main()
{
	// number of loop
	int i;
	// initialize the result
	double result = 0.0;
	// initialize parameter h
	double h = (b - a) / m;
	// set the number of threads
	omp_set_num_threads(NUM_THREAD);

	// the default type is shared and i is private for each thread
	#pragma omp parallel default(shared) private(i)
	{
		// use reduction to combine the result for each thread and set the chunk size with static type
		#pragma omp for schedule(static, CHUNK) reduction(+ : result)
			// use for loop to iterate all intervals
			for (i = 0; i < m; i++)
			{
				// calculate
				result += h / 2 * sinFloorSum(i, h);
			}
	}

	// print the results
	printf("Total number of thread: %d\n", NUM_THREAD);
	printf("m(number of subintervals): %d\n", m);
	printf("Sum: %.8lf\n", result);
	return 0;
}