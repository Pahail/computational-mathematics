#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <fstream>

using namespace std;

// Массив расчетных точек икс
vector<double> grid;
// Массив значение сеточной функции
vector<double> gridfunction;

int N = 10;

// Нижний предел интегрирования
double lowerbound = 1;
// Верхний предел интегрирования
double upperbound = 2;
// Начальная мелкость сетки
double h = (upperbound - lowerbound) / N;
// Заданная точность
double accuracy = 0.0001;
// Начальное условие
double x_0 = 1;
double y_0 = -5;

// Правая часть уравнения dy/dx = f(x,y)
double f(double x, double y) {
    return x * pow(y,2) - y / x - 20 / pow(x,3);
}

// Метод Рунге-Кутты ( Модифицированный метод Эйлера)
double y_next(int n) {
    return gridfunction[n] + h * f(grid[n] + h / 2, gridfunction[n] + h / 2 * f(grid[n], gridfunction[n]) );
}

double y_next3(int n) {
    double f1 = f(grid[n],gridfunction[n]);
    double f2 = f(grid[n] + h/2 ,gridfunction[n] + (h * f1)/2 );
    double f3 = f(grid[n] + h ,gridfunction[n] - h * f1 + 2 * h * f2 );

    return gridfunction[n] + h * (f1 + 4 * f2 + f3) / 6;
}

// Инициализация массива рассчетных точек
void init_grid(int n) {
    int number = N * pow(2, n);
    grid.resize(number+1);
    h = ((upperbound - lowerbound) / N) * pow(0.5, n) ;
    for(int i = 0; i <= number; i++)  {
        grid[i] = (lowerbound + h * i);
    }
}

// Построение сеточной функции при заданной параметром n мелкости
void step(int n) {
    init_grid(n);
    int number = N * pow(2, n);
    gridfunction.resize(number+1);
    gridfunction[0] = y_0;
    for(int i = 0; i < number; i++)  {
        gridfunction[i + 1] = y_next(i) ;
    }
}

// Задание "равномерной" нормы в метрике 11 точек
double norm(vector<double> &a, vector<double> &b) {
    int a_step = a.size() / N;
    int b_step = b.size() / N;
    double norm = -1;
    for(int i = 0; i <= N; i++) {

        if(norm <= fabs( (a)[a_step * i] - (b)[b_step * i]  ) ) {
            norm = fabs( (a)[a_step * i] - (b)[b_step * i]  );
        }
    }
    return norm;
}

/*
void print_nearly_answers(int n) {
    step(n);
    for(unsigned i = 0; i < grid.size(); i++)  {
        cout << grid[i] << " ";
    }
    cout << endl;
    for(unsigned i = 0; i < gridfunction.size(); i++)  {
        cout << gridfunction[i] << " ";
    }
    cout << endl;
    step(n + 1);
    for(unsigned i = 0; i < grid.size(); i++)  {
        cout << grid[i] << " ";
    }
    cout << endl;
    for(unsigned i = 0; i < gridfunction.size(); i++)  {
        cout << gridfunction[i] << " ";
    }
}
*/
/*
void print_step(int n) {
    step(n);
    for(unsigned i = 0; i < grid.size(); i++)  {
        cout << grid[i] << " ";
    }int
    cout << endl;
    for(unsigned i = 0; i < gridfunction.size(); i++)  {
        cout << gridfunction[i] << " ";
    }
}
*/
void write_all_information(ofstream &fout, int n,vector<double> &grid, vector<double> &a, vector<double> &b ) {

    int a_step = a.size() / N;
    int b_step = b.size() / N;

    fout << "Between steps # " << n << " - " << n + 1 << endl;
    fout << "Knots ";
    for(int i = 0; i <= N; i++) {
        fout << setw(11) << grid[b_step * i] << setprecision(6) << " ";
    }
    fout << endl  << "Step " << n ;
    for(int i = 0; i <= N; i++) {
        fout << setw(11) << a[a_step * i] << setprecision(6) << " ";
    }
    fout << endl  << "Step " << n + 1 ;
    for(int i = 0; i <= N; i++) {
        fout << setw(11) << b[b_step * i] << setprecision(6) << " ";
    }
    fout << endl << "Diff  ";
    for(int i = 0; i <= N; i++) {
        fout << setw(11)  <<fabs( (a)[a_step * i] - (b)[b_step * i]  ) << setprecision(4) << " ";
    }
    fout << endl << "Norm     " << norm(a, b) << endl << endl << endl;
}

int main()
{
    ofstream fout;
	fout.open("output.txt");
    vector<double> temp;
    vector<double> norms;
    step(0);
    temp = gridfunction;
    for(int n = 1; n < 20; n++) {
        step(n);
        double norm1 = norm(temp, gridfunction);
        norms.push_back(norm1);
        write_all_information(fout, n - 1, grid, temp, gridfunction);
        temp = gridfunction;

    }
	fout.close();

    for(unsigned i = 0; i < norms.size(); i++) {
        if(norms[i] < accuracy) {
            cout << "Precision " << accuracy
                 <<  " reaches on step #" <<  i + 1
                 << " with h =  " << (upperbound - lowerbound) / ( N * pow(2, i+1) )
                 << " ( " <<  N * pow(2, i+1) << " knots )" << endl;
            break;
        }

	}


	cout << "Series of Norm relations" << endl;
	for(unsigned i = 1; i < norms.size(); i++) {
        cout << setw(12) << norms[i-1] / norms[i] << setprecision(6) << endl;
	}

	while(1) {
        double x;
        cin >> x;
        for(unsigned i = 1; i < grid.size(); i++) {
            if(grid[i-1] <= x && grid[i] >= x)
            {
                cout << gridfunction[i] << endl;
                break;
            }
        }
	}


    return 0;
}
