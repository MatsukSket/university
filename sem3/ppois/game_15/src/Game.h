#ifndef GAME_H
#define GAME_H

#include <vector>

class Game
{
private:
    const int SIZE = 4;
    std::vector<std::vector<int>> board;
    int emptyX, emptyY;

public:
    Game();
    Game(const std::vector<std::vector<int>> &customBoard);

    void create_random_board();
    bool is_solved() const;

    bool move(int val);
    bool is_valid_move(const int& tileX, const int& tileY) const;

    void display() const;

    int get_empty_x() const;
    int get_empty_y() const;
    std::vector<std::vector<int>> get_board() const;
    int get_size() const;

    int operator [](int index) const;

    void create_board();
    int count_inversions() const;
    bool is_solvable() const;
};

#endif