#include <iostream>
#include <cmath>

using namespace std;

int main()  
{
    setlocale(LC_ALL, "ru");

    cout << "Введите число: ";
    int k;  cin >> k;
    int k1 = k, length = 0;
    int *a;
    switch (k)
    {
    case 0:
        a = new int[1];
        a[0] = 0;
        length++;
        break;
    default:
        while (k1) {
            k1 /= 10;
            length++;
        }

        a = new int[length];
        k1 = k;
        for (int i = 0; i < length; i++) {
            a[i] = pow(k1 % 10, 2);
            k1 /= 10;
        }
        break;
    }
    
    
    cout << '|';
    for (int i = length-1; i >= 0; i--)
        cout << a[i] << '|';

    cout << endl << endl;
    
    return 0;
}