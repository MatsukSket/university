#include <iostream>
#include <stdio.h>
#include <vector>
#include <iomanip>
#include <cstring>

using namespace std;
struct Student
{   
    char name[20];
    int group;
    int phys, math, inf;
    float average = (phys + math + inf) / 3.;
};

void writeData(vector<Student> vec)
{
    FILE* journal = fopen("journal.txt", "w");

    fprintf(journal, "%d\n", vec.size());
    for (auto stud : vec)
        fprintf(journal, "%s %d %d %d %d %.1f\n", stud.name, stud.group, stud.phys, stud.math, stud.inf, stud.average);
    
    fclose(journal);
}

void readData(vector<Student>& vec)
{
    FILE* journal = fopen("journal.txt", "r");

    int studCount;
    char count[3];
    fscanf(journal, "%s", count);
    studCount = atoi(count);

    for (int i = 0; i < studCount; i++){
        Student stud;
        char groupC[8], physC[3], mathC[3], infC[3], averageC[5]; 
        fscanf(journal,"%s%s%s%s%s%s", stud.name, groupC, physC, mathC, infC, averageC);
        stud.group = atoi(groupC);
        stud.phys = atoi(physC);
        stud.math = atoi(mathC);
        stud.inf = atoi(infC);
        stud.average = atof(averageC);
        vec.push_back(stud);
    }
    
    fclose(journal);
}

void enterData(vector<Student>& vec, int& studCount)
{
    cout << "Enter a count of students: "; cin >> studCount;

    cout << "Enter name, number of group, phisics grade, math grade and informatics grade of each student in this order: \n";
    vec.clear();
    for (int i = 0; i < studCount; i++) {
        Student newStud;
        cin >> newStud.name >> newStud.group >> newStud.phys >> newStud.math >> newStud.inf;
        newStud.average = (newStud.phys + newStud.math + newStud.inf) / 3.;
        vec.push_back(newStud);
    }
}

void outputData(vector<Student>& vec)
{
    for (auto stud : vec)
        printf("%s %d %d %d %d %.1f\n", stud.name, stud.group, stud.phys, stud.math, stud.inf, stud.average);
}

void addStudent(vector<Student>& vec, int& studCount)
{
    studCount++;
    Student newStud;
    
    cout << "Enter name, number of group, phisics grade, math grade and informatics grade of student in this order: \n";
    cin >> newStud.name >> newStud.group >> newStud.phys >> newStud.math >> newStud.inf;
    newStud.average = (newStud.phys + newStud.math + newStud.inf) / 3.;
    
    vec.push_back(newStud);
}

void findGoodInf(vector<Student>& goodInf, vector<Student>& vec)
{
    for(auto& stud : vec)
        if(stud.inf >= 9)
            goodInf.push_back(stud);
}

void editInfo(vector<Student>& vec, char name[])
{
    int nameLen, listLen = vec.size();
    for (int i = 0; name[i] != '\0'; i++)
        nameLen = i + 1;
    
    
    for (int i = 0; i < listLen; i++){
        bool findIt = true;
        char* listName = vec[i].name;
        int studLen;
        for (int i = 0; listName[i] != '\0'; i++)
            studLen = i + 1;

        for (int i = 0; i < nameLen || i < studLen; i++) {
            if(name[i] != listName[i] || name[i+1] != listName[i+1])
                findIt = false;
        }
        if(findIt){
            int group, phys, math, inf;
            cout << "Enter new group, phisics, math and informatics grades:\n";
            cin >> group >> phys >> math >> inf;
            vec[i].group = group;
            vec[i].phys = phys;
            vec[i].math = math;
            vec[i].inf = inf;
            vec[i].average = (phys + math + inf) / 3.;
            return;
        }
    }
}

void deleteStudent(vector<Student>& vec, char name[])
{
    int nameLen, listLen = vec.size();
    for (int i = 0; name[i] != '\0'; i++)
        nameLen = i + 1;
    
    
    for (int i = 0; i < listLen; i++){
        bool findIt = true;
        char* listName = vec[i].name;
        for (int i = 0; i < nameLen; i++) {
            if(name[i] != listName[i] || name[i+1] != listName[i+1])
                findIt = false;
        }
        if(findIt){
            for(int j = i + 1; j < listLen; j++) {
                vec[j-1] = vec[j];
            }
            vec.resize(listLen-1);
            return;
        }
    }
}

void sortByName(vector<Student>& vec) 
{   
    int studCount = vec.size();
    for (int i = 0; i < studCount - 1; i++)
        for (int j = 0; j < studCount - i - 1; j++)
            if (strcmp(vec[j].name, vec[j+1].name) > 0)
                swap(vec[j], vec[j+1]);

}

void sortByGroup(vector<Student>& vec) 
{   
    int studCount = vec.size();
    for (int i = 0; i < studCount - 1; i++)
        for (int j = 0; j < studCount - i - 1; j++)
            if (vec[j].group > vec[j+1].group)
                swap(vec[j], vec[j+1]);
}

void sortByPhys(vector<Student>& vec) 
{   
    int studCount = vec.size();
    for (int i = 0; i < studCount - 1; i++)
        for (int j = 0; j < studCount - i - 1; j++)
            if (vec[j].phys > vec[j+1].phys)
                swap(vec[j], vec[j+1]);
}

void sortByMath(vector<Student>& vec) 
{   
    int studCount = vec.size();
    for (int i = 0; i < studCount - 1; i++)
        for (int j = 0; j < studCount - i - 1; j++)
            if (vec[j].math > vec[j+1].math)
                swap(vec[j], vec[j+1]);
}

void sortByInf(vector<Student>& vec) 
{   
    int studCount = vec.size();
    for (int i = 0; i < studCount - 1; i++)
        for (int j = 0; j < studCount - i - 1; j++)
            if (vec[j].inf > vec[j+1].inf)
                swap(vec[j], vec[j+1]);
}

void sortByAverage(vector<Student>& vec) 
{   
    int studCount = vec.size();
    for (int i = 0; i < studCount - 1; i++)
        for (int j = 0; j < studCount - i - 1; j++)
            if (vec[j].average > vec[j+1].average)
                swap(vec[j], vec[j+1]);
}

int main() 
{
    int studCount;
    vector<Student> studList;
    // enterData(studList, studCount);
    // writeData(studList);

    cout << "There are the list of operations:\n";
    cout << "1. Create a new list\n";
    cout << "2. View the list\n";
    cout << "3. Add a student\n";
    cout << "4. Complete an individual task\n";
    cout << "5. Edit a student !!!doesn't work!!!\n";
    cout << "6. Delete a student\n";
    cout << "7. Sort the list\n";
    cout << "0. Exit\n";

    while(true) {
        int what_operation;
        cout << "Enter what operation do you want to do: "; cin >> what_operation;
        
        vector<Student> goodInf;
        char edit_name[20], delete_name[20];

        switch (what_operation)
        {
        case 1: // create list
            studList.clear();
            enterData(studList, studCount);
            writeData(studList);
            break;
        case 2: // view list
            studList.clear();
            readData(studList);
            outputData(studList);
            break;
        case 3: // add student
            studList.clear();
            readData(studList);
            addStudent(studList, studCount);
            writeData(studList);
            break;
        case 4: // my task
            goodInf.clear();
            studList.clear();

            readData(studList);
            findGoodInf(goodInf, studList);
            outputData(goodInf);
            break;
        case 5: // edit student         !!!doesnt work!!!
            studList.clear();

            cout << "There are all students:\n";
            readData(studList);
            outputData(studList);

            cout << "Enter the student's name to edit: "; cin >> edit_name;
            editInfo(studList, edit_name);
            writeData(studList);
            break;
        case 6: // delete student
            studList.clear();

            cout << "There are all students:\n";
            readData(studList);
            outputData(studList);

            cout << "Enter the student's name to edit: "; cin >> delete_name;
            deleteStudent(studList, delete_name);
            writeData(studList);
            break;
        case 7: // sort list
            studList.clear();
            int what_sort;

            cout << "Sort by what you want to do?\n";
            cout << "1. Name\n";
            cout << "2. Group number\n";
            cout << "3. Physics grade\n";
            cout << "4. Math grade\n";
            cout << "5. Informatics grade\n";
            cout << "6. Average grade\n";

            cout << "Enter the number: ";   cin >> what_sort;
            readData(studList);
            switch (what_sort)
            {
            case 1:
                sortByName(studList);
                writeData(studList);
                break;
            case 2:
                sortByGroup(studList);
                writeData(studList);
                break;
            case 3:
                sortByPhys(studList);
                writeData(studList);
                break;
            case 4:
                sortByMath(studList);
                writeData(studList);
                break;
            case 5:
                sortByInf(studList);
                writeData(studList);
                break;
            case 6:
                sortByAverage(studList);
                writeData(studList);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
        if (what_operation == 0) break;
    }


    return 0;
}