#include <iostream>

using namespace std;

float 
float rpn(char* str, int i){
    if(str[i])
}

int main()
{
    char* str = new char[10];
    cin.getline(str, 10);
    int i = 0;
    while(str[i])
        i++;
    cout << i << '\n';
    cout << str << '\n';
    float ans = rpn(str, i-1);
    // abc-de+/.
    return 0;
}