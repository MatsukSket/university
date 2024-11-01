#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

vector<int> u;

int check_num() {
    int k; cin >> k;

    while(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits <streamsize>::max(), '\n');
		cout << "Вводите только числа: ";
		cin >> k;
    }
    return k;
}

bool find_el(vector<int> vec, int el) {
    for (int it : vec)
        if (el == it)
            return true;
    return false;
}

int check_el(vector<int> vec) {
    int k = check_num();

    if (!find_el(u, k)) {
        cout << "Этого числа нет в универсальном множестве, введите число от 1 до 100: ";
        return check_el(vec);
    }

    if (find_el(vec, k)) {
        cout << "Не повторяйтесь, введите новое число: ";
        return check_el(vec);
    } 
    return k;
}

void print_set(vector<int> vec) {
    for (int it : vec)
        cout << it << ' ';
    cout << endl;
    return;
}

void print_add(vector<int> vec) {
    for (int it : u)
        if (!find_el(vec, it))
            cout << it << ' ';
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "ru");

    vector<int> a, b, c, d, e, f, g;
    int n1, n2, n3, k;

    //заполнение универсального множества
    for(int i = 1; i <= 100; i++)
        u.push_back(i);
    
    //ввод множества А
    cout << "Введите мощность множества A: "; n1 = check_num();
    cout << "Введите множество A: ";
    do {
        a.push_back(check_el(a));
    } while (a.size() != n1);
    
    //ввод множества В
    cout << "Введите мощность множества B: "; n2 = check_num();
    cout << "Введите множество B: ";
    do {
        b.push_back(check_el(b));
    } while (b.size() != n2);

    //объединение, множество С
    c = a;  n3 = n1;
    for (int it : b) 
        if (!find_el(c, it))
            c.push_back(it);
    
    //пересечение, множество D
    for (int it : c)
        if (find_el(a, it) && find_el(b, it))
            d.push_back(it);

    //Разность множеств А и В, множество E
    for (int it : a)
        if (!find_el(b, it))
            e.push_back(it);
     
    //Разность множеств B и A, множество F
    for (int it : b)
        if (!find_el(a, it))
            f.push_back(it);
     
    //Cимметричная разность множеств А и В, множество G
    for (int it : c)
        if (!find_el(a, it) || !find_el(b, it))
            g.push_back(it);
    
    cout << "Множество А: ";                            print_set(a);
    cout << "Множество B: ";                            print_set(b);
    cout << "Объединение множеств А и В: ";             print_set(c);
    cout << "Пересечение множеств А и В: ";             print_set(d);
    cout << "Разность множеств А и В: ";                print_set(e);
    cout << "Разность множеств B и A: ";                print_set(f);
    cout << "Симметричная разность множеств А и В: ";   print_set(g);
    cout << "Дополнение множества А: ";                 print_add(a);
    return 0;
}