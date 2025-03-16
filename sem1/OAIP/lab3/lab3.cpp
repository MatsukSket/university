#include <iostream>
#include <cmath>
#include <iomanip>

#define setprec setprecision(6) << fixed

using namespace std;

double a, b, h, n;
int l;
const double eps = 0.0001; //погрешность

double find_Y(double x)
{
    return (x * x / 4 + x / 2 + 1) * exp(x / 2);
}

double find_S(double x, double y, double s, double k, double sk)
{   
    int k1 = k - 1;
    
    if (k == 0)
        sk = 1;
    else 
        sk = sk / (k1 * k1 + 1) * (k * k + 1) / k * x / 2;

    s += sk;

    l = k;
    return (fabs(s - y) < eps) ? s : find_S(x, y, s, k + 1, sk);
}

int main()
{
    cout << "Enter min value: ";    cin >> a;
    cout << "Enter max value: ";    cin >> b;
    cout << "Enter step: ";         cin >> h;

    double val_Y, val_S;
    for (double x = a; x <= b; x += h) {
        val_Y = find_Y(x);
        val_S = find_S(x, val_Y, 0, 0, 0);
        int count = l;

        cout << "for " << setprecision(1) << fixed << x << "  #  ";
        cout << "Y(x) = " << setprec << val_Y << "  #  " << defaultfloat;
        cout << "S(x) = " << setprec << val_S << "  #  ";
        cout << "|Y(x) - S(x)| = " << fabs(val_S - val_Y) << endl;
    }
}