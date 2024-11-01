#include <iostream>
#include <cmath>
#include <algorithm>
#include <limits>

using namespace std;

int input_check() {
    int x;
    cin >> x;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits <streamsize>::max(), '\n');
        cout << "Введите число: ";
        cin >> x;
    }
    return x;
}

int main()
{
    setlocale(LC_ALL, "Ru");
    int z, a, b;    
    
    cout << "Введите z: ";  z = input_check();

    double x = (z > 0) ? 1. / (z * z + 2 * z) : 1 - pow(z, 3);
    cout << "x = " << x << endl;

    cout << "Введите a: ";  a = input_check();
    cout << "Введите b: ";  b = input_check();

    double high = 2.5 * a * exp(-3 * x) - 4 * b * x * x,
           lnx = log(fabs(x));
    
    cout << "Какую функцию вы хотите использовать?\nЧтобы использовать 2х введите 1, чтобы использовать х^2 введите 2, чтобы использовать х/3 введите 3: ";
    char what_func = input_check();
    switch (what_func)
    {
    case '1':
        x *= 2;
        break;
    case '2':
        x *= x;
        break;
    case '3':
        x /= 3.;
        break;
    }

    cout << high / (lnx + x);
}

