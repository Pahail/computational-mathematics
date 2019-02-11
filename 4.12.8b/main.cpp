#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;
double eps = 0.0005;

double f1(double x) {
    return pow(M_E,pow(x,2)) / sqrt(8*M_E);
}

double f2(double x) {
    return sqrt(log(sqrt(8*M_E) * x ));
}

int main()
{
    double x0 = -1;
    double ans = 0.01;
    while(fabs(x0 - ans) > eps) {
        x0 = ans;
        ans = f1(x0);
    }
    printf("%g\n", ans);
    x0 = -1;
    ans = 1.01;
    while(fabs(x0 - ans) > eps) {
        x0 = ans;
        ans = f2(x0);
    }
    printf("%g\n", ans);
    return 0;
}
