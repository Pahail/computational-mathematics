#include <iostream>
#include <math.h>

using namespace std;

double line (double x) {
    return -35 * x / 13 + 850;
}

double normal(double x, double d) {
    double k = 1 / (sqrt(d*2*M_PI));
    return k * exp(- pow( 0.45 * (x - 4.12),2) / (2 * d) );
}

double porable(double x) {
    return -41.1145 * pow(x,2) + 338.7529 * x - 693.0885;
}

int main()
{
    for(double d = 3.85; d <= 4.4; d += 0.05) {
        cout << d << " ";
    }
    cout << endl;
    for(double d = 3.85; d <= 4.4; d += 0.05) {
        cout << normal(d, 0.0059)<< " ";
    }
    return 0;
}
