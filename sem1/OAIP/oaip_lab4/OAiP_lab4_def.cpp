#include <iostream>
#include <cmath>

using namespace std;

int main()  
{
    setlocale(LC_ALL, "ru");

    cout << "Введите число элементов: ";
    int k;  cin >> k;
    
    cout << "Введите массив: ";
    int *a = new int[k];
    int *b = new int[k];
    for (int i = 0; i < k; i++)
        cin >> a[i];
    
    int len = 0;
    double sum = 0;
    for (int i = 0; i < k; i++){
        if (a[i] % 2 == 1) {
            b[len] = a[i];
            sum += a[i];
            len++;
        }
    }

    cout << "Массив без четных элементов: ";
    for (int i = 0; i < len; i++) {
        cout << b[i] << ' ';
    }
    cout << endl << "Среднее арифметическое его занчений: " << sum / len << endl;

    delete[] a;
    delete[] b;
    return 0;
}