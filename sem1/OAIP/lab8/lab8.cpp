#include <iostream>

using namespace std;

double my_func(int n){
    if (n == 1)
        return 2/3.;
    else
        return 1 / (n + my_func(n-1));
}

int main(){
    int n;  
    cout << "Enter n: ";    cin >> n;
    cout << my_func(n) << endl;
}