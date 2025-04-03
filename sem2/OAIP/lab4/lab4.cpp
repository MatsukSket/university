#include <iostream>

using namespace std;

template <typename T> class Stack{
private:
    struct Node{
        T data;
        Node* next = nullptr;
    };
    Node* head = nullptr;

public:
    // конструктор поумолчанию
    Stack() = default;

    // конструктор копирования
    Stack(const Stack& other) : head(nullptr) {
        *this = other;
    }
    // оператор присвоения
    Stack& operator=(const Stack& other) {
        if (this == &other) {
            return *this; // Проверка на одинаковость
        }

        Stack <T> temp;
        Node* curr = other.head;
        while (curr) {
            temp.push(curr->data);
            curr = curr->next;
        }

        deleteAll();

        while (!temp.isEmpty()) {
            this->push(temp.top());
            temp.pop();
        }

        return *this;
    }

    bool isEmpty() const{
        return head == nullptr;
    }

    void push(T value){
        Node *new_node = new Node;
        new_node->data = value;
        new_node->next = head;
        head = new_node;
    }

    void pop(){
        if (isEmpty()){
            cout << "Error: pop!\n";
            return;
        }

        Node *temp = head;
        head = head->next;
        delete temp;
    }

    T top() const{
        if (isEmpty()){
            cout << "Error: top!\n";
            return T();
        }

        return head->data;
    }

    void print(){
        if (isEmpty()){
            cout << "Stack is emtpy!\n";
            return;
        }

        Node *curr = head;
        while(curr){
            cout << curr->data << ' ';
            curr = curr->next;
        }
        cout << '\n';
    }

    void reverse(){
        Node *curr = head;
        Stack <T> temp;
        while(curr){
            temp.push(curr->data);
            curr = curr->next;
        }
        *this = temp;
    }

    void deleteAll(){
        while(head)
            pop();
    }

    ~Stack(){
        deleteAll();
    }
};

bool isMath(char c){
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isLetter(char c){
    return 'a' <= c && c <= 'z';
}

bool isValid(char *str){
    Stack <char> brackets;

    if(!isLetter(str[0]) && str[0] != '(')
        return false;
    
    if(str[0] == '(')
        brackets.push('(');
    
    for(int i = 1; str[i] != '\0'; i++){
        if(str[i] == '('){
            if(isLetter(str[i-1]) || str[i-1] == ')')
                return false;
            brackets.push('(');
            continue;
        }
        if(str[i] == ')'){
            if(isMath(str[i-1]) || str[i-1] == '(')
                return false;
            if(!brackets.isEmpty())
                brackets.pop();
            else
                return false;
            continue;
        }

        if(isLetter(str[i])){
            if(isLetter(str[i-1]) || str[i-1] == ')')
                return false;
            continue;
        }
        
        if(isMath(str[i])){
            if(isMath(str[i-1]) || str[i-1] == '(')
                return false;
            continue;
        }
    }
    if(!brackets.isEmpty())
        return false;
    return true;
}

int symbol_priority(char a){
    if (a == '+' || a == '-')
        return 1;
    if (a == '*' || a == '/')
        return 2;
    return 0;
}

float get_num(char c){
    // test
    if (c == 'a')   return 5.6;
    if (c == 'b')   return 7.4;
    if (c == 'c')   return 8.9;
    if (c == 'd')   return 3.1;
    if (c == 'e')   return 0.2;
    if (c == 'f')   return 1.5;
    if (c == 'g')   return 2.0;
    if (c == 'h')   return 4.8;
    if (c == 'k')   return 6.3;
    if (c == 'm')   return 9.7;

    // task
    // if (c == 'a')   return 1.6;
    // if (c == 'b')   return 4.9;
    // if (c == 'c')   return 5.7;
    // if (c == 'd')   return 0.8;
    // if (c == 'e')   return 2.3;
    return 0;
}

Stack <char> get_rpn(char* str){
    Stack <char> symbols;
    Stack <char> rpn;
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] == '('){
            symbols.push(str[i]);
            continue;
        }
        if(str[i] == ')'){
            while(!symbols.isEmpty() && symbols.top() != '('){
                rpn.push(symbols.top());
                symbols.pop();
            }
            if(!symbols.isEmpty() && symbols.top() == '(')
                symbols.pop();
            continue;
        }

        if(isLetter(str[i])){
            rpn.push(str[i]);
            continue;
        }
        if(isMath(str[i])){
            while(!symbols.isEmpty() && symbol_priority(str[i]) <= symbol_priority(symbols.top())){
                rpn.push(symbols.top());
                symbols.pop();
            }
            symbols.push(str[i]); 
        }
    }

    while(!symbols.isEmpty()){
        rpn.push(symbols.top());
        symbols.pop();
    }

    return rpn;
}

float get_ans(Stack<char> rpn){
    Stack <float> temp;
    while(!rpn.isEmpty()){
        char symb = rpn.top();      rpn.pop();

        if('a' <= symb && symb <= 'z')
            temp.push(get_num(symb));
        else {
            float x = temp.top();   temp.pop();
            float y = temp.top();   temp.pop();
            switch (symb)
            {
                case '+':
                    temp.push(x+y);
                    break;
                case '-':
                    temp.push(y-x);
                    break;
                case '*':
                    temp.push(x*y);
                    break;
                case '/':
                    temp.push(y/x);
                    break;
                default:
                    break;
            }
        }
    }
    float ans = temp.top();     temp.pop();
    return ans;
}

int main()
{
    Stack <char> rpn;
    char *str = new char[50];

    cout << "enter data: ";
    cin.getline(str, 50);
    for(int i = 0; str[i] != '\0'; i++)
        cout << str[i];
    cout << endl;
    if(!isValid(str)){
        cout << "Error: Invalid input!\n";
        return -1;
    }
    rpn = get_rpn(str);
    rpn.reverse();
    rpn.print();

    cout << get_ans(rpn);
    delete str;
    return 0;
}

// ((a*(b-(c+d)))/((e+f)*(g-h)))+(k/m)
// a*(b-c)/(d+e)