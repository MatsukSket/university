#include <iostream>
// test
using namespace std;

struct Node
{
    int data;

    struct Node* prev;
    struct Node* next;
};

struct Node *head = NULL;
struct Node *last = NULL;

bool isEmpty()
{
    return head == NULL;
}

void printList()
{
    struct Node* curr = head;

    printf("\n[ ");
    while(curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("]");
}

void insertFirst(int data)
{
    struct Node *link = new Node;
    link->data = data;
    
    if (isEmpty()) 
        last = link;
    else 
        head->prev = link;
    
    link->prev = NULL;
    link->next = head;
    head = link;
}

void insertLast(int data)
{
    struct Node *link = new Node;
    link->data = data;

    if(isEmpty())
        head = link;
    else
        last->next = link;

    link->next = NULL;
    link->prev = last;
    last = link;
}

void deleteElement()
{
    
}

void deleteAll() {
    struct Node* curr = head;
    while (curr != NULL) {
        struct Node* temp = curr;
        curr = curr->next;
        delete temp;  
    }
    head = NULL;
    last = NULL;
}

int main()
{
    int whatToDo;
    bool stop = false;

    // list of operations
    printf("\n1. Display list");
    printf("\n2. Insert first element");
    printf("\n3. Insert last element");
    printf("\n4. Delete element");
    printf("\n0. Exit");

    while(!stop) {
        printf("\nEnter the number of operation: ");

        scanf("%d", &whatToDo);

        switch (whatToDo)
        {
            int new_value;
        // display list
        case 1:
            if (isEmpty())
                printf("List is empty");
            else
                printList();
            break;

        // insert first element
        case 2:
            printf("Enter the value: ");
            scanf("%d", &new_value);
            insertFirst(new_value);
            break;
        
        // insert last element
        case 3:
            printf("Enter the value: ");
            scanf("%d", &new_value);
            insertLast(new_value);
            break;

        // delete first
        case 4:
            if(isEmpty())
                printf("List is empty.");
            else 
                deleteElement();
            break;
        
        // exit program
        case 0:
            stop = true;
            deleteAll();
            break;
            
        // incorrect input data
        default:
            printf("\nIncorrect input. ");
            break;
        }
    }
    
    return 0;
}