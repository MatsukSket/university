#include <iostream>
#include "Game.h"
#include <iomanip>
#include <stdexcept>
#include <random>
#include <algorithm>

Game::Game() : board(SIZE, std::vector<int>(SIZE)), emptyX(SIZE - 1), emptyY(SIZE - 1) {
    create_board();
}

Game::Game(const std::vector<std::vector<int>>& customBoard) {
    if (customBoard.size() != SIZE || customBoard[0].size() != SIZE) {
        throw std::invalid_argument("Invalid board size.");
    }
    
    board = customBoard;
    
    bool foundEmpty = false;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                emptyX = i;
                emptyY = j;
                foundEmpty = true;
            }
        }
    }
    
    if (!foundEmpty) {
        throw std::invalid_argument("Board must contain empty cell (0)");
    }
}

void Game::create_board() {
    int val = 1;
    for (int i = 0; i < SIZE; i++) 
        for (int j = 0; j < SIZE; j++) 
            board[i][j] = val++;

    board[SIZE - 1][SIZE - 1] = 0;
    emptyX = SIZE - 1;
    emptyY = SIZE - 1;
}

void Game::display() const {
    std::cout << "\n=========================\n";
    for (int i = 0; i < SIZE; i++) {
        std::cout << "|";

        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0)
                std::cout << "     |";
            else
                std::cout << " " << std::setw(2) << board[i][j] << "  |";
        }

        if (i < SIZE - 1) {
            std::cout << "\n|=====|=====|=====|=====|\n";
        }
    }

    std::cout << "\n=========================\n\n";
}

void Game::create_random_board() {
    std::random_device rd;
    std::mt19937 g(rd());
    do {
    std::vector<int> val;
    for (int i = 0; i < SIZE * SIZE; i++) 
        val.push_back(i);

    std::shuffle(val.begin(), val.end(), g);

    int val_idx = 0;
    for (int i = 0; i < SIZE; i++) 
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = val[val_idx++];
            if (board[i][j] == 0) {
                emptyX = i;
                emptyY = j;
            }
        }
    } while (!is_solvable() && !is_solved());
}

bool Game::is_solved() const {
    int val = 1;
    for (int i = 0; i < SIZE; i++) 
        for (int j = 0; j < SIZE; j++) {
            if (i == SIZE - 1 && j == SIZE - 1) {
                if (board[i][j] != 0)
                    return false;
            }
            else if (board[i][j] != val++) 
                return false;
        }

    return true;
}   

bool Game::is_solvable() const {
    int inversions = count_inversions();
    int emplty_row_from_bottom = SIZE - emptyX;

    return (inversions + emplty_row_from_bottom) % 2 == 1;
}

int Game::count_inversions() const {
    int inversions = 0;
    std::vector<int> linear_board;

    for (int i = 0; i < SIZE; i++) 
        for (int j = 0; j < SIZE; j++) 
            if (board[i][j] != 0) 
                linear_board.push_back(board[i][j]);
            
    for (int i = 0; i < SIZE * SIZE - 1; i++)
        for (int j = i + 1; j < SIZE * SIZE; j++)
            if (linear_board[i] > linear_board[j])
                inversions++;

    return inversions;
}

bool Game::move(int val) {
    if (val <= 0 || val >= SIZE * SIZE) 
        throw std::invalid_argument("Invalid tile value.");
    
    for (int i = 0; i < SIZE; i++) 
        for (int j = 0; j < SIZE; j++) 
            if (board[i][j] == val) {
                if (is_valid_move(i, j)) {
                    board[emptyX][emptyY] = val;
                    board[i][j] = 0;
                    emptyX = i;
                    emptyY = j;
                    return true;
                } 
                else 
                    throw std::invalid_argument("Invalid move.");
            }

    return false;
}

bool Game::is_valid_move(const int& tileX, const int& tileY) const {
    if (tileX == -1 || tileY == -1 )
        return false;
    
    return (tileX == emptyX && std::abs(tileY - emptyY) == 1) || 
           (tileY == emptyY && std::abs(tileX - emptyX) == 1);
}

int Game::get_empty_x() const {
    return emptyX;
}

int Game::get_empty_y() const {
    return emptyY;
}

std::vector<std::vector<int>> Game::get_board() const {
    return board;
}

int Game::get_size() const {
    return SIZE;
}

int Game::operator [](int index) const {
    if (index < 1 || index > SIZE * SIZE)
        throw std::out_of_range("Index out of range.");
    
    int x = (index - 1) / SIZE,
        y = (index - 1) % SIZE;
    return board[x][y];
}