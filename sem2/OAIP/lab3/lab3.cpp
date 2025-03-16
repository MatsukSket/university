#include <iostream>
#include <ctime>
#include <cstdlib>

int getRandom(){
    return rand() % 199 - 99;
}

class List{
private:
    class Node{
    public:
        int data;
        Node *next = NULL;
        Node *prev = NULL;
    };
    Node *head = NULL;
    Node *last = NULL;

public:
    bool isEmpty(){
        return head == NULL;
    }

    int front(){
        return last->data;
    }

    void pushfront(int new_value){
        Node *new_node = new Node;
        new_node->data = new_value;

        if(isEmpty()){
            head = new_node;
            last = new_node;
            return;
        }
        
        head->next = new_node;
        new_node->prev = head;
        head = new_node;
    }

    void pushback(int new_value){
        Node *new_node = new Node;
        new_node->data = new_value;

        if(isEmpty()){
            head = new_node;
            last = new_node;
            return;
        }

        last->prev = new_node;
        new_node->next = last;
        last = new_node;
    }

    void pop(){
        if(isEmpty()){
            std::cout << "Queue is empty\n";
            return;
        }

        Node *temp = last;
        last = last->next;
        if(last)
            last->prev = NULL;
        else {
            head->prev = NULL;
            head = NULL;
        }
        
        delete temp;
    }    

    void printFront(){
        if(isEmpty()){
            std::cout << "Queue is empty\n";
            return;
        }

        Node *curr = last;
        while(curr){
            std::cout << curr->data << ' ';
            curr = curr->next;
        }
        std::cout << '\n';
    }

    void printBack(){
        if(isEmpty()){
            std::cout << "Queue is empty\n";
            return;
        }

        Node *curr = head;
        while(curr){
            std::cout << curr->data << ' ';
            curr = curr->prev;
        }
        std::cout << "\n";
    }

    Node *findMax()
    {
        Node *max_element = head;
        Node *curr = head->prev;
        
        while(curr){
            if(curr->data > max_element->data)
                max_element = curr;
            curr = curr->prev;
        }

        return max_element;
    }

    void copyToMax(List &other) 
    {
        other.deleteAll();
        Node *curr = findMax();

        while(curr){
            other.pushfront(curr->data);
            curr = curr->next;
        }
    }

    void deleteAll(){
        while(last)
            pop();
    }

    ~List(){
        deleteAll();
    }
};

int main()
{
    srand(static_cast<unsigned int>(time(0))); 

    int whatToDo;
    List myQueue, taskQueue;

    std::cout << "1 - Add front\n"
                 "2 - Add back\n"
                 "3 - View front\n"
                 "4 - View back\n"
                 "5 - Delete one\n"
                 "6 - Delete all\n"
                 "7 - Task\n"
                 "0 - Exit\n";

    bool stop = false;
    while(!stop){
        std::cout << "Enter the number of activity: ";
        std::cin >> whatToDo;

        switch (whatToDo)
        {
        // push
        case 1:
            myQueue.pushfront(getRandom());
            myQueue.printFront();
            break;
        case 2:
            myQueue.pushback(getRandom());
            myQueue.printFront();
            break;
        
        // view 
        case 3:
            myQueue.printFront();
            break;
        case 4:
            myQueue.printBack();
            break;

        // delete one
        case 5:
            myQueue.pop();
            break;

        // delete all
        case 6:
            myQueue.deleteAll();
            break;

        // complete task
        case 7:
            if(myQueue.isEmpty()){
                std::cout << "Stack is empty\n";
                break;
            }

            myQueue.copyToMax(taskQueue);
            taskQueue.printFront();
            break;
        case 0:
            stop = true;
            break;
        default:
            std::cout << "Incorrect input. Try again\n";
            break;
        }
    }

    return 0;
}