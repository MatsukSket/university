#include <iostream>
#include <iomanip>
#include "Tree.h"

int menu() {
    std::cout << "\n1. Add element\n"
                 "2. Delete element\n"
                 "3. Print pre-order\n"
                 "4. Print post-order\n"
                 "5. Print in-order\n"
                 "6. Get data by key\n"
                 "7. Print the count of symbols in each element\n"
                 "0. Exit\n"
                 "Enter the number of activity: ";
    int whatToDo;
    std::cin >> whatToDo;
    return whatToDo; 
}

int main()
{
    Tree myTree;

    int testKeys[] = {1, 2, 3, 4, 5, 6, 7};
    char *testData[]= {"aa", "bb", "cc", "dd", "ee", "ff", "gg"};
    for(int i = 0; i < 7; i++)
        myTree.insert(testKeys[i], testData[i]);

    int whatToDo;
    while(true) {
        switch (menu())
        {
        case 1: {   // insertion
            std::cout << "Enter key: ";
            int key;        std::cin >> key;
            std::cin.ignore();
            std::cout << "Enter data: "; 
            char data[30];  std::cin.getline(data, 30);
            myTree.insert(key, data);
            break;
        }
        case 2: {   // delete
            std::cout << "Enter key to delete: ";
            int key;        std::cin >> key;
            myTree.deleteEl(key);
            break;
        }
        case 3:     // pre-order
            myTree.printPreOrder();
            break;
        case 4:     // post-order
            myTree.printPostOrder();
            break;
        case 5:     // in-order
            myTree.printInOrder();
            break;
        case 6: {   // get data
            std::cout << "Enter key to find: ";
            int key;        std::cin >> key;
            myTree.printData(myTree.search(key));  
            break; 
        }
        case 7:     // my task
            myTree.completeTask();
            break;
        case 0:     // exit
            return 0;
        default:
            std::cout << "Incorrect input. Try again\n";
            break;
        }
    }
    return 0;
}

// cd C:\Users\User\Desktop\university\sem2\OAIP\lab5
// g++ lab5.cpp -o lab5 Tree.cpp
<<<<<<< HEAD
// ./lab5.exe
=======
// ./lab5.exe
>>>>>>> 32870f7 (linux after pull)
