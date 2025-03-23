// не работает ввод имени на русском языке!!!
#include <iostream>
#include <stdio.h>
#include <iomanip>

using namespace std;

struct student{
    char fio[50];
    int group;
    float score;
    bool activist;
    int income;
};

void Create(FILE*);
void AddStud(FILE*);
void EnterStudentData(student*);
void ViewAll(FILE*);
void OutputStudentData(student*);
void EditStud(FILE*);
void DeleteStud(FILE*);
void LineSearchFIO(FILE*);
void BinSearchGroup(FILE*);
void QuickSortFIO(FILE*);
void SelectionSortGroup(FILE*);
void InsertSortScore(FILE*);
void SignSearch(FILE*);
int strComp(char*, char*);
void ReadData(FILE*, student*, int*, int*);

int main()
{   
    setlocale(0, "ru");
    
    FILE* file = fopen("students.bin", "rb");
    if (file == nullptr) {
        cout << "Ошибка при открытии файла!\n";
        return -1;
    }
    fclose(file);
    
    cout << "Меню\n"
            "1 - Создать новый файл\n"
            "2 - Добавить студента\n"
            "3 - Просмотр\n"
            "4 - Редактировать данные о студенте\n"
            "5 - Удаление информации о студенте\n"
            "6 - Линейный поиск по ФИО\n"
            "7 - Бинарный поиск номеру группы\n"
            "8 - Быстрая сортировка по ФИО\n"
            "9 - Сортировка выбором по номеру группы\n"
            "10 - Сортировка вставками по среднему баллу\n"
            "11 - Поиск по признаку\n"
            "12 - Составить очередь\n"
            "0 - Выход.\n";
    
    int what_to_do;
    bool end_program;
    do{
        end_program = false;
        cout << "Выберите номер операции: ";    cin >> what_to_do;
        switch (what_to_do)
        {
        case 1:
            Create(file);
            break;
        case 2:
            AddStud(file);
            break;
        case 3:
            ViewAll(file);
            break;
        case 4:
            EditStud(file);
            break;
        case 5:
            DeleteStud(file);
            break;
        case 6:
            
        case 0:
            return 0;
        default:
            break;
        }
    }while(!end_program);
    return 0;
}

void Create(FILE* file)
{   
    file = fopen("students.bin", "wb");
    if(!file){
        cout << "Ошибка при открытии файла!\n";
        return;
    }
    fclose(file);
    return;
}

void AddStud(FILE* file)
{   
    file = fopen("students.bin", "ab");
    if(!file){
        cout << "Ошибка при открытии файла!\n";
        return;
    }

    student stud;
    cin.ignore();
    EnterStudentData(&stud);

    fwrite(&stud, sizeof(student), 1, file);
    fclose(file);
}

void EnterStudentData(student* stud)
{
    cout << "Введите ФИО студента: "; cin.getline(stud->fio, 50);
    cout << "Введите номер группы: "; cin >> stud->group;
    cout << "Введите средний балл: "; cin >> stud->score;
    cout << "Студент активист? (1 - да, 0 - нет): "; cin >> stud->activist;
    cout << "Средний доход на члена семьи: "; cin >> stud->income;
}

void ViewAll(FILE* file)
{
    file = fopen("students.bin", "rb");
    if(!file){
        cout << "Ошибка при открытии файла!\n";
        return;
    }
    
    student stud;
    printf("%-30s%-10s%-15s%-15s%-10s\n", "  FIO", "Group", "Av. score", "activist", "income");
    while(fread(&stud, sizeof(student), 1, file)){
        OutputStudentData(&stud);
    }
    fclose(file);
}   

void EditStud(FILE* file) {
    file = fopen("students.bin", "rb+");
    if (!file) {
        cout << "Ошибка при открытии файла!\n";
        return;
    }

    char name_find[50];
    cin.ignore();
    cout << "Введите имя студента для редактирования: ";
    cin.getline(name_find, 50);

    student stud;
    bool success = false;
    long int pos = 0;

    while (fread(&stud, sizeof(student), 1, file)) {
        if (strComp(stud.fio, name_find) == 0) {
            success = true;
            cout << "Введите новые данные для студента:\n";
            EnterStudentData(&stud);

            fseek(file, pos, SEEK_SET);
            fwrite(&stud, sizeof(student), 1, file);
            break;
        }
        pos = ftell(file);
    }
    fclose(file);

    
    if (success) 
        cout << "Изменения применены\n";
    else
        cout << "Нет студента с таким именем\n";
    
}

void DeleteStud(FILE* file) 
{   
    // чтение, поиск, удаление
    file = fopen("students.bin", "rb");
    if(!file){
        cout << "Ошибка при чтении файла!\n";
        return;
    }

    bool success = false;
    char name_find[50];
    cin.ignore();
    cout << "Введите имя студента для удаления: ";
    cin.getline(name_find, 50);

    student studs[50];
    int count = -1, pos = -1;
    for(int i = 0; fread(&studs[i], sizeof(student), 1, file); i++){
        if(strComp(studs[i].fio, name_find) == 0){
            i--;
            success = true;
        }
        count = i + 1;
    }
    fclose(file);

    // запись
    file = fopen("students.bin", "wb");
    if(!file){
        cout << "Ошибка при записи в файл!\n";
        return;
    }

    for(int i = 0; i < count; i++){
        fwrite(&studs[i], sizeof(student), 1, file);
    }
    fclose(file);

    if (success) 
        cout << "Информация о студенте удалена\n";
    else
        cout << "Нет студента с таким именем\n";
}

void OutputStudentData(student* stud)
{
    printf("%-30s%-10d%-15.2f%-15d%-10d\n", stud->fio, stud->group, stud->score, stud->activist, stud->income);
}

int strComp(char* str1, char* str2)
{   
    // 0 - str1=str2
    // positive - str1>str2
    // negative - str1<str2
    int i;
    for(i = 0; str1[i] != '\0' && str2[i] != '\0'; i++)
        if(str1[i] != str2[i])
            return str1[i] - str2[i];
    return str1[i] - str2[i];
}

