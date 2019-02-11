#include <iostream>
#include <math.h>

using namespace std;

double f(double x) {
    return sin(1000*x) / (1 + x);
}
double a = 0;
double b = M_PI / 2;
int n = 3;

int main()
{
    double H = (b - a) / 4000000;
    double integral = 0;
    for(double t = a; t <= b; t+= n * H) {
        double h = (H) ;
        int i = 0;
        for(double x = t; x <= t + n * H; x+=h, i++) {
            integral +=  h * 3  * f(x) * ( (i == 0 || i == 3) ? (1) : (3) ) / 8;
        }
    }
    cout << integral << endl;
    return 0;
}
