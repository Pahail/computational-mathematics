#include <iostream>
#include <math.h>
#include <vector>
#include <stdio.h>
#include "stdlib.h"

using namespace std;

long double arctg1 = atanl(1.0);
long double *list;
bool *check;

long double Round(long double Argument)
{
    char s[100];
    sprintf(s, "%0.20Lf", Argument );
    //return atof(s);
    return Argument;
}


void init(int N) {
    list = (long double*)malloc( (N + 1) * sizeof(long double) );
    check = (bool*)malloc( (N + 1) * sizeof(bool));
        list[0] = list[1] =  Round(M_PI /  Round(M_PI / 4 + 1 - 5 * M_E) );
        check[0] = check[1] = true;
}


long double func(int number) {
    if(number == 0 || number == 1) {
        return Round(M_PI /  Round(M_PI / 4 + 1 - 5 * M_E));
    }
    else {
        long double last2 = (check[number - 2])? list[number - 2] : func(number - 2);
        long double last1 = (check[number - 1])? list[number - 1] : func(number - 1);

        long double result = 4 + Round(20 * M_E / M_PI * last2) -  Round(4 * last1 / M_PI) ;
        list[number] = Round( result);
        check[number] = true;
        return Round( result);
        }
}

int main()
{

    int N;
    cin >> N;
    init(N);
    func(N);
    for(int i = 0; i < N; i++) {
        //cout << list[i] << endl;
        printf("%0.16Lf\n", list[i] );
    }
    return 0;
}
