#include "../include/header.h"

using namespace std;

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
    logTable(txt);
    logOutputStudent(txt, new_stud);
    fprintf(txt, "\n");
    fclose(txt);
}

int inputNewGroup(){
    int group;
    cout << "Group number (6 digits): ";
    while (true) {
        cin >> group;
        if (cin.fail() || group < 100000 || 999999 < group){
            cout << "Error. Enter 6 digits: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else
            return group;   
    }
}

float inputNewScore(){
    float score;
    cout << "Enter average score (0 - 10): ";
    while (true) {
        cin >> score;
        if (cin.fail() || score < 0.0 || score > 10.0){
            cout << "Error. Enter number from 0 to 10: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else
            return score;
    }
}

bool inputNewActivist(){
    int activist;
    cout << "Activist? (1 - yes, 0 - no): ";
    while (true) {
        cin >> activist;
        if (cin.fail() || (activist != 1 && activist != 0)){
            cout << "Error. Enter 1 or 0: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else 
            return activist == 1;
    }
}

int inputNewIncome(){
    int income;
    cout << "Income per family member: ";
    while (true) {
        cin >> income;
        if(cin.fail() || income < 0){
            cout << "Error, enter integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else
            return income;
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
    stud->income = inputNewIncome();
    
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
    logTable(txt);
    while(fread(&stud, sizeof(Student), 1, file)){
        printStudent(&stud);
        logOutputStudent(txt, stud);
    }
    cout << endl;
    fprintf(txt, "\n");

    fclose(file);
    fclose(txt);
}

Student *getStudentArray(int stud_count){
    FILE *file = fopen("students.bin", "rb");
    if(!file){
        cout << "File open error!\n\n";
        FILE *txt = fopen("log.txt", "at");
        fprintf(txt, "--FILE OPEN ERROR--\n\n");
        fclose(txt);
        return 0;
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

int nameComp(char *first, char *second) {
    if (!first || !second) 
        return (!first && !second) ? 0 : ((!first) ? -1 : 1);

    while (*first == ' ') first++;
    while (*second == ' ') second++;

    while (true) {
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

    Student *studentForEdit = findStudentByName(studs, editName, stud_count);

    FILE *txt = fopen("log.txt", "at");
    if (studentForEdit != nullptr) {
        cout << "Current student data:\n";
        printTable();
        printStudent(studentForEdit);
        
        fprintf(txt, "--EDIT STUDENT--\nEdited student:\n");
        logTable(txt);
        logOutputStudent(txt, *studentForEdit);

        cout << "\nEnter new info:\n";
        inputStudentInfo(studentForEdit);
        
        logOutputStudent(txt, *studentForEdit);
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

Student *findStudentByName(Student *studs, char *name, int stud_count){
    for(int i = 0; i < stud_count; i++)
        if(nameComp(studs[i].name, name) == 0)
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
        if(nameComp(studs[i].name, deleteName) == 0){
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
        if(nameComp(studs[i].name, findName) == 0){
            if(!success){
                txt = fopen("log.txt", "at");
                fprintf(txt, "--LINEAR SEARCH BY NAME--\n");
                logTable(txt);
                printTable();
            } 
            printStudent(&studs[i]);
            logOutputStudent(txt, studs[i]);
            success = true;
        }
    }
    delete[] studs;
    
    if(!success) {
        cout << "No such student\n";
        txt = fopen("log.txt", "at");
        fprintf(txt, "--LINEAR SEARCH BY NAME--\nStudent %s not found\n\n", findName);
    }
    else
        fprintf(txt, "\n");
    cout << endl;
    fclose(txt);
}

void logOutputStudent(FILE *txt, Student &student){
    fprintf(txt, "%-40s%-10d%10.2f%15s%20d\n", student.name, student.group, student.score, (student.activist) ? "yes" : "no", student.income);
}

void logTable(FILE *txt){
    fprintf(txt, "%-40s%-10s%10s%15s%20s\n", " name", "group", "av. score", "activist", "income");
}

void logOutputArray(FILE *txt, Student *studs, int stud_count){
    for(int i = 0; i < stud_count; i++)
        logOutputStudent(txt, studs[i]);
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

    selectionSortByGroup(studs, stud_count);

    FILE *txt = fopen("log.txt", "at");
    fprintf(txt, "--SELECTION SORT BY GROUP--\n");
    logTable(txt);
    logOutputArray(txt, studs, stud_count);
    fprintf(txt, "\n");
    fclose(txt);
    
    printTable();
    printStudentArray(studs, stud_count);
    cout << endl;

    delete[] studs;
}

void selectionSortByGroup(Student *studs, int stud_count){
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
    selectionSortByGroup(studs, stud_count);

    int find_group = inputNewGroup();
    cin.ignore();

    int group_index = binarySearchByGroup(studs, stud_count, find_group);

    if(group_index != -1){
        FILE *txt = fopen("log.txt", "at");
        printTable();
        fprintf(txt, "--BINARY SEARCH BY GROUP--\n");
        logTable(txt);
        for(int i = group_index; studs[i].group == find_group; i++){
            logOutputStudent(txt, studs[i]);
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

int binarySearchByGroup(Student *studs, int stud_count, int find_group){
    int start = 0;
    int len = stud_count;
    while(len > 0) {
        int half = len / 2;
        if (studs[start + half].group < find_group) {
            start += half + 1;
            len -= half + 1;
        }
        else
            len = half;
    }
    if (start < stud_count && studs[start].group == find_group)
        return start;
    else
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
    logTable(txt);
    logOutputArray(txt, studs, stud_count);
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
    quicksortByName(studs, 0, stud_count-1);

    FILE *txt = fopen("log.txt", "at");
    fprintf(txt, "--QUICK SORT BY NAME--\n");
    logTable(txt);
    logOutputArray(txt, studs, stud_count);
    fprintf(txt, "\n");
    fclose(txt);

    printTable();
    printStudentArray(studs, stud_count);
    cout << endl;

    delete[] studs;
}

void quicksortByName(Student *studs, int l, int r){
    Student pivot = studs[(l+r) / 2], temp_stud;
    int lt = l, rt = r; // left temp & right temp
    do {
        while(nameComp(studs[lt].name, pivot.name) < 0)    lt++;
        while(nameComp(studs[rt].name, pivot.name) > 0)    rt--;
        if(lt <= rt){
            temp_stud = studs[lt];
            studs[lt] = studs[rt];
            studs[rt] = temp_stud;
            lt++;
            rt--;
        }
    } while(lt <= rt);

    if (l < rt) 
        quicksortByName(studs, l, rt);
    if (lt < r) 
        quicksortByName(studs, lt, r);
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
    selectionSortByGroup(studs, stud_count);

    int find_group = inputNewGroup();   cin.ignore();
    float find_score = inputNewScore();
    int group_index = binarySearchByGroup(studs, stud_count, find_group);
    bool success = false;

    if(group_index != -1){
        int groupmates_count = 0;
        for(int i = group_index; studs[i].group == find_group; i++)
            groupmates_count++;
        quicksortByName(studs, group_index, group_index + groupmates_count - 1);
        
        FILE *txt = fopen("log.txt", "at");
        printTable();
        fprintf(txt, "--SPECIAL SEARCH--\n");
        logTable(txt);
        for(int i = group_index; studs[i].group == find_group; i++){
            if(studs[i].score > find_score && studs[i].activist){
                success = true;
                logOutputStudent(txt, studs[i]);
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
    logTable(txt);
    
    int privileged_count = 0;
    for (int i = 0; i < stud_count; i++) {
        if (studs[i].income < 2 * min_salary) {
            privileged_count++;
        }
        printStudent(&studs[i]);
        logOutputStudent(txt, studs[i]);
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

void printAdd(Student* stud) {
    cout << "   ";
    cout << setw(40) << left << stud->name 
        << setw(10) << right << fixed << setprecision(2) << stud->score
        << setw(15) << right << (stud->activist ? "yes" : "no") 
        << setw(20) << right << stud->income << endl;
}

void sortAddTask(Student *studs, int count){
    for (int i = 1; i < count; i++) {
        Student key = studs[i];
        int j;
        for (j = i - 1; j >= 0 && myComp(studs[j], key) > 0; j--)
            studs[j + 1] = studs[j];
        studs[j + 1] = key;
    }
}

void addictionalTask() {
    int stud_count = getStudentCount();
    Student* studs = getStudentArray(stud_count);

    bool newGroup = false;
    sortAddTask(studs, stud_count);

    cout << studs[0].group << endl;
    printAdd(&studs[0]);
    for(int i = 1; i < stud_count; i++){
        if(studs[i].group != studs[i-1].group)
            newGroup = true;
        if(newGroup){
            cout << studs[0].group << endl;
            newGroup = false;
        }
        if(studs[i].activist)
            printAdd(&studs[i]);
    }
    
    delete[] studs;
}

int myComp(Student &a, Student &b) {
    if (a.group != b.group) 
        return a.group - b.group;

    return nameComp(a.name, b.name);
}