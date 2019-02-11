#include <stdio.h>
#include <math.h>

#define eps 0.000001


double fx(double x)
{
    double d = pow(10,-8);
    return atan(1 * pow(10,8) / (x + 1)) - M_PI / 2 + d;
}

double dfx(double x)
{
    double d = pow(1 / (x + pow(10,-8)),2);
    //return -1 / (d * (1/d + 1) );
    return -1 * pow(10,8) / ( pow(x,2) + 2*x + pow(10,16) + 1);
}

double ddfx(double x)
{
    double d2 = pow(1 / (x + pow(10,-8)),2);
    double d5 = pow(1 / (x + pow(10,-8)),5);
    //return (2 * d2) / (d5 * pow(1/d2 + 1, 2) );
    return 2 * pow(10,8) * (x + 1) / pow( pow(x,2) + 2*x + pow(10,16) + 1, 2);
}


double maxddfx(double a, double b, double n)
{
    double pp = 1/n;
    double i, max = 0, number;

    for (i = a; i < b; i += pp)
    {
        number = fabs(ddfx(i));
        if (number > max)
        {
            max = number;
        }
    }
    return max;
}

double minddfx(double a, double b, double n)
{
    double pp = 1/n;
    double i, number, min = fabs(dfx(a));

    for (i = a; i < b; i += pp)
    {
        number = fabs(dfx(i));
        if (number < min)
        {
            min = number;
        }
    }
    return min;
}

typedef double(*function)(double x);

int p[1];

int *localization(double bottomEdge, double topEdge, int n)
{
    int segments[1];
    int i = 0, j;

    double h = (topEdge - bottomEdge) / n;
    double z = bottomEdge;
    int counter = 0;
    while (fabs(z + h) < fabs(topEdge))
    {
        if (fx(z) * fx(z + h) <= 0)
        {
            segments[i] = counter;
            i++;
        }
        counter++;
        if (counter > 549900)
        {
            break;
        }
        z += h;
    }
    if (fx(z) * fx(topEdge) < 0)
    {
        segments[i] = counter;
        i++;
    }

    for(j = 0; j < 1; j++)
    {
        p[j] = segments[j];
    }
    return 0;
}


double solve(function fx, function dfx, double x0, double a, double b)
{
    double coef = maxddfx(a, b, 10000) / (2 * minddfx(a, b, 10000));

    if (fx(x0) * ddfx(x0) <= 0)
    {

        x0 = b;
        if (fx(x0) * ddfx(x0) <= 0)
        {
            printf("Bad initial approximation\n");
            return 0;
        }
    }

    double x1  = x0 - fx(x0)/dfx(x0);
    while ((x1-x0) * (x1-x0) * coef > eps)
    {
        x0 = x1;
        x1 = x1 - fx(x1)/dfx(x1);
    }
    return x1;

}

int main ()
{
    double mainTopEdge = 1;
    double mainBottomEdge = 0;
    int n = 1000000, i;
    double h;
    double bottom;
    double top;

    for (i = 0; i < 1; i++)
    {
        int *l = localization(mainBottomEdge, mainTopEdge, n);
        double topEdge = mainTopEdge;
        double bottomEdge = mainBottomEdge;
        h = (topEdge - bottomEdge)/n;
        bottom = bottomEdge + h * p[i];
        top = bottomEdge + h * (p[i] + 1);

        printf("From %g to %g \n", bottom, top);
        printf("Root: %0.12f\n\n",solve(fx, dfx, bottom, bottom, top));
    }
    return 0;
}
