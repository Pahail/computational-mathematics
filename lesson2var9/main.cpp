/*
#include <iostream>
#include <math.h>

using namespace std;

double func(double argument) {
    double d = pow(10,-8);
    return atan(1 / (argument + d)) - M_PI / 2 + d;
}

typedef double (*function)(double x);

double TangentsMethod(function f, function df, double x0, double eps) {
    double x1 = 0;//  = xn - f(xn)/df(xn);
    int n = 0;
    while(n++ < 10)
    {
        x1 = x0 - f(x0)/df(x0);
        x0 = x1;
        cout << x0 << endl;
    }
    return x1;
}

double f1(double x) {
    return cos(x);

    }

double f2(double x) {
    return -sin(x);
}

//Выбор начального приближения
//xn = MyFunction(A)*My2Derivative(A) > 0 ? B : A;

double der1func(double x) {
    double d = pow(1 / (x + pow(10,-8)),2);
    return -1 / (d * (1/d + 1) );
}

double der2func(double x) {
    double d2 = pow(1 / (x + pow(10,-8)),2);
    double d5 = pow(1 / (x + pow(10,-8)),5);
    return (2 * d2) / (d5 * pow(1/d2 + 1, 2) );
}


int main()
{

    for(double d = -100; d < 100; d += 0.1) {
        cout << d << " ";
    }
    cout << endl;
    for(double d = -100; d < 100; d += 0.1) {
        cout << func(d) << " ";
    }

    cout <<"lol " << der2func(0) << endl;

    //double xn = func()*der2func() > 0 ? 0.1 : 0.01;
    double x = TangentsMethod(f1, f2, -0.5 * pow(10,-8) , 0.01);
    return 0;
}
*/
// Метод_Ньютона.cpp: определяет точку входа для консольного приложения

//#include <stdafx.h>

#include <iostream>
#include <math.h>

using namespace std;

float f(double x) //возвращает значение функции f(x) = x^2-2

{

    double d = pow(10,-8);
    return atan(1 / (x + d)) - M_PI / 2 + d;

}

float df(float x) //возвращает значение производной

{
    double d = pow(1 / (x + pow(10,-8)),2);
    return -1 / (d * (1/d + 1) );

}

float d2f(float x) // значение второй производной

{
    double d2 = pow(1 / (x + pow(10,-8)),2);
    double d5 = pow(1 / (x + pow(10,-8)),5);
    return (2 * d2) / (d5 * pow(1/d2 + 1, 2) );

}

int main()

{

       int exit = 0, i=0;//переменные для выхода и цикла

       double x0,xn;// вычисляемые приближения для корня

       double a, b, eps;// границы отрезка и необходимая точность

             do {

                    i=0;

                    cout<<"Please input [a;b]\n=>";

                    cin>>a>>b; // вводим границы отрезка, на котором будем искать корень

                    cout<<"\nPlease input epsilon\n=>";

                    cin>>eps; // вводим нужную точность вычислений

                    if (a > b) // если пользователь перепутал границы отрезка, меняем их местами

                           {

                                  x0 = a;

                                  a = b;

                                  b = x0;

                           }

                    if (0) // если знаки функции на краях отрезка одинаковые, то здесь нет корня

                                  cout<<"\nError! No roots in this interval\n";

                           else

                           {

                           if (f(a)*d2f(a)>0) x0  = a; // для выбора начальной точки проверяем f(x0)*d2f(x0)>0 ?

                                  else x0 = b;

                           xn = x0-f(x0)/df(x0); // считаем первое приближение

                           cout<<++i<<"-th iteration = "<<xn<<"\n";

                           while(fabs(x0-xn) > eps) // пока не достигнем необходимой точности, будет продолжать вычислять

                           {

                                  x0 = xn;

                                  xn = x0-f(x0)/df(x0); // непосредственно формула Ньютона

                                  cout<<++i<<"-th iteration = "<<xn<<"\n";

                           }

                    cout<<"\nRoot = "<<xn; // вывод вычисленного корня

                    }

                    cout<<"\nExit?=>";

                    cin>>exit;

             } while (exit!=1); // пока пользователь не ввел exit = 1

       return 0;

}
