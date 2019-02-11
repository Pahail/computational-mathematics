#include <iostream>
#include <math.h>

using namespace std;

double line (double x) {
    return 445;
}

double lorents(double x, double d) {
    double k = 1/ M_PI;
    return -k * ( d / ( pow( 0.035 * (x+2.45),2) + pow(d,2) ) ) + line(x);
}


int main()
{
    for(double d = -7; d <= 7; d += 0.01) {
        cout << d << " ";
    }
    cout << endl;
    for(double d = -7; d <= 7; d += 0.01) {
        cout << lorents(d,0.009) << " ";
    }
    return 0;
}
