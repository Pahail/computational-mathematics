#include <iostream>
#include <vector>
#include <math.h>

using namespace std;



double h;
double y_0  = 1;
double dy_0 = -101;
double lowerbound  = 0;
double upperbound  = 2;
double epsilon  = 0.000001;



double f11(double t, double y, double dy)
{
    return dy;
}

double f12(double t, double y, double dy)
{
    return -2*dy - (pow(10,4) + 2*exp(-t)) * y - 200 * cos(100*t) + exp(-t) * (pow(10,4) * cos(t - 2*sin(100*t)));
}

double f21(double t, double y, double dy)
{
    return dy + h*f12(t,y,dy)/2;
}


double f22(double t, double y, double dy)
{
    return f12(t + h/2, y + h*f11(t, y, dy)/2, dy + h*f12(t, y, dy)/2);
}

double yNext(double t, double y, double dy)
{
    return y + h*(f21(t, y, dy));
}

double dyNext(double t, double y, double dy)
{
    return dy + h*(f22(t, y, dy));
}

vector<double> findY(int L)
{
    h = (upperbound - lowerbound) / L;
    vector<double> t(L + 2);
    vector<double> y(L + 2);
    vector<double> dy(L + 2);
    t[0] = lowerbound;
    y[0] = y_0;
    dy[0] = dy_0;
    for (int i = 0; i < L + 1; i++) {
        y[i + 1] = yNext(t[i], y[i], dy[i]);
        dy[i + 1] = dyNext(t[i], y[i], dy[i]);
        t[i + 1] = lowerbound+ h*(i+1);
    }
    return y;
}

int main() {
    int L = 1000000;
    vector<double> yh = findY(L);
    vector<double> y2h = findY(L/2);
    double max = 0;
    double f;
    for (int i = 0; i < L/2 + 1; i++) {
        f = fabs(yh[2 * i] - y2h[i]);
        max = max < f ? f : max;
    }
    cout << max / 3 << endl;

    vector<double> points;
    points.push_back(0);
    points.push_back(0.5);
    points.push_back(1);
    points.push_back(1.5);
    points.push_back(2);
    vector<double> result(points.size());
    for (unsigned i = 0; i < points.size(); i++) {
        int k = (int)(points[i] / (upperbound - lowerbound) * L);
        result[i] = yh[k];
    }

    for(unsigned i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}
