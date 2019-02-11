#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

long double gamma_0 = 5.0 / 3;
long double gamma_3 = gamma_0;
long double P_0 = 3.04 * pow(10,9);
long double ro_0 = 7.9;
long double P_3 = 1.17928 * pow(10,9);
long double ro_3 = 11.37;
long double U_0 = 0.0;
long double U_3 = 50000;


long double alpha_0 = (gamma_0 + 1) / (gamma_0 - 1);
long double alpha_3 = (gamma_3 + 1) / (gamma_3 - 1);
long double c_0 = sqrt(gamma_0 * P_0 / ro_0);
long double c_3 = sqrt(gamma_3 * P_3 / ro_3);
long double X = P_3 / P_0;
long double e_0 = 2*(c_0 * c_0) / (gamma_0 * (gamma_0 - 1) * (U_3 - U_0) * (U_3 - U_0) );
long double e_3 = 2*(c_3 * c_3) / (gamma_3 * (gamma_3 - 1) * (U_3 - U_0) * (U_3 - U_0) );


long double a_0_coef() {
    return pow(alpha_0 * e_3 - alpha_3 * X * e_0, 2);
}

long double a_1_coef() {
    long double temp1 = alpha_0 * e_3 - alpha_3 * X * e_0;
    long double temp2 = alpha_0 * e_3 + alpha_3 * X * e_0;

    return 2 * (temp1 * (e_3 * (1 - 2 * alpha_0 * X) - e_0 * X * (X - 2 * alpha_3)) - alpha_0 * alpha_3 * X * temp2 );
}

long double a_2_coef() {
    long double temp1 = pow(e_3,2) * (6 * pow(alpha_0,2) * pow(X,2) - 8 * alpha_0 * X + 1 );
    long double temp2 = 2 * e_0 * e_3 * X * (alpha_0 * alpha_3 * ( pow(X,2) + 4 * X + 1) - 2 * (X + 1) * (alpha_3 + alpha_0 * X) + X );
    long double temp3 = pow(e_0,2) * pow(X,2) * (6 * pow(alpha_3,2) - 8 * alpha_3 * X + pow(X,2)) + pow(alpha_0,2) * pow(alpha_3,2) * pow(X,2);
    long double temp4 = 2 * alpha_0 * X * e_3 * (alpha_0 * X - 2 * alpha_0 * alpha_3 * X + 2 * alpha_3);
    long double temp5 = 2 * alpha_3 * pow(X,2) * e_0 * (alpha_3 + 2 * alpha_0 * X - 2 * alpha_0 * alpha_3);
    return temp1 - temp2 + temp3 - temp4 - temp5;
}

long double a_3_coef() {
    long double temp1 = 2 * pow(e_3,2) * (pow(alpha_0,2) * pow(X,2) - 3 * alpha_0 * X + 1 );
    long double temp2 = (alpha_3 + alpha_0 * X) * ( pow(X,2) + 4 * X + 1) - 2 * alpha_0 * alpha_3 * X * (X + 1) - 2 * X * (X + 1);
    long double temp3 = 2 * pow(e_0,2) * X * (pow(X,2) - 3 * alpha_3 * X + pow(alpha_3,2) ) - alpha_0 * alpha_3 * X * (alpha_0 * X + alpha_3);
    long double temp4 = e_3 * (pow(alpha_0,2) * alpha_3 * pow(X,2) - 2 * X * (2 *alpha_0 * alpha_3 + pow(alpha_0,2) * X) + (2 * alpha_0 * X + alpha_3));
    long double temp5 = e_0 * X * ( alpha_0 * pow(alpha_3,2) - 2 * alpha_3 * (alpha_3 + 2 * alpha_0 * X) + 2 * alpha_3 * X + alpha_0 * pow(X,2));
    return -2 * X * (temp1 + e_0 * e_3 * temp2 + temp3 + temp4 + temp5);
}

long double a_4_coef() {
    long double temp1 = pow(e_3,2) * ( pow(alpha_0,2) * pow(X,2) - 8 * alpha_0 * X + 6);
    long double temp2 = 2 * e_0 * e_3 * (alpha_0 * alpha_3 * X - 2 * (X + 1) * (alpha_3 + alpha_0 * X) + pow(X,2) + 4 * X + 1 );
    long double temp3 = pow(e_0,2) * (pow(alpha_3,2) - 8 * alpha_3 * X + 6 * pow(X,2) ) + (pow(alpha_3,2) + 4 * alpha_0 * alpha_3 * X + pow(alpha_0,2) * pow(X,2));
    long double temp4 = 2 * e_3 * ( (pow(alpha_3,2) * X + 2 * alpha_0 * alpha_3) * X - 2 * (2 * alpha_0 * X + alpha_3) + 1);
    long double temp5 = 2 * e_0 * ( alpha_3 * (2 * alpha_0 * X + alpha_3) - 2 * X * (2 * alpha_3 + alpha_0 * X) + pow(X,2));
    return pow(X,2) * ( temp1 - temp2 + temp3 - temp4 - temp5);
}

long double a_5_coef() {
    long double temp1 = pow(e_3,2) * (alpha_0 * X - 2) - e_0 * e_3 * (alpha_0 * X - 2 + alpha_3 - 2 * X);
    long double temp2 = pow(e_0,2) * (alpha_3 - 2 * X) + (alpha_3 + alpha_0 * X);
    long double temp3 = e_3 * ( 2 * alpha_0 * X + alpha_3 - 2) + e_0 * (2 * alpha_3 + alpha_0 * X - 2 * X);
    return 2 * pow(X,3) * (temp1 + temp2 - temp3);
}

long double a_6_coef() {
    return pow(X,4) * ( pow(e_3 - e_0, 2) + 1 - 2 * (e_3 + e_0)  );
}

void print_coef() {
    cout << "a0: "<< a_0_coef() << endl;
    cout << "a1: "<< a_1_coef() << endl;
    cout << "a2: "<< a_2_coef() << endl;
    cout << "a3: "<< a_3_coef() << endl;
    cout << "a4: "<< a_4_coef() << endl;
    cout << "a5: "<< a_5_coef() << endl;
    cout << "a6: "<< a_6_coef() << endl;
}

void print_series(double from, double to, double step) {
    for( double dx = from; dx < to; dx += step ) {
        cout << dx << " ";
    }
    cout << endl;
    for( double dx = from; dx < to; dx += step ) {
        cout << pow(dx, 6) * a_0_coef() + pow(dx,5) * a_1_coef() + pow(dx,4)  * a_2_coef() + pow(dx,3) * a_3_coef() + pow(dx,2) * a_4_coef() + dx * a_5_coef() + a_6_coef() << " ";
    }
}

int main()
{
    print_coef();
    //print_series(-1000, 1000, 0.5);
    return 0;
}
