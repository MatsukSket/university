#include <iostream>

using namespace std;

struct Node 
{
    int data;
    Node *next;

    Node() { data = 0; next = nullptr; }  
};

bool myComp(int a, int b) {
    return (a >= 0 && b >= 0) || (a < 0 && b < 0);
}

int main()
{
    Node *sp = nullptr, *sm = nullptr, *t;  // StackPlus, StackMinus, Temp
    
    for(int i = 0; i < 8; i++){
        t = new Node;
        scanf("%d", &t->data);
        t->next = sp;
        sp = t;
    }

    t = sp;
    while (t) {
        printf("%d ", t->data);
        t = t->next;
    }
    printf("\n");

    // решение
    Node *curr = sp; 
    sm = sp;
    while(sp && sp->data < 0) {
        t = sp;
        sp = sp->next;
        curr = sp;
    }
    while(sm && sm->data >= 0) {
        t = sm;
        sm = sm->next;
        curr = sm;
    }
    while (curr && curr->next) {
        if (!myComp(curr->data, curr->next->data)) {
            t->next = curr->next;
            t = curr;
        }
        curr = curr->next;
    }
    t->next = nullptr;

    // вывод
    t = sp;
    while (t) {
        printf("%d ", t->data);
        t = t->next;
    }
    printf("\n");

    t = sm;
    while (t) {
        printf("%d ", t->data);
        t = t->next;
    }

    // освобождение памяти
    while (sp) {
        t = sp;
        sp = sp->next;
        delete t;
    }
    while (sm) {
        t = sm;
        sm = sm->next;
        delete t;
    }
    return 0;
}