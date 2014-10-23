#include <stdio.h>
#include <stdlib.h>

#define N 20
#define M 20
#define TEMP 100

void print(double array[][M])
{
	int color = 30; 
	double colorStep = TEMP / CON_COLORS;
	printf("\n");
	for (int i = 1; i < N - 1; i++)
	{
		for(int j = 1; j < M - 1; j++)
		{
			double elem = array[i][j];
			if(elem < 11) color = 37;
			if(elem > 10 & elem < 21) color = 36;
			if(elem > 20 & elem < 51) color = 32;
			if(elem > 50 & elem < 71) color = 33;
			if(elem > 70) color = 31;
			printf("\x1b[1;%d;%dm%6.1f\x1b[0m", 30, color + 10, array[i][j]);
		}
		printf("\n");
	}		
	printf("\n");
}

double prev[N][M];
double next[N][M];

int main()
{
	int time = 230, color = 0;

	if(TEMP < 11) color = 37;
	if(TEMP > 10 & TEMP < 21) color = 36;
	if(TEMP > 20 & TEMP < 51) color = 32;
	if(TEMP > 50 & TEMP < 71) color = 33;
	if(TEMP > 70) color = 31;

	for(int i = 0; i < N; ++i)
		prev[i][0] = prev[i][M-1] = next[i][0] = next[i][M-1] = TEMP;
	for(int i = 0; i < M; ++i)
		prev[0][i] = prev[N-1][i] = next[0][i] = next[N-1][i] = TEMP;

	for (int t = 1; t < time + 1; ++t)
	{
		system("clear");
		printf("\x1b[4;30mTemperature distribution at the %d second:\x1b[0m\n", t);

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
		print((time % 2 == 0) ? prev : next);
		//if time is big - change 0.1 to not laggy value
		system("sleep 0.1");
	}
	
	return 0;
}

