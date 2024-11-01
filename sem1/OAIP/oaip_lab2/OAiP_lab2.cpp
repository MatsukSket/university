#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

double x, y, a;

// придумать пример, чтобы был и иф и свич

double Max(double a, double b) {
    return (a > b) ? a : b;
    /*if (a > b)  return a;
    else        return b;*/
}

double Min(double a, double b) {
    if (a < b)  return a;
    else        return b;
}

int main()
{
    setlocale(LC_ALL, "Ru");
    
    cout << "Введите х: ";  cin >> x;
    cout << "Введите y: ";  cin >> y;
    cout << "Введите a: ";  cin >> a;

    cout << "Ответ: ";
    if (a < 0)  
        cout << Min(x * x, y * y) + a;
    else 
        if (a == 0) 
            cout << Max(Max(x, y), a); 
        else 
           cout << fabs(x - y) + y * (x + pow(a, 1 / 3.));
}

