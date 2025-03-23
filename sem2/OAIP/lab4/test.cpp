#include <iostream>
#include <stack>
#include <unordered_set>
#include <map>
#include <cmath>
#include <string>

using namespace std;

// Структура для стека
struct Stack {
    char info;
    Stack* next;
};

// Функция для добавления элемента в стек
Stack* InStack(Stack* begin, char value) {
    Stack* t = new Stack;
    t->info = value;
    t->next = begin;
    return t;
}

// Функция для извлечения элемента из стека
Stack* OutStack(Stack* begin, char* value) {
    if (begin == nullptr) {
        cerr << "Стек пуст!" << endl;
        return nullptr;
    }
    *value = begin->info;
    Stack* t = begin;
    begin = begin->next;
    delete t;
    return begin;
}

// Функция для определения приоритета операций
int Prior(char a) {
    switch (a) {
        case '^': return 4;
        case '*': case '/': return 3;
        case '+': case '-': return 2;
        case '(': return 1;
        default: return 0;
    }
}

// Функция для вычисления результата выражения в ОПЗ
double Rezult(const string& Str, const map<char, double>& variables) {
    stack<double> st;
    unordered_set<char> znak = {'*', '/', '+', '-', '^'};

    for (char ch : Str) {
        if (znak.find(ch) == znak.end()) {
            // Если это операнд, помещаем его значение в стек
            st.push(variables.at(ch));
        } else {
            // Если это операция, извлекаем два операнда и выполняем операцию
            double op1 = st.top(); st.pop();
            double op2 = st.top(); st.pop();
            double rez = 0;
            switch (ch) {
                case '+': rez = op2 + op1; break;
                case '-': rez = op2 - op1; break;
                case '*': rez = op2 * op1; break;
                case '/': rez = op2 / op1; break;
                case '^': rez = pow(op2, op1); break;
            }
            st.push(rez);
        }
    }
    return st.top();
}

int main() {
    // Входная строка
    string InStr = "a+b*(c-d)/e";
    string OutStr = "";

    // Множество знаков операций
    unordered_set<char> znak = {'*', '/', '+', '-', '^'};

    // Стек для операций
    Stack* begin = nullptr;

    // Преобразование в ОПЗ
    for (char ss : InStr) {
        if (ss == '(') {
            begin = InStack(begin, ss);
        } else if (ss == ')') {
            char a;
            while (begin != nullptr && begin->info != '(') {
                begin = OutStack(begin, &a);
                OutStr += a;
            }
            if (begin != nullptr) {
                begin = OutStack(begin, &a); // Удаляем '('
            }
        } else if (ss >= 'a' && ss <= 'z') {
            OutStr += ss;
        } else if (znak.find(ss) != znak.end()) {
            while (begin != nullptr && Prior(begin->info) >= Prior(ss)) {
                char a;
                begin = OutStack(begin, &a);
                OutStr += a;
            }
            begin = InStack(begin, ss);
        }
    }

    // Очистка стека
    while (begin != nullptr) {
        char a;
        begin = OutStack(begin, &a);
        OutStr += a;
    }

    cout << "Обратная польская запись: " << OutStr << endl;

    // Значения переменных
    map<char, double> variables = {
        {'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}
    };

    // Вычисление результата
    double result = Rezult(OutStr, variables);
    cout << "Результат: " << result << endl;

    return 0;
}