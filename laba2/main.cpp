#include "stdio.h"
#include "cmath"
//#include "iostream"
#include <fstream>
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

/*
const int n = 6;
double x_values[n] = {0.52360, 0.87267, 1.22173, 1.57080, 1.91986, 2.26893};
double y_values[n] = {0.000014, 0.00037, 0.00352, 0.01971, 0.08033, 0.26380};
*/

const int n = 6;
double x_values[n] = {0, 1, 2, 3, 4, 5};
double y_values[n] = {8, 10, 26, 92, 268, 638} ;

double newton_diff[n];
double newton[n];
double lagrange[n];
double spline[n - 1][4];




double get_Spline(double x)
{
	double ans = 0;
	for (int i = 0; i < n - 1; ++i)
		if (x >= x_values[i] && x <= x_values[i + 1])
		{
			ans = spline[i][0]
				+ spline[i][1] * x
				+ spline[i][2] * x * x
				+ spline[i][3] * x * x * x;
		}
	return ans;
}

double PpNewton(double x)
{
	if (n < 2)
		return 0;

	double ans = 0;
	double temp = 1;
	for (int i = n - 2; i >= 0; --i)
	{
		ans += temp * newton[i] * (n - i - 1);
		temp *= x;
	}
	return ans;
}

double PpNewton1(double x)
{
	if (n < 2)
		return 0;

	double ans = 0;
	for (int i = n - 2; i >= 0; --i)
	{
		ans +=  newton[i] * (n - i - 1) * pow(x, n - i - 2);

	}
	return ans;
}

double func_Newton(int l, int r)
{
	if (l == r)
		return y_values[l];
	return ((func_Newton(l + 1, r) - func_Newton(l, r - 1)) / (x_values[r] - x_values[l]));
}


vector<double> calc_polyn_newton(int m)
{
	vector<double> ans = vector<double>(m + 1);
	ans[0] = 1;
	for (int i = 1; i <= m; ++i)
	{
		for (int k = i; k > 0; --k)
		{
			ans[k] = ans[k] - ans[k - 1] * x_values[i - 1];
		}
	}
	return ans;
}

vector<double> calc_polyn_lagrange(int m)
{
	vector<double> ans = vector<double>(n);
	ans[0] = 1;
	for (int i = 1; i <= n; ++i)
	{
		if (i - 1 == m)
			continue;
		for (int k = n - 1; k > 0; --k)
		{
			ans[k] = ans[k] - ans[k - 1] * x_values[i - 1];
		}
	}

	double temp = 1;
	for (int i = 0; i < n; ++i)
		if (i != m)
			temp *= (x_values[m] - x_values[i]);

	for (int i = 0; i < n; ++i)
		ans[i] = ans[i] / temp;

	return ans;
}

void calc_Newton()
{
	for (int i = 0; i < n; ++i)
		newton_diff[i] = func_Newton(0, i);

	for (int i = 0; i < n; ++i)
	{
		vector<double> temp = calc_polyn_newton(i);

		for (int k = 0; k <= i; ++k)
			newton[n - i + k - 1] += temp[k] * newton_diff[i];
	}
}

void calc_Lagrange()
{
	for (int i = 0; i < n; ++i)
	{
		vector<double> temp = calc_polyn_lagrange(i);

		for (int k = 0; k < n; ++k)
			lagrange[k] += temp[k] * y_values[i];
	}
}

double comp_newton(double x, int k)
{
	double ans = 1;
	for (int i = 0; i < k; ++i)
		ans *= x - x_values[i];
	return ans;
}
double comp_lagrange(double x, int k)
{
	double ans = 1;
	for (int i = 0; i < n; ++i)
		if (i != k)
			ans *= (x - x_values[i]) / (x_values[k] - x_values[i]);
	return ans;
}

double get_Newton(double x)
{
	double ans = 0;
	for (int i = 0; i < n; ++i)
		ans += newton_diff[i] * comp_newton(x, i);
	return ans;
}

double PNewton(double x)
{
	double ans = 0;
	double temp = 1;
	for (int i = n - 1; i >= 0; --i)
	{
		ans += newton[i] * temp;
		temp *= x;
	}
	return ans;
}

double get_Lagrange(double x)
{
	double ans = 0;
	for (int i = 0; i < n; ++i)
		ans += y_values[i] * comp_lagrange(x, i);
	return ans;
}

double PLagrange(double x)
{
	double ans = 0;
	double temp = 1;
	for (int i = n - 1; i >= 0; --i)
	{
		ans += lagrange[i] * temp;
		temp *= x;
	}
	return ans;
}

void calc_spline()
{
	for (int i = 0; i < n - 1; ++i)
	{
		spline[i][0] = (PNewton(x_values[i + 1]) * pow(x_values[i], 2) * (3 * x_values[i + 1] - x_values[i])
			- PpNewton(x_values[i + 1]) * pow(x_values[i], 2) * x_values[i + 1] * (x_values[i + 1] - x_values[i])
			+ PNewton(x_values[i]) * pow(x_values[i + 1], 2) * (x_values[i + 1] - 3 * x_values[i])
			- PpNewton(x_values[i]) * x_values[i] * pow(x_values[i + 1], 2) * (x_values[i + 1] - x_values[i]))
			/ (pow(x_values[i + 1] - x_values[i], 3));

		spline[i][1] = (PpNewton(x_values[i + 1]) * x_values[i] * (2 * x_values[i + 1] + x_values[i]) * (x_values[i + 1] - x_values[i])
			- 6 * (PNewton(x_values[i + 1]) - PNewton(x_values[i])) * x_values[i] * x_values[i + 1]
			+ PpNewton(x_values[i]) * x_values[i + 1] * (x_values[i + 1] + 2 * x_values[i]) * (x_values[i + 1] - x_values[i]))
			/ (pow(x_values[i + 1] - x_values[i], 3));

		spline[i][2] = (3 * (PNewton(x_values[i + 1]) - PNewton(x_values[i])) * (x_values[i + 1] + x_values[i])
			- PpNewton(x_values[i + 1]) * (x_values[i + 1] - x_values[i]) * (x_values[i + 1] + 2 * x_values[i])
			- PpNewton(x_values[i]) * (x_values[i + 1] - x_values[i]) * (x_values[i] + 2 * x_values[i + 1]))
			/ (pow(x_values[i + 1] - x_values[i], 3));


		spline[i][3] = (PpNewton(x_values[i + 1]) * (x_values[i + 1] - x_values[i])
			- 2 * (PNewton(x_values[i + 1]) - PNewton(x_values[i]))
			+ PpNewton(x_values[i]) * (x_values[i + 1] - x_values[i]))
			/ (pow(x_values[i + 1] - x_values[i], 3));

	}
}


void write(ofstream &fout)
{
	fout << "NEWTON\n";
	for (int i = 0; i < n; ++i)
		fout << fixed << "x^" << n-1-i << " " << setprecision(7) << newton[i] << endl;
	fout << "\n\n\n";

    fout << "x^0" << "\t" << "x^1" << "\t" << "x^2" << "\t"  << "x^3" << endl;
	for (int i = 0; i < n - 1; ++i)
	{
        for(int j = 0; j < 4; ++j) {
            fout << spline[i][j] << setprecision(7) << "   ";
        }
        fout << endl;
	}
    fout << endl;
}

void sample(ofstream &fout)
{
    for(double x = 0; x < 3; x += 0.01) {
        fout << x << " ";
	}

	fout << endl;
	for(double x = 0; x < 3; x += 0.01) {
        fout << get_Spline(x) << " ";
	}
}

int main()
{
	ofstream fout;
	fout.open("output.txt");


	calc_Newton();
	calc_Lagrange();
	calc_spline();

	write(fout);
	fout.close();
	fout.open("sample.txt");
    sample(fout);
	fout.close();

	double x;
	while(1) {
        cin >> x;
        cout << get_Spline(x) << endl;
        cout << get_Newton(x) << endl;
	}
    return 0;
}
