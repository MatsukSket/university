#include "../include/header.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    FILE *txt = fopen("log.txt", "at");
    fprintf(txt, "--START THE PROGRAM--\n\n");
    fclose(txt);
    int what_to_do;
    bool end_program = false;
    
    do {
        cout << "Menu\n"
                "1 - Create new file\n"
                "2 - Add student\n"
                "3 - Print all\n"
                "4 - Edit student\n"
                "5 - Delete student\n"
                "6 - Line search by name\n"
                "7 - Binary search by group\n"
                "8 - Quick sort by name\n"
                "9 - Selevtion sort by group\n"
                "10 - Insertion sort by av. score\n"
                "11 - Special search\n"
                "12 - Complete task\n"
                "0 - Exit\n";

        cout << "Enter the number: ";
        cin >> what_to_do;
        cin.ignore();
        
        switch (what_to_do) {
        case 1:
            createFile();
            break;
        case 2:
            addStudent();
            break;
        case 3:
            printAll();
            break;
        case 4:
            editStudent();
            break;
        case 5:
            deleteStudent();
            break;
        case 6:
            searchName();
            break;
        case 7:
            searchGroup();
            break;
        case 8:
            sortName();
            break;
        case 9:
            sortGroup();
            break;
        case 10:
            sortAvScore();
            break;
        case 11:
            specialSearch();
            break;
        case 12:
            getStats();
            break;
        case 0:
            end_program = true;
            txt = fopen("log.txt", "at");
            fprintf(txt, "--CLOSE THE PROGRAM--\n\n");
            fclose(txt);
            break;
        default:
            cout << "Unknown operation!\n";
            break;
        }
    } while (!end_program);
    
    return 0;
}
