#include <iostream>
#include <stdio.h>

using namespace std;

char encd(char c) {
    if ('a' <= c && c <= 'z')
        return ((c == 'a') ? ('z') : (c - 1));
    if ('A' <= c && c <= 'Z')
        return ((c == 'A') ? ('Z') : (c - 1));
    return c; 
}

int main()
{
    FILE* f = fopen("input.txt", "r");
    char* str = new char[99];
    fscanf(f, "%[^\n]", str);
    fclose(f);

    FILE* ans = fopen("output.txt", "w");
    for (int i = 0; str[i] != '\0'; i++) {
        fprintf(ans, "%c", encd(str[i]));
    }
    fclose(ans);

    delete[] str;
    return 0;
}