#ifndef DORM_H
#define DORM_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <cstdio>   


struct Student {
    char name[40];
    int group;
    float score;
    bool activist;
    int income;
};


// ----- MAIN FUNCTIONS ---- //
void createFile();
void addStudent();
void printAll();
void editStudent();
void deleteStudent();
void searchName();      // linear
void searchGroup();     // binary
void sortName();        // quicksort
void sortGroup();       // selection
void sortAvScore();     // insertion
void specialSearch();   
void getStats();        


// ------------------ INPUT/OUTPUT ------------------- //
// console
int inputNewGroup();
float inputNewScore();
bool inputNewActivist();
int inputNewIncome();
void inputStudentInfo(Student *stud);
void printTable();
void printStudent(Student *stud);
// bin file
Student *getStudentArray(int stud_count);
void writeStudentArray(Student *studs, int stud_count);
int getStudentCount();
// logging
void logTable(FILE *txt);
void logOutputStudent(FILE *txt, Student &student);
void logOutputArray(FILE *txt, Student *studs, int stud_count);


// ------------------------ HELPER FUNCTIONS ----------------------------- //
// search
Student *findStudentByName(Student *studs, char *name, int stud_count);
int binarySearchByGroup(Student *studs, int stud_count, int find_group);
// sort
void quicksortByName(Student *studs, int low, int high);
void selectionSortByGroup(Student *studs, int stud_count);
void insertionSortByPriority(Student* studs, int count, int min_salary);
// compare
int nameComp(char *first, char *second);
bool comparePriority(const Student& a, const Student& b, int min_salary);

#endif