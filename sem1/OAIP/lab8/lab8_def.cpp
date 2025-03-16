#include <iostream>
#include <cmath>

using namespace std;

double my_rec_func(int n, int k){
    if (k == n)
        return sqrt(n);
    else
        return sqrt(k + my_rec_func(n, k + 1));
}

double my_func(int n){
    double res = sqrt(n);
    for (int i = n - 1; i > 0; i--){
        res = sqrt(i + res);
    }
    return res;
}
int main(){
    int n;  
    cout << "Enter n: ";    cin >> n;
    cout << "Result of recursive func: " << my_rec_func(n, 1) << endl;
    cout << "Result of defoult func:   " << my_func(n) << endl;

    return 0;
}