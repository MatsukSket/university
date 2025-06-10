#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

struct student {
    string name;
    int group;
    int year;
};

int getHash1(int key, int M) {
    return key % M;
}

int getHash2(int key, int i, int M) {
    int c = 1 + (key % (M - 2));
    i = i - c;
    return (i < 0) ? i + M : i;
}   

void addStud(student stud, student* Hash, int size = 20) {
    int key = stud.year;
    int i = getHash1(key, size);

    if(Hash[i].year == -1) {
        Hash[i] = stud;
        return;
    }

    int c = 1 + (key % (size - 2));
    while(true) {
        i = getHash2(key, i, size);
        if(Hash[i].year == -1) {
            Hash[i] = stud;
            return;
        }
    }
}

int studFind(student stud, student* Hash, int size = 20) {
    int key = stud.year;
    int i = getHash1(key, size);
    int original_i = i;
    int c = 1 + (key % (size - 2));

    if (Hash[i].name == stud.name && 
        Hash[i].group == stud.group && 
        Hash[i].year == stud.year) 
        return i;

    while(true) {
        i = getHash2(key, i, size);
        
        if (i == original_i)
            return -1;
            
        if (Hash[i].name == stud.name && 
            Hash[i].group == stud.group && 
            Hash[i].year == stud.year) 
            return i;
        if (Hash[i].year == -1)
            return -1;
    }
}

int main() 
{
    const int STUD_NUM = 11;
    const int HASH_SIZE = 20;
    
    student studs[STUD_NUM];
    student Hash[HASH_SIZE];

    for (int i = 0; i < HASH_SIZE; i++) {
        Hash[i].name = "";
        Hash[i].group = -1;
        Hash[i].year = -1;
    }

    for (int i = 0; i < STUD_NUM; i++) {
        cout << "Enter name: ";     getline(cin, studs[i].name);
        cout << "Enter group: ";    cin >> studs[i].group;
        cout << "Enter year: ";     cin >> studs[i].year;
        cin.ignore();

        addStud(studs[i], Hash);
    }

    cout << "\n-------HASH TABLE--------\n";
    for(int i = 0; i < HASH_SIZE; i++) {
        if(Hash[i].year == -1)
            cout << i << ": Empty\n";
        else
            cout << i << ": " 
                 << setw(10) << left << Hash[i].name 
                 << Hash[i].group << "\t" 
                 << Hash[i].year << "\n";
    }

    student st;
    while(true) {
        cout << "\nEnter student to search:\n";
        cout << "Enter name: ";     getline(cin, st.name);
        cout << "Enter group: ";    cin >> st.group;
        cout << "Enter year: ";     cin >> st.year;
        cin.ignore();

        int index = studFind(st, Hash);
        if(index == -1)
            cout << "\nStudent not found.\n";
        else
            cout << "\nFound student index: " << index << "\n"
                 << Hash[index].name << "\t" 
                 << Hash[index].group << "\t" 
                 << Hash[index].year << "\n";
    }

    return 0;
}