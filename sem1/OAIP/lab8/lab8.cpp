#include <iostream>

using namespace std;

double my_rec_func(int n){
    if (n == 1)
        return 2/3.;
    else
        return 1 / (n + my_rec_func(n-1));
}

double my_func(int n){
    double res;
    for (int i = 1; i <= n; i++){
        if (i == 1) 
            res = 2/3.;
        else
            res = 1 / (i + res);
    }
    return res;
}
int main(){
    int n;  
    cout << "Enter n: ";    cin >> n;
    cout << "Result of recursive func: " << my_rec_func(n) << endl;
    cout << "Result of defoult func:   " << my_func(n) << endl;

    return 0;
}