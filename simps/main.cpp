#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    for(int i = 0; i < 30; i+=5) {
        cout << (1 - cos(i * M_PI / 180)) << " ";
    }
    for(int i = 30; i <= 120; i+=10) {
        cout << (1 - cos(i * M_PI / 180)) << " ";
    }
    cout << endl;
    return 0;
}
