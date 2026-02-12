#include <iostream>
#include <string>
#include <algorithm>
#include "Set.h"

int main()
{
    using namespace std;

    Set current;
    string line;

    while (true) {
        cout << "Enter set A: \n";
        if (!std::getline(cin, line)) return 0;
        try {
            current = Set(line);
            break;
        } catch (const exception &e) {
            cout << "Error in set A: " << e.what() << "\nTry again.\n";
        }
    }

    while (true) {
        cout << "\n========Menu========\n"
             << "1. Union\n"
             << "2. Intersection\n"
             << "3. Difference\n"
             << "4. Symmetric difference\n"
             << "5. Power\n"
             << "6. Boolean\n"
             << "7. Show set A\n"
             << "8. Re-enter set A\n"
             << "0. Exit\n"
             << "Choise action: ";

        if (!std::getline(cin, line)) break;
        int choice = -1;

        try {
            choice = std::stoi(line);
        } catch (...) {
            choice = -1;
        }

        switch (choice) {
            case 1: // Union
                cout << "Enter set B: \n";
                if (!std::getline(cin, line)) break;
                try {
                    Set b(line);
                    cout << "Result of union A & B: ";
                    (current + b).print();
                    cout << "\n";
                } catch (const exception &e) {
                    cout << "Error in set B: " << e.what() << "\n";
                }
                break;

            case 2: // Intersection
                cout << "Enter set B: \n";
                if (!std::getline(cin, line)) break;
                try {
                    Set b(line);
                    cout << "Result of intersection A & B: ";
                    (current * b).print();
                    cout << "\n";
                } catch (const exception &e) {
                    cout << "Error in set B: " << e.what() << "\n";
                }
                break;

            case 3: // Difference
                cout << "Enter set B: \n";
                if (!std::getline(cin, line)) break;
                try {
                    Set b(line);
                    cout << "Result of difference A & B: ";
                    (current - b).print();
                    cout << "\n";
                } catch (const exception &e) {
                    cout << "Error in set B: " << e.what() << "\n";
                }
                break;

            case 4: // Symmetric difference
                cout << "Enter set B: \n";
                if (!std::getline(cin, line)) break;
                try {
                    Set b(line);
                    cout << "Result of symmetric difference A & B: ";
                    (current / b).print();
                    cout << "\n";
                } catch (const exception &e) {
                    cout << "Error in set B: " << e.what() << "\n";
                }
                break;

            case 5: // Power
                cout << "Power of set A: " << current.get_power() << "\n";
                break;

            case 6: // Boolean
                cout << "Boolean of set A: ";
                try {
                    current.boolean().print();
                    cout << "\n";
                } catch (const exception &e) {
                    cout << "Error in calculating of boolean: " << e.what() << "\n";
                }
                break;

            case 7: // Show current
                cout << "Set A: ";
                current.print();
                cout << "\n";
                break;
            
            case 8: // Re-enter A
                while (true) {
                    cout << "Enter set A: \n";
                    if (!std::getline(cin, line)) return 0;
                    try {
                        current = Set(line);
                        break;
                    } catch (const exception &e) {
                        cout << "Error in set A: " << e.what() << "\nTry again.\n";
                    }
                }
                break;

            case 0:
                cout << "Programm is end.\n";
                return 0;
            default:
                cout << "No such operation. Try again.\n";
        }
    }

    return 0;
}