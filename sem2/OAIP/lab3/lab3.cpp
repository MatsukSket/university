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
        Node *next = nullptr;
        Node *prev = nullptr;
    };
    Node *head = nullptr;
    Node *last = nullptr;

public:
    bool isEmpty(){
        return head == nullptr;
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
            std::cout << "List is empty\n";
            return;
        }

        Node *temp = last;
        last = last->next;
        if(last)
            last->prev = nullptr;
        else {
            head->prev = nullptr;
            head = nullptr;
        }
        
        delete temp;
    }    

    void printBack(){
        if(isEmpty()){
            std::cout << "List is empty\n";
            return;
        }

        Node *curr = last;
        while(curr){
            std::cout << curr->data << ' ';
            curr = curr->next;
        }
        std::cout << '\n';
    }

    void printFront(){
        if(isEmpty()){
            std::cout << "List is empty\n";
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

    void moveToMax(List &other) 
    {
        other.deleteAll();
        Node *curr = findMax();

        while(curr){
            other.pushfront(curr->data);
            curr = curr->next;
        }
    }
    // защита
    void task(){
        Node *max_el = findMax();
        Node *dot = head->prev;
        if(dot)
            if(max_el != dot->next && max_el != dot && max_el != dot->prev){
                Node *curr = dot->prev;
                while(curr != max_el){
                    Node *temp = curr;
                    curr = curr->prev;
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                    delete temp;
                }
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
                std::cout << "List is empty\n";
                break;
            }

            // myQueue.moveToMax(taskQueue);
            // taskQueue.printFront();

            myQueue.task();
            myQueue.printFront();
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