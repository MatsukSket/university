#include <iostream>

using namespace std;

char encd(char c){
    if ('a' <= c && c <= 'z')
        return (c == 'a') ? 'z' : c + 1;
    if ('A' <= c && c <= 'Z')
        return (c == 'A') ? 'Z' : c + 1;
}

int main()
{
    FILE *myFile;
    if (!(myFile = fopen("test.txt", "rt"))){
        puts("\nОшибка открытия файла");
        return 0;
    }
    FILE *ans = fopen("ans.txt", "wt");
    if (ans == nullptr) {
        puts("ошибка открытия файла");
        return 0;
    }

    char *str = new char[99];
    fscanf(myFile, "%s", str);

    
    
    
    fclose(myFile);
    fclose(ans);
}