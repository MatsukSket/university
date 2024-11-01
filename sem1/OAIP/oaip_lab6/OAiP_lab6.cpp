#include <iostream>

using namespace std;

int main(){
    char *str = new char[100];
    cout << "Введите строку: ";
    cin.getline(str, 100);
    for (int i = 0; str[i] != '\0'; i++){
        if (str[i] == 'a')
            str[i] = '*';
        else
            if('0' <= str[i] && str[i] <= '9')
                str[i] = '#';
    }

    cout << str << endl;

    delete[] str;
    return 0;
}