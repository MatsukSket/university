#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

float recursiveRoot(float val, int num)
{
    float newVal;
    newVal = (val + num / val) / 2;
    return (val == newVal) ? newVal : recursiveRoot(newVal, num);
}

float defaultRoot(float val, int num)
{
    float newVal;
    while(true){
        newVal = (val + num / val) / 2;
        if (newVal != val)
            val = newVal;
        else
            return newVal;
    }
}

int main()
{
    int a;
    cout << "Enter the number: ";   cin >> a;
    float x;
    x = (a + 1) / 2;
    cout << left << setw(13) << "recursive: " << recursiveRoot(x, a) << endl;
    cout << left << setw(13) << "default: " << defaultRoot(x, a) << endl;
    cout << left << setw(13) << "cmath func: " << sqrt(a) << endl;
    return 0;
}