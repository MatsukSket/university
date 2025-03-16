#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
double x, y, z, a, b, c, d, h;

int main()
{
    setlocale(LC_ALL, "Ru");
    x = 0.1722; y = 6.330; z = 3.25e-4;
    //cout << "Введите x: ";    cin >> x;
    //cout << "Введите y: ";    cin >> y;
    //cout << "Введите z: ";    cin >> z;

    a = 5. * atan(x);
    b = 1 / 4. * acos(x);
    h = fabs(x - y);
    c = x + 3 * h + x * x;
    d = h * z + x * x;

    cout << "Результат: ";
    cout << setprecision(4) << fixed << a - b * c / d << '\n';
}