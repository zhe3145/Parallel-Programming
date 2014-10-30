#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP 
#include "omp.h"
#endif

#define N 2000
#define M 2000
#define TEMP 50

void print(double array[][M])
{
	printf("\n");
	for (int i = 1; i < N - 1; i++)
	{
		for(int j = 1; j < M - 1; j++)
		{
			printf("%6.2f", array[i][j]);
		}
		printf("\n");
	}		
	printf("\n");
}

double prev[N][M];
double next[N][M];

int main()
{
	int time = 2000, color = 0;
	double t1, t2;
	for(int i = 0; i < N; ++i)
	{
		prev[i][0] = next[i][0] = 0;
		prev[i][M-1] = next[i][M-1] = TEMP;
	}
	for(int i = 0; i < M; ++i)
	{
		prev[0][i] = next[0][i] = 0;
		prev[N-1][i] = next[N-1][i] = TEMP;
	}

	printf("\x1b[4;30mHeating a metal plate to %d degree.\x1b[0m\n", TEMP);
	
	t1 = omp_get_wtime();
	for (int t = 1; t < time + 1; ++t)
	{
		//#pragma omp parallel for
		for(int i = 1; i < N - 1; ++i)
		{	
			for(int j = 1; j < M - 1; ++j)
			{
				if(t % 2 == 1)
				{
					next[i][j] = 0.9 * next[i][j] + 0.0125 * (prev[i-1][j-1] + prev[i][j-1] + prev[i+1][j-1] + prev[i-1][j] + prev[i+1][j] + prev[i-1][j+1] + prev[i][j+1] + prev[i+1][j+1]); 
				}
				else
				{
					prev[i][j] = 0.9 * prev[i][j] + 0.0125 * (next[i-1][j-1] + next[i][j-1] + next[i+1][j-1] + next[i-1][j] + next[i+1][j] + next[i-1][j+1] + next[i][j+1] + next[i+1][j+1]);

				}
			}
		}	
	}
	t2 = omp_get_wtime();
	printf("\x1b[32mExecution time for %dx%d: %fs.\x1b[0m\n", N, M, t2 - t1);
	//print(time % 2 ? next : prev);
	return 0;
}

