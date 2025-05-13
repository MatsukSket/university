#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <cstdio>

using namespace std;

struct Student {
    char name[40];
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
void searchName();
void searchGroup();
void sortName();
void sortGroup();
void sortAvScore();
void specialSearch();
void getStats();

// input/output
void inputStudentInfo(Student *stud);
void printStudent(Student *stud);
void printTable();
int inputNewGroup();
float inputNewScore();
bool inputNewActivist();
void writeStudentArray(Student *studs, int stud_count);
Student *getStudentArray(int stud_count);
void txtOutputStudent(FILE *txt, Student &student);
void txtTable(FILE *txt);
void txtOutputArray(FILE *txt, Student *studs, int stud_count);

// helper functions
int getStudentCount();
int strComp(char *first, char *second);
int nameComp(char *first, char *second);
Student *findStudentName(Student *studs, char *name, int stud_count);
void selectionSortGroup(Student *studs, int stud_count);
void quicksort(Student *studs, int low, int high);
int partition(Student *studs, int low, int high);
int binarySearch(Student *studs, int stud_count, int find_group);
void insertionSortByPriority(Student* studs, int count, int min_salary);
bool comparePriority(const Student& a, const Student& b, int min_salary);

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

void createFile(){
    FILE* file = fopen("students.bin", "wb");
    fclose(file);
    cout << "File was created\n\n";
    FILE *txt = fopen("log.txt", "at");
    fprintf(txt, "--CREATE FILE--\nNew file was created\n\n");
    fclose(txt);
}

void addStudent(){
    FILE* file = fopen("students.bin", "ab");
    if(!file){
        cout << "File open error!\n\n";
        FILE *txt = fopen("log.txt", "at");
        fprintf(txt, "--FILE OPEN ERROR--\n\n");
        fclose(txt);
        return;
    }

    Student new_stud;
    cout << "Enter new student data\n";
    inputStudentInfo(&new_stud);
    fwrite(&new_stud, sizeof(Student), 1, file);
    fclose(file);
    
    cout << "Student was added\n\n";
    FILE *txt = fopen("log.txt", "at");
    fprintf(txt, "--ADD STUDENT--\n");
    txtTable(txt);
    txtOutputStudent(txt, new_stud);
    fprintf(txt, "\n");
    fclose(txt);
}

int inputNewGroup(){
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

float inputNewScore(){
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

bool inputNewActivist(){
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
    cout << setw(40) << left << stud->name 
        << setw(10) << left << stud->group
        << setw(10) << right << fixed << setprecision(2) << stud->score
        << setw(15) << right << (stud->activist ? "yes" : "no") 
        << setw(20) << right << stud->income << endl;
}

void printStudentArray(Student *studs, int stud_count){
    for(int i = 0; i < stud_count; i++)
        printStudent(&studs[i]);
}

void printTable(){
    cout << setw(40) << left << " name"
        << setw(10) << left << "group"
        << setw(10) << right << "av. score"
        << setw(15) << right << "activist"
        << setw(20) << right << "income" << endl;
}

void inputStudentInfo(Student* stud) {
    cout << "Name: ";
    cin.getline(stud->name, 40);
    
    stud->group = inputNewGroup();
    stud->score = inputNewScore();
    stud->activist = inputNewActivist();
    
    cout << "Income per family member: ";
    while (!(cin >> stud->income) || stud->income < 0) {
        cout << "Error, enter integer: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    printTable();
    printStudent(stud);
}

void printAll(){
    FILE *file = fopen("students.bin", "rb");
    if(!file){
        cout << "File open error!\n\n";
        FILE *txt = fopen("log.txt", "at");
        fprintf(txt, "--FILE OPEN ERROR--\n\n");
        fclose(txt);
        return;
    }

    if(getStudentCount() == 0){
        cout << "Database is empty\n";
        FILE *txt = fopen("log.txt", "at");
        fprintf(txt, "--PRINT ALL--\nDatabase is empty\n\n");
        fclose(txt);
        return;
    }

    Student stud;
    FILE *txt = fopen("log.txt", "at");
    printTable();
    fprintf(txt, "--PRINT ALL--\n");
    txtTable(txt);
    while(fread(&stud, sizeof(Student), 1, file)){
        printStudent(&stud);
        txtOutputStudent(txt, stud);
    }
    cout << endl;
    fprintf(txt, "\n");

    fclose(file);
    fclose(txt);
}

Student *getStudentArray(int stud_count){
    FILE *file = fopen("students.bin", "rb");
    if(!file){
        cout << "File read error!\n";
        return nullptr;
    }

    Student *studs = new Student[stud_count];
    for(int i = 0; i < stud_count; i++)
        fread(&studs[i], sizeof(Student), 1, file);
    
    return studs;
}

void writeStudentArray(Student *studs, int stud_count){
    FILE *file = fopen("students.bin", "wb");

    for(int i = 0; i < stud_count; i++)
        fwrite(&studs[i], sizeof(Student), 1, file);

    fclose(file);
}

int strComp(char *first, char *second) {
    if (!first || !second) 
        return (!first && !second) ? 0 : ((!first) ? -1 : 1);

    bool wordStartFirst = true;
    bool wordStartSecond = true;

    while (true) {
        if (*first == ' ' && wordStartFirst) {
            ++first;
            continue;
        }
        if (*second == ' ' && wordStartSecond) {
            ++second;
            continue;
        }

        wordStartFirst = (*first == ' ');
        wordStartSecond = (*second == ' ');

        if (*first == '\0' || *second == '\0') 
            return (*first == '\0' && *second == '\0') ? 0 : ((*first == '\0') ? -1 : 1);
        

        if (*first != *second) {
            return (*first > *second) ? 1 : -1;
        }

        first++;
        second++;
    }
}

void editStudent(){
    int stud_count = getStudentCount();
    if (stud_count == 0) {
        cout << "Database is empty\n";
        FILE *txt = fopen("log.txt", "at");
        fprintf(txt, "--EDIT STUDENT--\nDatabase is empty\n\n");
        fclose(txt);
        return;
    }

    Student *studs = getStudentArray(stud_count);

    char editName[40];
    cout << "Enter student name for edit: ";
    cin.getline(editName, 40);

    Student *studentForEdit = findStudentName(studs, editName, stud_count);

    FILE *txt = fopen("log.txt", "at");
    if (studentForEdit != nullptr) {
        cout << "Current student data:\n";
        printTable();
        printStudent(studentForEdit);
        
        fprintf(txt, "--EDIT STUDENT--\nEdited student:\n");
        txtTable(txt);
        txtOutputStudent(txt, *studentForEdit);

        cout << "\nEnter new info:\n";
        inputStudentInfo(studentForEdit);
        
        txtOutputStudent(txt, *studentForEdit);
        fprintf(txt, "\n");

        writeStudentArray(studs, stud_count);
        cout << "Changes were saved\n\n";
    } else {
        cout << "No such student\n\n";
        fprintf(txt, "--EDIT STUDENT--\nStudent %s not found\n\n", editName);
    }
    fclose(txt);

    delete[] studs;
}

int getStudentCount(){
    FILE *file = fopen("students.bin", "rb");
    if(!file){
        cout << "File open error!\n\n";
        FILE *txt = fopen("log.txt", "at");
        fprintf(txt, "--FILE OPEN ERROR--\n\n");
        fclose(txt);
        return 0;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    
    fclose(file);
    return file_size / sizeof(Student);
}

Student *findStudentName(Student *studs, char *name, int stud_count){
    for(int i = 0; i < stud_count; i++)
        if(strComp(studs[i].name, name) == 0)
            return &studs[i];
    return nullptr;
}

void deleteStudent(){
    int stud_count = getStudentCount();
    if (stud_count == 0) {
        cout << "Database is empty\n";
        FILE *txt = fopen("log.txt", "at");
        fprintf(txt, "--DELETE STUDENT--\nDatabase is empty\n\n");
        fclose(txt);
        return;
    }

    Student *studs = getStudentArray(stud_count);
    char deleteName[40];
    bool success = false;
    cout << "Enter student name for delete: ";    cin.getline(deleteName, 40);

    FILE *file = fopen("students.bin", "wb");

    for(int i = 0; i < stud_count; i++){
        if(strComp(studs[i].name, deleteName) == 0){
            success = true;
            continue;
        }
        fwrite(&studs[i], sizeof(Student), 1, file);
    }

    fclose(file);
    delete[] studs;
    if(success){
        FILE *txt = fopen("log.txt", "at");
        fprintf(txt, "--DELETE STUDENT--\nStudent was deleted\n\n");
        fclose(txt);
        cout << "Changes was saved\n\n";
    }
    else{
        cout << "No such student\n\n";
        FILE *txt = fopen("log.txt", "at");
        fprintf(txt, "--DELETE STUDENT--\nStudent %s not found\n\n", deleteName);
        fclose(txt);
    }
}

void searchName(){
    int stud_count = getStudentCount();
    if (stud_count == 0) {
        cout << "Database is empty\n";
        FILE *txt = fopen("log.txt", "at");
        fprintf(txt, "--LINEAR SEARCH BY NAME--\nDatabase is empty\n\n");
        fclose(txt);
        return;
    }

    Student *studs = getStudentArray(stud_count);
    char findName[40];
    bool success = false;
    cout << "Enter student name for find: ";    cin.getline(findName, 40);
    
    FILE *txt;
    for(int i = 0; i < stud_count; i++){
        if(strComp(studs[i].name, findName) == 0){
            if(!success){
                txt = fopen("log.txt", "at");
                fprintf(txt, "--LINEAR SEARCH BY NAME--\n");
                txtTable(txt);
                printTable();
            } 
            printStudent(&studs[i]);
            txtOutputStudent(txt, studs[i]);
            success = true;
        }
    }
    delete[] studs;
    
    if(!success) {
        cout << "No such student\n";
        txt = fopen("log.txt", "at");
        fprintf(txt, "--LINEAR SEARCH BY NAME--\nStudent %s not found\n\n", findName);
    }
    cout << endl;
    fclose(txt);
}

void txtOutputStudent(FILE *txt, Student &student){
    fprintf(txt, "%-40s%-10d%10.2f%15s%20d\n", student.name, student.group, student.score, (student.activist) ? "yes" : "no", student.income);
}

void txtTable(FILE *txt){
    fprintf(txt, "%-40s%-10s%10s%15s%20s\n", " name", "group", "av. score", "activist", "income");
}

void txtOutputArray(FILE *txt, Student *studs, int stud_count){
    for(int i = 0; i < stud_count; i++)
        txtOutputStudent(txt, studs[i]);
}

void sortGroup(){
    int stud_count = getStudentCount();
    if (stud_count == 0) {
        cout << "Database is empty\n";
        FILE *txt = fopen("log.txt", "at");
        fprintf(txt, "--SELECTION SORT BY GROUP--\nDatabase is empty\n\n");
        fclose(txt);
        return;
    }
    Student *studs = getStudentArray(stud_count);

    selectionSortGroup(studs, stud_count);

    FILE *txt = fopen("log.txt", "at");
    fprintf(txt, "--SELECTION SORT BY GROUP--\n");
    txtTable(txt);
    txtOutputArray(txt, studs, stud_count);
    fprintf(txt, "\n");
    fclose(txt);
    
    printTable();
    printStudentArray(studs, stud_count);
    cout << endl;

    delete[] studs;
}

void selectionSortGroup(Student *studs, int stud_count){
    for(int i = 0; i < stud_count - 1; i++){
        int minIndex = i;

        for(int j = i+1; j < stud_count; j++) 
            if(studs[j].group < studs[minIndex].group)
                minIndex = j;
        
        if(minIndex != i) {
            Student temp = studs[i];
            studs[i] = studs[minIndex];
            studs[minIndex] = temp;
        }
    }
}

void searchGroup(){
    int stud_count = getStudentCount();
    if (stud_count == 0) {
        cout << "Database is empty\n";
        FILE *txt = fopen("log.txt", "at");
        fprintf(txt, "--BINARY SEARCH BY GROUP--\nDatabase is empty\n\n");
        fclose(txt);
        return;
    }

    Student *studs = getStudentArray(stud_count);
    selectionSortGroup(studs, stud_count);

    int find_group = inputNewGroup();
    cin.ignore();

    int group_index = binarySearch(studs, stud_count, find_group);

    if(group_index != -1){
        FILE *txt = fopen("log.txt", "at");
        printTable();
        fprintf(txt, "--BINARY SEARCH BY GROUP--\n");
        txtTable(txt);
        for(int i = group_index; studs[i].group == find_group; i++){
            txtOutputStudent(txt, studs[i]);
            printStudent(&studs[i]);
        }
        fprintf(txt, "\n");
        fclose(txt);
    }
    else{
        FILE *txt = fopen("log.txt", "at");
        fprintf(txt, "--BINARY SEARCH BY GROUP--\nGroup %d students not found\n\n", find_group);
        fclose(txt);
        cout << "No such student\n";
    }

    cout << endl;
    delete[] studs;
}

int binarySearch(Student *studs, int stud_count, int find_group){
    int left = 0;
    int right = stud_count - 1;

    while(left <= right) {
        int mid = left + (right - left) / 2;

        if(studs[mid].group == find_group){
            int start = mid;
            while (start > 0 && studs[start - 1].group == find_group)
                start--;
            return start;
        }
        else if (studs[mid].group < find_group)
            left = mid + 1;
        else 
            right = mid - 1;
    }

    return -1;
}

void sortAvScore(){
    int stud_count = getStudentCount();
    if (stud_count == 0) {
        cout << "Database is empty\n";
        FILE *txt = fopen("log.txt", "at");
        fprintf(txt, "--INSERTION SORT BY AV. SCORE--\nDatabase is empty\n\n");
        fclose(txt);
        return;
    }

    Student *studs = getStudentArray(stud_count);
    for(int i = 1; i < stud_count; i++){
        Student key = studs[i];
        int j;
        for(j = i - 1; j >=0 && studs[j].score < key.score; j--) 
            studs[j+1] = studs[j];
        studs[j+1] = key;
    }

    FILE *txt = fopen("log.txt", "at");
    fprintf(txt, "--INSERTION SORT BY AV. SCORE--\n");
    txtTable(txt);
    txtOutputArray(txt, studs, stud_count);
    fprintf(txt, "\n");
    fclose(txt);

    printTable();
    printStudentArray(studs, stud_count);
    cout << endl;
    
    delete[] studs;
}

void sortName(){
    int stud_count = getStudentCount();
    if (stud_count == 0) {
        cout << "Database is empty\n";
        FILE *txt = fopen("log.txt", "at");
        fprintf(txt, "--QUICK SORT BY NAME--\nDatabase is empty\n\n");
        fclose(txt);
        return;
    }

    Student *studs = getStudentArray(stud_count);
    quicksort(studs, 0, stud_count-1);

    FILE *txt = fopen("log.txt", "at");
    fprintf(txt, "--QUICK SORT BY NAME--\n");
    txtTable(txt);
    txtOutputArray(txt, studs, stud_count);
    fprintf(txt, "\n");
    fclose(txt);

    printTable();
    printStudentArray(studs, stud_count);
    cout << endl;

    delete[] studs;
}

void quicksort(Student *studs, int low, int high){
    if(low < high){
        int pivotIndex = partition(studs, low, high);
        quicksort(studs, low, pivotIndex - 1);
        quicksort(studs, pivotIndex + 1, high);
    }
}

int partition(Student *studs, int low, int high){
    Student pivot = studs[high];
    int i = low - 1;

    for(int j = low; j < high; j++){
        if(strComp(studs[j].name, pivot.name) <= 0){
            i++;
            Student temp = studs[i];
            studs[i] = studs[j];
            studs[j] = temp;
        }
    }

    Student temp = studs[i + 1];
    studs[i + 1] = studs[high];
    studs[high] = temp;
    return i + 1;
}

void specialSearch(){
    int stud_count = getStudentCount();
    if (stud_count == 0) {
        cout << "Database is empty\n";
        FILE *txt = fopen("log.txt", "at");
        fprintf(txt, "--SPECIAL SEARCH--\nDatabase is empty\n\n");
        fclose(txt);
        return;
    }

    Student *studs = getStudentArray(stud_count);
    selectionSortGroup(studs, stud_count);

    int find_group = inputNewGroup();   cin.ignore();
    float find_score = inputNewScore();
    int group_index = binarySearch(studs, stud_count, find_group);
    bool success = false;

    if(group_index != -1){
        int groupmates_count = 0;
        for(int i = group_index; studs[i].group == find_group; i++)
            groupmates_count++;
        quicksort(studs, group_index, group_index + groupmates_count - 1);
        
        FILE *txt = fopen("log.txt", "at");
        printTable();
        fprintf(txt, "--SPECIAL SEARCH--\n");
        txtTable(txt);
        for(int i = group_index; studs[i].group == find_group; i++){
            if(studs[i].score > find_score && studs[i].activist){
                success = true;
                txtOutputStudent(txt, studs[i]);
                printStudent(&studs[i]);
            }
        }
        fprintf(txt, "\n");
        fclose(txt);
    }

    if(!success){
        FILE *txt = fopen("log.txt", "at");
        fprintf(txt, "--SPECIAL SEARCH--\nNo %d group student with %.2f av. score\n\n", find_group, find_score);
        fclose(txt);
        cout << "No such student\n";
    }
    cout << endl;

    delete[] studs;
}

void getStats() {
    int stud_count = getStudentCount();
    if (stud_count == 0) {
        cout << "Database is empty\n";
        FILE *txt = fopen("log.txt", "at");
        fprintf(txt, "--QUEUE TO DORM--\nDatabase is empty\n\n");
        fclose(txt);
        return;
    }

    int min_salary;
    cout << "Enter minimal salary: ";
    while (!(cin >> min_salary) || min_salary <= 0) {
        cout << "Error! Enter positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    Student* studs = getStudentArray(stud_count);
    insertionSortByPriority(studs, stud_count, min_salary);

    cout << "Priority list for dormitory:\n";
    FILE *txt = fopen("log.txt", "at");
    printTable();
    fprintf(txt, "--QUEUE TO DORM--\n");
    txtTable(txt);
    
    int privileged_count = 0;
    for (int i = 0; i < stud_count; i++) {
        if (studs[i].income < 2 * min_salary) {
            privileged_count++;
        }
        printStudent(&studs[i]);
        txtOutputStudent(txt, studs[i]);
    }
    
    cout << "Number of privileged students: " << privileged_count << endl << endl;
    fprintf(txt, "Privileged students: %d\n\n", privileged_count);
    fclose(txt);
    delete[] studs;
}

void insertionSortByPriority(Student* studs, int count, int min_salary) {
    for (int i = 1; i < count; i++) {
        Student key = studs[i];
        int j;
        for (j = i - 1; j >= 0 && comparePriority(studs[j], key, min_salary); j--)
            studs[j + 1] = studs[j];
        studs[j + 1] = key;
    }
}

bool comparePriority(const Student& a, const Student& b, int min_salary) {
    bool a_pr = (a.income < 2 * min_salary);
    bool b_pr = (b.income < 2 * min_salary);

    if (a_pr != b_pr) 
        return !a_pr;
        
    if (a.score != b.score) 
        return a.score < b.score;
        
    return !a.activist && b.activist;
}