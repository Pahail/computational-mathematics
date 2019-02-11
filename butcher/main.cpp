#include <iostream>
#include <vector>
#include <stdio.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cmath>

double EPS = 0.00000001;

class Fraction {
 private:
  int nominator;
  int denominator;
  void simplify() {
    if (denominator < 0) {
      nominator *= -1;
      denominator *= -1;
    }
    if (abs(nominator) < 2) return;
    int gcd = getGCD(std::abs(nominator), denominator);
    nominator /= gcd;
    denominator /= gcd;
  }
 public:
  Fraction(int nominator, int denominator) : nominator(nominator), denominator(denominator) {
    if (this->denominator == 0) throw std::logic_error("Division by zero.");
    simplify();
  }
  Fraction() : nominator(0), denominator(1) {}
  Fraction(const Fraction &other) : nominator(other.getNominator()), denominator(other.getDenominator()) {}
  Fraction(int value) : nominator(value), denominator(1) {}
  int getNominator() const {
    return nominator;
  }
  int getDenominator() const {
    return denominator;
  }
  double getValue() const {
    return static_cast<double>(getNominator()) / static_cast<double>(getDenominator());
  }
  int compareTo(const Fraction &other) const {
    return getNominator() * other.getDenominator() - getDenominator() * other.getNominator();
  }
  static int getGCD(int a, int b) {
    while (a != b)
      if (a > b) a -= b; else b -= a;
    return a;
  }
};

std::ostream &operator<<(std::ostream &stream, const Fraction &fraction) {
  return stream << fraction.getNominator() << "/" << fraction.getDenominator();
}

Fraction operator-(const Fraction &a) {
  return Fraction(-a.getNominator(), a.getDenominator());
}

Fraction operator+(const Fraction &a, const Fraction &b) {
  int commonDenominator = a.getDenominator() * b.getDenominator();
  int commonNominator = a.getNominator() * b.getDenominator() + b.getNominator() * a.getDenominator();
  return Fraction(commonNominator, commonDenominator);
}

Fraction operator-(const Fraction &a, const Fraction &b) {
  return a + -b;
}

Fraction operator*(const Fraction &a, const Fraction &b) {
  return Fraction(a.getNominator() * b.getNominator(), a.getDenominator() * b.getDenominator());
}

Fraction operator/(const Fraction &a, const Fraction &b) {
  return Fraction(a.getNominator() * b.getDenominator(), a.getDenominator() * b.getNominator());
}

bool operator==(const Fraction &a, const Fraction &b) { return a.compareTo(b) == 0; }
bool operator<(const Fraction &a, const Fraction &b) { return a.compareTo(b) < 0; }
bool operator>(const Fraction &a, const Fraction &b) { return a.compareTo(b) > 0; }
bool operator<=(const Fraction &a, const Fraction &b) { return a.compareTo(b) <= 0; }
bool operator>=(const Fraction &a, const Fraction &b) { return a.compareTo(b) >= 0; }

Fraction power(const Fraction &fraction, int power) {
  if (power < 0)
    return Fraction((int)pow(fraction.getDenominator(), -power), (int)pow(fraction.getNominator(), -power));
  else
    return Fraction((int)pow(fraction.getNominator(), power), (int)pow(fraction.getDenominator(), power));
}

Fraction scan() {
    int a;
    int b;
    scanf("%d/%d", &a, &b );
    if( a == 0) {
        return Fraction();
    }
    return Fraction(a, b);
}

using namespace std;

bool first1(vector<Fraction> &a, vector< vector<Fraction> > &B) {
    for(unsigned i = 0; i < a.size(); i++ ) {
        double b = 0;
        for(unsigned j = 0; j < a.size(); j++) {
            b += (B[i][j]).getValue();
        }

        if( fabs( a[i].getValue() - b   ) > EPS)
            return false;
    }
    return true;
}

bool first2(vector<Fraction> &b) {
    double d = 0;
    for( unsigned i = 0; i < b.size(); i++ ) {
        d += (b[i]).getValue();
    }
    if(fabs ( d - 1 ) > EPS ) {
        return false;
    }
    return true;
}

bool first( vector<Fraction> &a, vector<Fraction> &b, vector< vector<Fraction> > &B ) {
    if( first1(a, B) == false) return false;
    if( first2(b) == false) return false;
    return true;
}

bool second( vector<Fraction> &a, vector<Fraction> &b, vector< vector<Fraction> > &B ) {
    double d = 0;
    for( unsigned i = 0; i < a.size(); i++ ){
        d += a[i].getValue() * b[i].getValue();
    }
    if(fabs ( d - 0.5 ) > EPS ) {
        return false;
    }
    return true;

}

bool thrid1(vector<Fraction> &a, vector<Fraction> &b, vector< vector<Fraction> > &B) {
    double d = 0;
    for( unsigned i = 0; i < a.size(); i++ ){
        d += a[i].getValue() * a[i].getValue() * b[i].getValue();
    }
    if(fabs ( 3 * d - 1 ) > EPS ) {
        return false;
    }
    return true;
}

bool thrid2(vector<Fraction> &a, vector<Fraction> &b, vector< vector<Fraction> > &B) {
    double d = 0;
    for( unsigned i = 0; i < a.size(); i++ ) {
        for( unsigned k = 0; k < a.size(); k++) {
            for(unsigned l = 0; l < a.size(); l++ ) {
            d += b[i].getValue() * B[i][k].getValue() * B[k][l].getValue();
            }
        }
    }

    if(fabs ( 6 * d - 1 ) > EPS ) {
        return false;
    }
    return true;
}

bool thrid( vector<Fraction> &a, vector<Fraction> &b, vector< vector<Fraction> > &B ) {
    if( thrid1(a, b, B) == false) return false;
    if( thrid2(a, b, B) == false) return false;
    return true;
}

bool fourth1( vector<Fraction> &a, vector<Fraction> &b, vector< vector<Fraction> > &B ) {
    double d = 0;
    for( unsigned i = 0; i < a.size(); i++ ){
        d += a[i].getValue() * a[i].getValue() * a[i].getValue() * b[i].getValue();
    }
    if(fabs ( 4 * d - 1 ) > EPS ) {
        return false;
    }
    return true;
}

void printButcher( vector<Fraction> &a, vector<Fraction> &b, vector< vector<Fraction> > &B ) {
    unsigned n = a.size();
    for(unsigned i = 0; i < n; i++) {
        cout << a[i] << "   ";
        for(unsigned j = 0; j < n; j ++ ) {
            cout << B[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << "      ";
    for( unsigned i = 0; i < n; i++) {
        cout << b[i] << " ";
    }
    cout << endl;
}


int main()
{
    unsigned n = 0;
    cin >> n;
    vector<Fraction> a;
    vector<Fraction> b;
    vector< vector<Fraction> > B(n, vector<Fraction>(n));
    for( unsigned i = 0; i < n; i++) {
        a.push_back(scan());
    }
    for( unsigned i = 0; i < n; i++) {
        b.push_back(scan());
    }

    for(unsigned i = 0; i < n; i++) {
        for(unsigned j = 0; j < n; j ++ ) {
            B[i][j] = scan();
        }
    }

    cout << endl;
    printButcher(a, b, B);



    cout << "1 porjadok = " << first(a, b, B) << endl;
    cout << "2 porjadok = " << second(a,b,B) << endl;
    cout << "3 porjadok = " << thrid(a, b, B) << endl;
    cout << "4 porjadok = " << fourth1(a, b, B) << endl;

    return 0;
}
