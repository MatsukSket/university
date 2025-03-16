#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <io.h>
#include <iomanip>
#include <Windows.h>
using namespace std;
const char* statusnames[] = { "В обработке", "Доставляется", "Доставлен" };
 
struct client {
    enum status {
        InProgress,
        Delivering,
        Delivered
    };
    char fio[50];
    char meals[10][20];
    int mealscount;
    char time[6];
    float price;
    status orderstatus{ status::InProgress };
};
 
void Create(FILE*);
void ViewAll(FILE*);
void Add(FILE*);
void EditStud(FILE*);
void Delete(FILE*);
void Report(FILE*);
void LineSearchFIO(FILE*);
void BinarySearchPrice(FILE*);
void QuickSortTime(client*, int, int);
void SelectionSortPrice(FILE*);
void InsertSortStatus(FILE*);
void SignSearch(FILE*);
void DeliveryStatistics(FILE*);
int strlen(char*);
int strcomp(char*, char*);
void clientout(client);
void clientin(client&);
void clientswap(FILE*, int pos1, int pos2, client, client);
void ReportFile(FILE*);
void InsertSortStatusArray(FILE*);
void FioArraySort(client*, int, int, float);
int timecomp(char*, char*);
 
int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    FILE* file;
 
    int choice;
    do {
        cout << "Меню\n"
            "1 - Создание нового файла.\n"
            "2 - Просмотр записей из файла.\n"
            "3 - Добавление записей в файл.\n"
            "4 - Редактирование записей в файле.\n"
            "5 - Удаление записей в файле.\n"
            "6 - Линейный поиск в файле по ФИО заказчика.\n"
            "7 - Бинарный поиск в файле по стоимости заказа.\n"
            "8 - Быстрая сортировка по времени оформления заявки.\n"
            "9 - Сортировка выбором по стоимости заказа.\n"
            "10 - Сортировка вставками по статусу заказа.\n"
            "11 - Поиск по признаку: вводится максимальная сумма. Вывести заказы, стоимость которых не превышает указанную, в порядке возрастания времени оформления.\n"
            "12 - Статистика по доставке: для каждого статуса заказа вывести список клиентов в алфавитном порядке. Определить среднюю стоимость заказа.\n"
            "13 - Выход.\n";
        cin >> choice;
 
        switch (choice) {
        case 1:
            Create(file);
            break;
 
        case 2:
            ViewAll(file);
            
            break;
 
        case 3:
            Add(file);
            break;
 
        case 4:
            EditStud(file);
            break;
 
        case 5:
            Delete(file);
            break;
 
        case 6:
            LineSearchFIO(file);
            break;
 
        case 7:
            BinarySearchPrice(file);
            break;
 
        case 8: {
            file = fopen("orders.txt", "a+b");
            if (file == nullptr) {
                cout << "Ошибка при открытии файла!" << endl;
                break;
            }
            int count = _filelength(_fileno(file)) / sizeof(client);
            client* banda = new client[count];
            for (int k = 0; k < count; k++) fread(&banda[k], sizeof(client), 1, file);
            fclose(file);
 
            QuickSortTime(banda, 0, count - 1);
 
            FILE* textfile = fopen("report.txt", "w+");
            if (textfile == nullptr) {
                cout << "Ошибка при открытии файла!" << endl;
                break;
            }
            fprintf(textfile, "%-50s%-20s%-20s%-30s\n", "ФИО", "Время заявки", "Цена", "Статус заказа");
            for (int k = 0; k < count; k++) {
                fprintf(textfile, "%-50s%-20s%-20.2f%-30s", banda[k].fio, banda[k].time, banda[k].price, statusnames[banda[k].orderstatus]);
                fprintf(textfile, "|");
                for (int i = 0; i < banda[k].mealscount - 1; i++) fprintf(textfile, "%s, ", banda[k].meals[i]);
                fprintf(textfile, "%s\n", banda[k].meals[banda[k].mealscount - 1]);
            }
            fclose(textfile);
            delete[] banda;
            break;
        }
 
        case 9:
            SelectionSortPrice(file);
            ReportFile(file);
            break;
 
        case 10:
            InsertSortStatus(file);
            ReportFile(file);
            break;
 
        case 11:
            SignSearch(file);
            break;
 
        case 12:
            DeliveryStatistics(file);
            break;
        }
        cout << endl;
    } while (choice != 13);
    return 0;
}
 
void Create(FILE* file) {
    file = fopen("orders.txt", "w+b");
    if (file == nullptr) {
        cout << "Ошибка при открытии файла!" << endl;
        return;
    }
    fclose(file);
}
 
void ViewAll(FILE* file) {
    file = fopen("orders.txt", "rb");
    if (file == nullptr) {
        cout << "Ошибка при открытии файла!" << endl;
        return;
    }
 
    printf("%-50s%-20s%-20s%-30s\n", "ФИО", "Время заявки", "Цена", "Статус заказа");
    client broski;
    while (fread(&broski, sizeof(client), 1, file)) clientout(broski);
    fclose(file);
}
 
void Add(FILE* file) {
    file = fopen("orders.txt", "ab");
    if (file == nullptr) {
        cout << "Ошибка при открытии файла!" << endl;
        return;
    }
 
    int count;
    cout << "Введите количество заказов: ";
    cin >> count;
    client broski;
    for (int i = 0; i < count; i++) {
        cout << "Заполните данные " << i + 1 << "-го заказа:" << endl;
        clientin(broski);
        fwrite(&broski, sizeof(client), 1, file);
    }
 
    fclose(file);
}
 
void EditStud(FILE* file) {
    file = fopen("orders.txt", "r+b");
    if (file == nullptr) {
        cout << "Ошибка при открытии файла!" << endl;
        return;
    }
    char find[50];
    cin.ignore();
    cin.getline(find, 50);
 
    printf("%-50s%-20s%-20s%-30s\n", "ФИО", "Время заявки", "Цена", "Статус заказа");
    client broski;
    while (fread(&broski, sizeof(client), 1, file)) {
        if (strcomp(broski.fio, find) == 0) {
            clientout(broski);
            cout << "Заполните новые данные для заказа." << endl;
            clientin(broski);
            fseek(file, -static_cast<long>(sizeof(client)), SEEK_CUR);
            fwrite(&broski, sizeof(client), 1, file);
            break;
        }
    }
    fclose(file);
}
 
void Delete(FILE* file) {
    file = fopen("orders.txt", "r+b");
    if (file == nullptr) {
        cout << "Ошибка при открытии файла!" << endl;
        return;
    }
 
    char find[50];
    cout << "Введите ФИО клиента для удаления: ";
    cin.ignore();
    cin.getline(find, 50);
 
    client broski;
    int position = -1;
    while (fread(&broski, sizeof(client), 1, file)) {
        if (strcomp(broski.fio, find) == 0) {
            position = ftell(file) / sizeof(client) - 1;
            break;
        }
    }
    if (position == -1) {
        cout << "Клиент с таким ФИО не найден." << endl;
        return;
    }
    fseek(file, (position + 1) * sizeof(client), SEEK_SET);
    while (fread(&broski, sizeof(client), 1, file)) {
        fseek(file, -static_cast<long>(2 * sizeof(client)), SEEK_CUR);
        fwrite(&broski, sizeof(client), 1, file);
        fseek(file, sizeof(client), SEEK_CUR);
    }
    cout << "Клиент удален!" << endl;
    if (_chsize(_fileno(file), ftell(file) - sizeof(client)) == -1) {
        cout << "Ошибка при изменении размера файла!" << endl;
    }
    fflush(file);
    fclose(file);
}
 
void LineSearchFIO(FILE* file) {
    file = fopen("orders.txt", "rb");
    if (file == nullptr) {
        cout << "Ошибка при открытии файла!" << endl;
        return;
    }
 
    cin.ignore();
    char find[50];
    cout << "Введите ФИО: ";
    cin.getline(find, 50);
 
    client broski;
    bool found = false;
    while (fread(&broski, sizeof(client), 1, file)) {
        if (strcomp(broski.fio, find) == 0) {
            found = true;
            cout << "Клиент найден!" << endl;
            clientout(broski);
            break;
        }
    }
    if (!found) cout << "Клиент с таким ФИО не найден." << endl;
    fclose(file);
}
 
void BinarySearchPrice(FILE* file) {
    file = fopen("orders.txt", "r+b");
    if (file == nullptr) {
        cout << "Ошибка при открытии файла!" << endl;
        return;
    }
    SelectionSortPrice(file);
 
    cout << "Введите стоимость заказа: ";
    float price;
    cin >> price;
 
    client broski;
    int count = _filelength(_fileno(file)) / sizeof(client);
 
    int top = 0, mid, bottom = count - 1;
    bool found = false;
    while (top != bottom) {
        mid = (top + bottom) / 2;
        fseek(file, mid * sizeof(client), SEEK_SET);
        fread(&broski, sizeof(client), 1, file);
        if (price > broski.price) top = mid + 1;
        else if (price < broski.price) bottom = mid - 1;
        else break;
    }
 
    if (top == bottom) {
        fseek(file, top * sizeof(client), SEEK_SET);
        fread(&broski, sizeof(client), 1, file);
    }
 
    if (price == broski.price) clientout(broski);
    else cout << "Клиент с такой стоимостью заказа не найден." << endl;
    fclose(file);
}
 
void QuickSortTime(client* banda, int left, int right) {
    if (left < right) {
        client pivot = banda[right];
        int i = left - 1;
        for (int j = left; j < right; j++) {
            if (timecomp(banda[j].time, pivot.time) == -1) {
                i++;
                swap(banda[i], banda[j]);
            }
        }
        swap(banda[i + 1], banda[right]);
        QuickSortTime(banda, left, i);
        QuickSortTime(banda, i + 2, right);
    }
}
 
void SelectionSortPrice(FILE* file) {
    file = fopen("orders.txt", "r+b");
    if (file == nullptr) {
        cout << "Ошибка при открытии файла!" << endl;
        return;
    }
 
    client broski;
    client temp;
    float minprice = 100000;
    int minposition = 0;
    int count = _filelength(_fileno(file)) / sizeof(client);
    fseek(file, 0, SEEK_SET);
 
    for (int i = 0; i < count - 1; i++) {
        fseek(file, i * sizeof(client), SEEK_SET);
        for (int j = i; fread(&broski, sizeof(client), 1, file); j++) {
            if (broski.price < minprice) {
                minprice = broski.price;
                minposition = j;
            }
        }
        if (minposition != i) clientswap(file, minposition, i, temp, broski);
        else fseek(file, (i + 1) * sizeof(client), SEEK_SET);
    }
    fclose(file);
}
 
void InsertSortStatus(FILE* file) {
    file = fopen("orders.txt", "r+b");
    if (file == nullptr) {
        cout << "Ошибка при открытии файла!" << endl;
        return;
    }
 
    client broski, temp;
    int count = _filelength(_fileno(file)) / sizeof(client);
    for (int i = 1; i < count; i++) {
        fseek(file, (i - 1) * sizeof(client), SEEK_SET);
        fread(&temp, sizeof(client), 1, file);
        fread(&broski, sizeof(client), 1, file);
        fseek(file, -static_cast<long>(sizeof(client)), SEEK_CUR);
 
        for (int j = i; temp.orderstatus > broski.orderstatus && j >= 2; j--) {
            fwrite(&temp, sizeof(client), 1, file);
            fseek(file, -static_cast<long>(3 * sizeof(client)), SEEK_CUR);
            fread(&temp, sizeof(client), 1, file);
        }
        if (temp.orderstatus > broski.orderstatus) {
            fwrite(&temp, sizeof(client), 1, file);
            fseek(file, -static_cast<long>(2 * sizeof(client)), SEEK_CUR);
            fwrite(&broski, sizeof(client), 1, file);
        }
        else if (i != 1) fwrite(&broski, sizeof(client), 1, file);
    }
    fclose(file);
}
 
void SignSearch(FILE* file) {
    file = fopen("orders.txt", "r+b");
    if (file == nullptr) {
        cout << "Ошибка при открытии файла!" << endl;
        return;
    }
 
    cout << "Введите максимальную сумму: ";
    float maxprice;
    cin >> maxprice;
    int count = 0;
    int n = 100;
    client broski;
    client* banda = new client[n];
 
    while (fread(&broski, sizeof(client), 1, file)) {
        if (broski.price <= maxprice) {
            banda[count] = broski;
            count++;
        }
    }
    n = count;
    fclose(file);
 
    QuickSortTime(banda, 0, n - 1);
    for (int i = 0; i < count; i++) clientout(banda[i]);
 
    delete[] banda;
}
 
void DeliveryStatistics(FILE* file) {
    file = fopen("orders.txt", "r+b");
    if (file == nullptr) {
        cout << "Ошибка при открытии файла!" << endl;
        return;
    }
 
    int n = 100;
    client broski;
    client* banda = new client[n];
 
    int count0 = 0, count1 = 0, count2 = 0;
    float price0 = 0, price1 = 0, price2 = 0;
    for (int k = 0; fread(&broski, sizeof(client), 1, file); k++) {
        banda[k] = broski;
        if (broski.orderstatus == 0) {
            count0++;
            price0 += broski.price;
        }
        if (broski.orderstatus == 1) {
            count1++;
            price1 += broski.price;
        }
        if (broski.orderstatus == 2) {
            count2++;
            price2 += broski.price;
        }
    }
    n = count0 + count1 + count2;
    fclose(file);
 
    for (int i = 1; i < n; i++) {
        int j = i - 1;
        client temp = banda[i];
        while (j >= 0 && banda[j].orderstatus < temp.orderstatus) {
            banda[j + 1] = banda[j];
            j--;
        }
        banda[j + 1] = temp;
    }
 
    cout << "Клиенты со статусом заказа \"В обработке\":" << endl;
    FioArraySort(banda, 0, count0, price0);
 
    cout << "Клиенты со статусом заказа \"Доставляется\":" << endl;
    FioArraySort(banda, count0, count1, price1);
 
    cout << "Клиенты со статусом заказа \"Доставлен\":" << endl;
    FioArraySort(banda, count0 + count1, count2, price2);
 
    delete[] banda;
}
 
int strlen(char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}
 
void clientout(client broski) {
    printf("%-50s%-20s%-20.2f%-30s", broski.fio, broski.time, broski.price, statusnames[broski.orderstatus]);
    for (int i = 0; i < broski.mealscount - 1; i++) printf("%s, ", broski.meals[i]);
    printf("%s\n", broski.meals[broski.mealscount - 1]);
}
 
int strcomp(char* str1, char* str2) {
    int count = 0;
    for (int i = 0; str1[i] != '\0' || str2[i] != '\0'; i++) {
        if (str1[i] == str2[i]) count++;
        else if (str1[i] < str2[i]) return 1;
        else return -1;
    }
    if (strlen(str1) == strlen(str2) && count == strlen(str1)) return 0;
    return (strlen(str1) < strlen(str2)) ? 1 : -1;
}
 
void clientin(client& broski) {
    cin.ignore();
    cout << "Введите ФИО: ";
    cin.getline(broski.fio, 50);
    cout << "Введите время заказа в формате XX:YY: ";
    cin.getline(broski.time, 6);
    cout << "Введите конечную стоимость заказа: ";
    cin >> broski.price;
    cin.ignore();
 
    cout << "Выберите статус заказа:" << endl;
    cout << "1 - В обработке." << endl;
    cout << "2 - Доставляется." << endl;
    cout << "3 - Доставлен." << endl;
    int choice;
    do {
        cin >> choice;
        if (choice == 1) broski.orderstatus = client::InProgress;
        else if (choice == 2) broski.orderstatus = client::Delivering;
        else if (choice == 3) broski.orderstatus = client::Delivered;
        else cout << "Попробуйте снова!" << endl;
    } while (choice < 1 || choice > 3);
 
    cout << "Введите количество заказанных блюд: ";
    do {
        cin >> broski.mealscount;
    } while (broski.mealscount < 1);
    cin.ignore();
 
    cout << "Введите блюда." << endl;
    for (int i = 0; i < broski.mealscount; i++) {
        cout << i + 1 << "-е блюдо: ";
        cin.getline(broski.meals[i], 20);
    }
}
 
void clientswap(FILE* file, int pos1, int pos2, client temp, client broski) {
    fseek(file, pos1 * sizeof(client), SEEK_SET);
    fread(&broski, sizeof(client), 1, file);
    fseek(file, pos2 * sizeof(client), SEEK_SET);
    fread(&temp, sizeof(client), 1, file);
    fseek(file, -static_cast<long>(sizeof(client)), SEEK_CUR);
    fwrite(&broski, sizeof(client), 1, file);
    fseek(file, pos1 * sizeof(client), SEEK_SET);
    fwrite(&temp, sizeof(client), 1, file);
}
 
void ReportFile(FILE* file) {
    FILE* textfile = fopen("report.txt", "w+");
    file = fopen("orders.txt", "r+b");
    if (textfile == nullptr || file == nullptr) {
        cout << "Ошибка при открытии файла!" << endl;
        return;
    }
    fseek(file, 0, SEEK_SET);
    client broski;
    fprintf(textfile, "%-50s%-20s%-20s%-30s\n", "ФИО", "Время заявки", "Цена", "Статус заказа");
 
    while (fread(&broski, sizeof(client), 1, file)) {
        fprintf(textfile, "%-50s%-20s%-20.2f%-30s", broski.fio, broski.time, broski.price, statusnames[broski.orderstatus]);
        for (int i = 0; i < broski.mealscount - 1; i++) fprintf(textfile, "%s, ", broski.meals[i]);
        fprintf(textfile, "%s\n", broski.meals[broski.mealscount - 1]);
    }
    fclose(textfile);
    fclose(file);
}
 
int timecomp(char* time1, char* time2) {
    int h1 = (time1[0] - '0') * 10 + (time1[1] - '0');
    int m1 = (time1[3] - '0') * 10 + (time1[4] - '0');
    int h2 = (time2[0] - '0') * 10 + (time2[1] - '0');
    int m2 = (time2[3] - '0') * 10 + (time2[4] - '0');
 
    if (h1 > h2) return 1;
    else if (h1 < h2) return -1;
    else {
        if (m1 > m2) return 1;
        else if (m1 < m2) return -1;
        else return 0;
    }
}
 
void InsertSortStatusArray(FILE* file) {
    file = fopen("orders.txt", "r+b");
    if (file == nullptr) {
        cout << "Ошибка при открытии файла!" << endl;
        return;
    }
    int count = 0;
    int n = 100;
    client broski;
    client* banda = new client[n];
 
    while (fread(&broski, sizeof(client), 1, file)) {
        banda[count] = broski;
        count++;
    }
    n = count;
    fclose(file);
 
    for (int i = 1; i < count; i++) {
        int j = i - 1;
        client temp = banda[i];
        while (j >= 0 && banda[j].orderstatus > temp.orderstatus) {
            banda[j + 1] = banda[j];
            j--;
        }
        if (j + 1 != i) banda[j + 1] = temp;
    }
 
    file = fopen("orders.txt", "w+b");
    for (int i = 0; i < count; i++) fwrite(&banda[i], sizeof(client), 1, file);
    fclose(file);
    delete[] banda;
}
 
void FioArraySort(client* banda, int start, int count, float price) {
    if (count == 0) {
        cout << "Клиенты с таким статусом отсутствуют" << endl;
        return;
    }
    for (int i = start + 1; i < start + count; i++) {
        int j = i - 1;
        client temp = banda[i];
        while (j >= start && strcomp(banda[j].fio, temp.fio) > 0) {
            banda[j + 1] = banda[j];
            j--;
        }
        banda[j + 1] = temp;
    }
 
    for (int p = start; p < start + count; p++) {
        clientout(banda[p]);
    }
    cout << "Средняя стоимость заказов данного статуса: " << (float)price / count << endl;
}