// Berke Algül 040230762

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double ln(unsigned long long x, int n);

int main()
{
    unsigned long long x;
    double t = 1E-3;
    int n;

    srand(time(NULL)); 
    x = rand() * rand() * rand();

    double logx = log(x);
    double error = t;

    while(error >= t)
    {
        n++;
        double lnx = ln(x, n);
        error = fabs(lnx-logx);
        printf("Iteration %d\nx\t= %llu\nlog(x)\t= %f\nln(x)\t= %lf\nError\t= %lf\n\n", n, x, logx, lnx, error);
    }

    return 0;
}

double ln(unsigned long long x, int n)
{
    if(x <= 0)
    {
        printf("Invalid argument!");
        exit(1);
    }

    double lnx = 0;
    for(int i = 0; i < n; i++)
    {
        lnx += 2 * ((x-exp(lnx)) / (x+exp(lnx)));
    }

    return lnx;
}