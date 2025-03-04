#include <iostream>
#include <ctime>
#include <cstdlib>


using namespace std;

struct Stack {
    int data;
    Stack *next;
};

Stack *myStack = NULL;

bool isEmpty(Stack *stack)
{
    return stack == NULL;
}

int random()
{
    return rand() % 199 - 99;
}

void push(Stack **stack, int newValue) 
{
    Stack *link = new Stack;
    link->data = newValue;
    
    link->next = *stack;
    *stack = link;
}

void view(Stack *beg)
{   
    if (isEmpty(myStack))
        cout << "Stack is empty";
    else {
        Stack *curr = beg;
        while(curr){
            cout << curr->data << ' ';
            curr = curr->next;
        }
    }
    cout << endl;
    return;
}

void Del_All(Stack **curr)
{
    while(*curr) {
        Stack *temp = *curr;
        *curr = (*curr)->next;
        delete temp;
    }
}

int main()
{
    int whatToDo, count;
    while (true) {
        cout << "1 - Create\n";
        cout << "2 - Add\n";
        cout << "3 - View\n";
        cout << "4 - Delete\n";
        cout << "5 - Task\n";
        cout << "0 - Exit\n";
        cin >> whatToDo;
        
        switch (whatToDo)
        {
        // create
        case 1: 
            if (!isEmpty(myStack)){
                cout << "Clear memory!\n";
                break;
            }

            cout << "Input the quantity: ";   cin >> count;
           
            for (int i = 0; i < count; i++)
                push(&myStack, random());

            break;
        // add
        case 2:
            cout << "Input the quantity: ";   cin >> count;
            
            for (int i = 0; i < count; i++)
                push(&myStack, random());

            break;
        // view
        case 3:
            if (isEmpty(myStack)) {
                cout << "Stack is empty\n";
                break;
            }
            
            view(myStack);
            break;
        // delete stack
        case 4:
            Del_All(&myStack);
            break;
        // my task
        case 5:
            break;
        // exit
        case 0:
            Del_All(&myStack);
            return 0;
        }
    }
    return 0;
}