#include <stdio.h>
#include <math.h>

void
kiir (double tomb[], int db)
{
int i;
for (i=0;i<db;i++)
printf("Pagerank [%d]: %lf\n",i,tomb[i]);
}

double
tavolsag (double PR[], double PRv[], int n )
{
	int i;
	double osszeg=0;
	for (i=0;i<n;i++)
		osszeg += (PRv[i] - PR[i]) * (PRv[i] -PR[i]);
	return osszeg;
}

int
main (void)
{
	double L[4][4] = {
		{0.0, 0.0, 1.0 / 3.0, 0.0},
		{1.0, 1.0/ 2.0, 1.0 / 3.0, 1.0},
		{0.0, 1.0 / 2.0, 0.0, 0.0},
		{0.0, 0.0, 1.0 / 3.0, 0.0}
	};

	double PR[4] = { 0.0, 0.0, 0.0, 0.0 };
	double PRv[4] = { 1.0 / 4.0, 1.0 /4.0, 1.0 / 4.0, 1.0 / 4.0};

	int i, j;

	for (;;)
		{
		
		for(i=0;i<4;i++)
			PR[i] = PRv[i];
		for (i=0;i<4;i++)
		{
			double temp=0;
			for (j=0;j<4;j++)
			temp+=L[i][j]*PR[j];
			PRv[i]=temp;
		}	





		if (tavolsag (PR, PRv, 4) < 0.0000000001)
			break;


		}
	kiir (PR,4);
	return 0;
}
