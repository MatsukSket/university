#include <iostream>

using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");

    int n;
    cout << "Введите порядок матрицы: ";    
    cin >> n;
    
    double **a = new double*[n];
    for (int i = 0; i < n; i++)
        a[i] = new double[n];
    
    int **b = new int*[n];
    for (int i = 0; i < n; i++)
        b[i] = new int[n];

    cout << "Введите исходную матрицу:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    
    cout << endl;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            b[i][j] = (a[i][j] > a[i][i]) ? 1 : 0;
            cout << b[i][j] << ' ';
        }
        cout << endl;
    }
    
    delete[] a;
    delete[] b;
}