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

    void push(int new_value){
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

    void print(){
        if(isEmpty()){
            std::cout << "Queue is empty\n";
            return;
        }

        Node *curr = new Node;
        curr = last;
        while(curr){
            std::cout << curr->data << ' ';
            curr = curr->next;
        }
        std::cout << '\n';
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
            other.push(curr->data);
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

    std::cout << "1 - Add\n2 - View one\n3 - View all\n4 - Delete one\n5 - Delete all\n6 - Task\n0 - Exit\n";

    bool stop = false;
    while(!stop){
        std::cout << "Enter the number of activity: ";
        std::cin >> whatToDo;

        switch (whatToDo)
        {
        // push
        case 1:
            myQueue.push(getRandom());
            break;

        // view one
        case 2:
            if(myQueue.isEmpty()){
                std::cout << "Queue is empty\n";
                break;
            }

            std::cout << myQueue.front() << '\n';
            break;
        
        // view all
        case 3:
            myQueue.print();
            break;

        // delete one
        case 4:
            myQueue.pop();
            break;

        // delete all
        case 5:
            myQueue.deleteAll();
            break;

        // complete task
        case 6:
            if(myQueue.isEmpty()){
                std::cout << "Stack is empty\n";
                break;
            }

            myQueue.copyToMax(taskQueue);
            taskQueue.print();
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