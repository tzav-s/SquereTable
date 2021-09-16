#include <stdio.h>
#include <math.h>
#include "genlib.h"
#include "simpio.h"

#define CTS 10
#define S 3

void ReadData(int r,int s, double temper[r][s]);
double CalculateAverage(int r,int s,double temper[r][s]);
void CalculateAvCity(int r,int s,double temper[r][s],double average[r] );
void  CalculateMaxDeviation(double natavg,int r,int s, double temper[r][s],double mdeviation[r]);
void PrintResults(double natavg,int r,double average[r],double mdeviation[r]);
int main()
{
    double  temper[CTS][S];
    double average[CTS], mdeviation[CTS];
    double natavg;

	ReadData(CTS,S,temper);

	natavg=CalculateAverage(CTS,S,temper);

	CalculateAvCity(CTS,S,temper,average);

	CalculateMaxDeviation(natavg,CTS,S,temper,mdeviation);

    PrintResults(natavg,CTS,average,mdeviation);

    system("PAUSE");
    return 0;
}
void ReadData(int r,int s, double temper[r][s])
{
    int i,j;
    	/*Read all Temperatures*/
	for (i=0; i<r; i++)
		for (j=0; j<s; j++)
		  	{ printf("Temp of City %d During %d 8-hour period: ",i,j);
              temper[i][j] = GetReal();
              }
}
double CalculateAverage(int r,int s,double temper[r][s])
{
    int i,j;
    double natavg;
    /*Calculating The Average of all Cities&Temps*/
    natavg = 0;
    for (i=0; i<r; i++)
      for (j=0; j<s; j+=1)
         natavg += temper[i][j];
    natavg = natavg/(r*s);
    return natavg;
}
void CalculateAvCity(int r,int s,double temper[r][s],double average[r] )
{
    int i,j;

    /*Calculating Average temp on each City*/
	for (i=0; i<r; i++)
    {
        average[i] = 0;
        for (j=0; j<s; j++)
        {
            average[i] += temper[i][j];
        }
        average[i] = average[i]/s;
    }
}
void  CalculateMaxDeviation(double natavg,int r,int s, double temper[r][s],double mdeviation[r])
{
    int i,j;
    double devnat[r][s];
    /*Calculating Standard Deviation*/
    for (i=0; i<r; i++)
        for (j=0; j<s; j++)
            devnat[i][j] = fabs(natavg-temper[i][j]);

	/*Calculating max Deviation*/
    for (i=0; i<r; i++)
    {
        mdeviation[i] = devnat[i][0];
        for(j=1; j<s; j++)
            if (mdeviation[i]<devnat[i][j]) mdeviation[i] = devnat[i][j];
    }

}
void PrintResults(double natavg,int r,double average[r],double mdeviation[r])
{
    int i;
     /*Printing results*/
    printf("%3.1f\n", natavg);
    for (i=0; i<r; i+=1)
		printf("City %d  %.1f  %.1f\n",i, average[i], mdeviation[i]);
}
