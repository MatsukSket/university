#include <iostream>
#include <ctime>
#include <cstdlib>

int getRandom(){
    return rand() % 199 - 99;
}

class Stack{
private:
    class Node{
    public:
        int data;
        Node *next = NULL;
    };
    Node *head = NULL;

    void copyFrom(const Stack &other)
    {
        if(!other.head){
            head = NULL;
            return;
        }

        head = new Node{other.head->data, NULL};
        Node *currThis = head;
        Node *currOther = other.head->next;

        while (currOther){
            currThis->next = new Node{currOther->data, NULL};
            currThis = currThis->next;
            currOther = currOther->next;
        }
    }
    
public:

    Stack &operator=(const Stack &other){
        if(this != &other){
            deleteAll();
            copyFrom(other);
        }
        return *this;
    }

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

    int findMax()
    {
        Node *curr = head;
        int max_element = curr->data;
        while(curr){
            if (curr->data > max_element)
                max_element = curr->data;
            curr = curr->next;
        }
        
        return max_element;
    }

    Stack copyToMax()
    {
        Stack temp_stack, reverse_stack;
        Node *curr = head;
        int max_element = findMax(); 

        while(curr){
            temp_stack.push(curr->data);
            if(curr->data == max_element)
                break;
            curr = curr->next;
        }

        while(!temp_stack.isEmpty()){
            reverse_stack.push(temp_stack.top());
            temp_stack.pop();
        }

        reverse_stack.print();

        return reverse_stack;
    }

    void deleteAll()
    {
        while (head) {
            Node *temp = head;
            head = head->next; 
            delete temp;
        }
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

    std::cout << "1 - Add\n";
    std::cout << "2 - View\n";
    std::cout << "3 - Delete last\n";
    std::cout << "4 - Delete all\n";
    std::cout << "5 - Task\n";
    std::cout << "0 - Exit\n";

    bool stop = false;
    while(!stop){
        std::cout << "Enter the number of activity: ";
        std::cin >> whatToDo;

        switch (whatToDo)
        {
        case 1:
            myStack.push(getRandom());
            break;
        case 2:
            myStack.print();
            break;
        case 3:
            myStack.pop();
            break;
        case 4:
            myStack.deleteAll();
            break;
        case 5:
            if(myStack.isEmpty()){
                std::cout << "Stack is empty\n";
                break;
            }

            taskStack = myStack.copyToMax();
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