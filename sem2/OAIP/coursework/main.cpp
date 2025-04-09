#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <cstdio>

using namespace std;

struct Student {
    char name[30];
    int group;
    float score;
    bool activist;
    int income;
};

// main functions
void createFile();
void addStudent();
void printAll();
void editStudent();
void deleteStudent();
void lineSearch();

// helper functions
void inputStudentInfo(Student* stud);
void printStudent(Student* stud);
void printTable();
int inputNewGroup();
float inputNewScore();
bool inputNewActivist();
int getStudentCount();
int strComp(char *first, char *second);
Student *getStudentArray(int studCount);
void writeStudentArray(Student *studs);
Student *findStudentName(Student *studs, char *name, int studCount);
void txtOutputStudent(Student &student);
void txtTable();
void txtSpace();

int main() {
    setlocale(LC_ALL, "ru");
    
    int what_to_do;
    bool end_program = false;
    
    do {
        cout << "Menu\n"
                "1 - Create new file\n"
                "2 - Add student\n"
                "3 - View all\n"
                "4 - Edit student\n"
                "5 - Delete student\n"
                "6 - Line search by name\n"
                "7 - Binary search by group\n"
                "8 - Quick sort by name\n"
                "9 - Selevtion sort by group\n"
                "10 - Insertion sort by av. score\n"
                "11 - Special sort\n"
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
            lineSearch();
            break;
        case 0:
            end_program = true;
            break;
        default:
            cout << "Unknown operation!\n";
            break;
        }
    } while (!end_program);
    
    return 0;
}

void createFile() {
    FILE* file = fopen("students.bin", "wb");
    fclose(file);
    cout << "File was created\n";
}

void addStudent() {
    FILE* file = fopen("students.bin", "ab");

    Student new_stud;
    cout << "Enter new student data\n";
    inputStudentInfo(&new_stud);
    
    fwrite(&new_stud, sizeof(Student), 1, file);
    fclose(file);
}

int inputNewGroup() {
    int group;
    cout << "Group number (6 digits): ";
    while (true) {
        cin >> group;
        if (100000 <= group && group <= 999999)
            return group;
        
        cout << "Error. Enter 6 digits\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

float inputNewScore() {
    float score;
    cout << "Enter average score (0 - 10): ";
    while (true) {
        cin >> score;
        if (0.0 <= score && score <= 10.0)
            return score;
        
        cout << "Error. Enter number from 0 to 10\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

bool inputNewActivist() {
    char activist;
    while (true) {
        cout << "Activist? (1 - yes, 0 - no): ";
        cin >> activist;
        if (activist == '1') return true;
        if (activist == '0') return false;
        
        cout << "Error. Enter 1 or 0\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void printStudent(Student* stud) {
    cout << setw(30) << left << stud->name 
         << setw(10) << left << stud->group
         << setw(10) << right << fixed << setprecision(2) << stud->score
         << setw(15) << right << (stud->activist ? "yes" : "no") 
         << setw(20) << right << stud->income << endl;
}

void printTable() {
    cout << setw(30) << left << " name"
         << setw(10) << left << "group"
         << setw(10) << right << "av. score"
         << setw(15) << right << "activist"
         << setw(20) << right << "income" << endl;
}

void inputStudentInfo(Student* stud) {
    cout << "name: ";
    cin.getline(stud->name, 30);
    
    stud->group = inputNewGroup();
    stud->score = inputNewScore();
    stud->activist = inputNewActivist();
    
    cout << "Income per family member: ";
    while (!(cin >> stud->income) || stud->income < 0) {
        cout << "Error, enter integer: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    cout << "\nStudent was added.\n";
    printTable();
    printStudent(stud);
}

void printAll(){
    FILE *file = fopen("students.bin", "rb");
    if(!file){
        cout << "File open error!\n";
        return;
    }

    Student stud;
    printTable();
    while(fread(&stud, sizeof(Student), 1, file))
        printStudent(&stud);
    
    cout << endl;
    fclose(file);
}

Student *getStudentArray(int studCount){
    FILE *file = fopen("students.bin", "rb");
    if(!file){
        cout << "File read error!\n";
        return nullptr;
    }

    Student *studs = new Student[studCount];
    for(int i = 0; i < studCount; i++)
        fread(&studs[i], sizeof(Student), 1, file);
    
    return studs;
}

void writeStudentArray(Student *studs, int studCount){
    FILE *file = fopen("students.bin", "wb");

    for(int i = 0; i < studCount; i++)
        fwrite(&studs[i], sizeof(Student), 1, file);

    fclose(file);
}

int strComp(char* first, char* second) {
    while (*first && *second && *first == *second) {
        first++;
        second++;
    }
    
    if (*first < *second) return -1;
    if (*first > *second) return 1;
    return 0;
}

void editStudent(){
    int studCount = getStudentCount();
    Student *studs = getStudentArray(studCount);
    char *editName = new char[30];
    bool success = false;
    cout << "Enter student name for edit: ";    cin.getline(editName, 30);

    Student *studentForEdit = findStudentName(studs, editName, studCount);

    if(studentForEdit != nullptr){
        success = true;
        cout << "Enter new info\n";
        inputStudentInfo(studentForEdit);    
    }

    delete[] studs;
    delete editName;
    if(success)
        cout << "Changes was saved.\n";
    else
        cout << "No such student.\n";
}

int getStudentCount(){
    FILE *file = fopen("students.bin", "rb");
    if(!file){
        cout << "File open error!\n";
        return 0;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    
    fclose(file);
    return file_size / sizeof(Student);
}

Student *findStudentName(Student *studs, char *name, int studCount){
    for(int i = 0; i < studCount; i++)
        if(strComp(studs[i].name, name) == 0)
            return &studs[i];
    return nullptr;
}

void deleteStudent(){
    int studCount = getStudentCount();
    Student *studs = getStudentArray(studCount);
    char *deleteName = new char[30];
    bool success = false;
    cout << "Enter student name for delete: ";    cin.getline(deleteName, 30);

    FILE *file = fopen("students.bin", "wb");

    for(int i = 0; i < studCount; i++){
        if(strComp(studs[i].name, deleteName) == 0){
            success = true;
            continue;
        }
        fwrite(&studs[i], sizeof(Student), 1, file);
    }

    fclose(file);
    delete[] studs;
    delete deleteName;
    if(success)
        cout << "Changes was saved.\n";
    else
        cout << "No such student.\n";
}

void lineSearch(){
    int studCount = getStudentCount();
    Student *studs = getStudentArray(studCount);
    char *findName = new char[30];
    bool success = false;
    cout << "Enter student name for find: ";    cin.getline(findName, 30);

    for(int i = 0; i < studCount; i++){
        if(strComp(studs[i].name, findName) == 0){
            success = true;
            printStudent(&studs[i]);
            txtTable();
            txtOutputStudent(studs[i]);
        }
    }

    delete[] studs;
    delete findName;
    if(!success) 
        cout << "No such student.\n";
    txtSpace();
}

void txtOutputStudent(Student &student){
    FILE *txt = fopen("log.txt", "at");
    fprintf(txt, "%-30s%-10d%10.2f%15s%20d\n", student.name, student.group, student.score, (student.activist) ? "yes" : "no", student.income);
    fclose(txt);
}

void txtTable() {
    FILE *txt = fopen("log.txt", "at");
    fprintf(txt, "%-30s%-10s%10s%15s%20s\n", "name", "group", "av. score", "activist", "income");
    fclose(txt);
}

void txtSpace() {
    FILE *txt = fopen("log.txt", "at");
    fprintf(txt, "\n");
    fclose(txt);
}

