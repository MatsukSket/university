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

// main functions
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

#endif