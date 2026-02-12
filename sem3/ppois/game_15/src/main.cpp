#include <iostream>
#include <limits>
#include "Game.h"

void showMenu();
void newGame(Game &game);
void moveTile(Game &game);


int main() {
    Game game;
    int choice;
    do {
        showMenu();
        std::cout << "Enter your choice: ";
        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                newGame(game);
                break;
            case 2:
                moveTile(game);
                break;
            case 3:
                game.display();
                break;
            case 0:
                std::cout << "Exiting the game.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
    return 0;
}

void showMenu() {
    std::cout << "========MENU========\n"
              << "| 1. New game      |\n"
              << "| 2. Move          |\n" 
              << "| 3. Show board    |\n"
              << "| 0. Exit          |\n"
              << "====================\n";
}

void newGame(Game& game) {
    game.create_random_board();
    game.display();
}

void moveTile(Game& game) {
    int tile;
    std::cout << "Enter the tile number to move: ";
    std::cin >> tile;
    std::cout << "\n";
    
    try {
        if (game.move(tile)) {
            std::cout << "Moved tile " << tile << " successfully.\n";
        } else {
            std::cout << "Invalid move for tile " << tile << ".\n";
        }
        if(game.is_solved()) 
            std::cout << "Congratulations! The puzzle is complete!\n\n";
        else
            game.display();
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << ". Try again.\n";
    }
}