#include <iostream>
#include <math.h>
#include <vector>

using namespace std;




double a = 0;
double b = M_PI;
double y_0 = 0;
double yN = pow(M_PI,2);
vector<double> X;
double H;

double q_(double x)
{
    return x*x - 2;
}

double c_(int n)
{
    return 1 + q_(X[n]) * H / 2;
}

double a_(int n)
{
    return 1 - q_(X[n]) * H / 2;
}

double p_(double x)
{
    return q_(x) * cos(x);
}

double b_(int n)
{
    return a_(n) + c_(n) + H * H * p_(X[n]);
}

double f(double x)
{
    return pow(M_E,x)*x*x*cos(x) + 2 + 2*pow(x,3) - pow(x,4) + 2*x*x;
}

double d_(int n)
{
    return H * H * f(X[n]);
}


vector<double> createP(int N)
{
    vector<double> P(N+1);
    P[1] = 0;
    for (int i = 1; i < N; i++) {
            P[i+1] = c_(i) / (b_(i) - a_(i) * P[i]);
    }
    return P;
}

vector<double> createQ(int N, vector<double> P)
{
    vector<double> Q(N+1);
    Q[1] = y_0;
    for (int i = 1; i < N; i++) {
        Q[i+1] = (a_(i) * Q[i] - d_(i)) / (b_(i) - a_(i) * P[i]);
    }
    return Q;
}

vector<double> createY(int N, vector<double> P, vector<double> Q)
{
    vector<double> Y(N+1);
    Y[N] = yN;
    for (int i = N; i > 0; i--)
    {
        Y[i - 1] = P[i] * Y[i] + Q[i];
    }
    return Y;
}

 void rebuildPointsAndH(int N){
    double h = (b - a)/(N - 1);
    vector<double> x(N);
    for (int i = 0; i < N; i++) {
        x[i] = a + h*i;
    }
    H = h;
    X = x;
}

int main()
{
    int N = 10000;
    rebuildPointsAndH(N);
    vector<double> P = createP(N);
    vector<double> Q = createQ(N, P);
    vector<double> Y = createY(N, P, Q);
    vector<double> points;
    points.push_back(0.5);
    points.push_back(1);
    points.push_back(1.5);
    points.push_back(2);
    points.push_back(2.5);
    vector<double> result(6);
    for (int i = 0; i < 6; i++) {
            int k = (int)(points[i] / (b - a) * N);
            result[i] = (Y[k] + Y[k + 1]) / 2;
    }

    for(unsigned i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;
}



