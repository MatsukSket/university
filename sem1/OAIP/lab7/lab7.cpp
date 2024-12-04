#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    FILE* f = fopen("input.txt", "r");
    char* str = new char[99];
    fscanf(f, "%s %d %d %d %d %lf", str);
    fclose(f);

    FILE* ans = fopen("output.txt", "w");
    
    fclose(ans);

    delete[] str;
    return 0;
}