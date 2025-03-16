#include <iostream>
#include <ctime>
#include <cstdlib>

int getRandom(){
    return rand() % 10;
}

class Stack{
private:
    class Node{
    public:
        int data;
        Node *next = NULL;
    };
    Node *head = NULL;
    
public:
    bool isEmpty() {
        return head == NULL;
    }

    int top(){
        return head->data;
    }

    void push(int new_value) 
    {
        Node *new_node = new Node;
        new_node->data = new_value;
        new_node->next = head;
        head = new_node; 
    }

    void pop()
    {
        if(!head){
            std::cout << "Stack is empty\n";
            return;
        }

        Node *temp = head;
        head = head->next;
        delete temp;
    }

    void print()
    {
        if(!head){
            std::cout << "Stack is empty\n";
            return;
        }

        Node *curr = head;
        while(curr){
            std::cout << curr->data << ' ';
            curr = curr->next;
        }
        std::cout << '\n';
    }

    Node *findMax()
    {
        Node *max_element = head;
        Node *curr = head->next;
        while(curr){
            if (curr->data > max_element->data)
                max_element = curr;
            curr = curr->next;
        }
        
        return max_element;
    }

    void copyToMax(Stack &other)
    {   
        other.deleteAll();
        Stack temp_stack;
        Node *curr = head, *max_element = findMax();

        while(curr != max_element){
            temp_stack.push(curr->data);
            curr = curr->next;
        }
        temp_stack.push(max_element->data);

        while(!temp_stack.isEmpty()){
            other.push(temp_stack.top());
            temp_stack.pop();
        }
    }

    void def(){
        int counter = 0;
        Node *new_node = new Node;
        new_node->next = head;
        Node *curr = new_node;
        while(curr->next){
            counter++;

            if(counter == 3){
                if(curr->next == head)
                    head = head->next;

                Node *temp = curr->next;
                curr->next = curr->next->next;
                
                counter = 0;
                delete temp;
                continue;
            }

            if(curr->next->data % 2 == 0){
                if(curr->next == head)
                    head = head->next;

                Node *temp = curr->next;
                curr->next = curr->next->next;

                if(counter <= 2)
                    counter++;
                delete temp;
                continue;
            }
            curr = curr->next;
        }
        delete new_node;
    }

    void deleteAll()
    {
        while (head)
            pop();
    }

    ~Stack(){
        deleteAll();
    }
};

int main()
{
    srand(static_cast<unsigned int>(time(0))); 

    int whatToDo;
    Stack myStack, taskStack;

    std::cout << "1 - Add\n"
                 "2 - View one\n"
                 "3 - View all\n"
                 "4 - Delete one\n"
                 "5 - Delete all\n"
                 "6 - Task\n"
                 "7 - Def\n"
                 "0 - Exit\n";

    bool stop = false;
    while(!stop){
        std::cout << "Enter the number of activity: ";
        std::cin >> whatToDo;

        switch (whatToDo)
        {
        // push
        case 1:
            myStack.push(getRandom());
            break;

        // view top
        case 2:
            if(myStack.isEmpty()){
                std::cout << "Stack is empty\n";
                break;
            }

            std::cout << myStack.top() << '\n';
            break;

        // view all
        case 3:
            myStack.print();
            break;

        // delete one
        case 4:
            myStack.pop();
            break;

        //delete all
        case 5:
            myStack.deleteAll();
            break;

        // complete task
        case 6:
            if(myStack.isEmpty()){
                std::cout << "Stack is empty\n";
                break;
            }

            myStack.copyToMax(taskStack);
            taskStack.print();
            break;
        case 7:
            if(myStack.isEmpty()){
                std::cout << "Stack is empty\n";
                break;
            }

            myStack.def();
            myStack.print();
            break;
        
        // exit program
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