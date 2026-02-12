#include <UnitTest++/UnitTest++.h>
#include "Game.h"
#include <vector>
#include <sstream>
#include <stdexcept>
#include <set>
#include <iostream>

std::string capture_print(const Game& g) {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    g.display();
    std::cout.rdbuf(old);
    return buffer.str();
}

TEST(Default_Constructor) {
    Game g;
    CHECK_EQUAL(4, g.get_size());
    CHECK_EQUAL(0, g[16]); 
    CHECK(g.is_solved());  
}

TEST(Custom_Constructor_Valid) {
    std::vector<std::vector<int>> board = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9,10,11,12},
        {13,14,15,0}
    };
    Game g(board);
    CHECK(g.is_solved());
    CHECK_EQUAL(3, g.get_empty_x());
    CHECK_EQUAL(3, g.get_empty_y());
}

TEST(Custom_Constructor_Invalid_Size) {
    std::vector<std::vector<int>> board = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };
    CHECK_THROW(Game g(board), std::invalid_argument);
}

TEST(Custom_Constructor_No_Empty_Cell) {
    std::vector<std::vector<int>> board = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9,10,11,12},
        {13,14,15,16} 
    };
    CHECK_THROW(Game g(board), std::invalid_argument);
}

TEST(Is_Solved_True) {
    std::vector<std::vector<int>> board = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9,10,11,12},
        {13,14,15,0}
    };
    Game g(board);
    CHECK(g.is_solved());
}

TEST(Is_Solved_False) {
    std::vector<std::vector<int>> board = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9,10,11,12},
        {13,15,14,0}
    };
    Game g(board);
    CHECK(!g.is_solved());
}

TEST(Count_Inversions) {
    std::vector<std::vector<int>> board = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9,10,11,12},
        {13,15,14,0}
    };
    Game g(board);
    CHECK_EQUAL(1, g.count_inversions());
}

TEST(Is_Solvable_True) {
    std::vector<std::vector<int>> board = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9,10,11,12},
        {13,14,15,0}
    };
    Game g(board);
    CHECK(g.is_solvable());
}

TEST(Is_Solvable_False) {
    std::vector<std::vector<int>> unsolvable = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9,10,11,12},
        {13,15,14,0}
    };
    Game g(unsolvable);
    CHECK(!g.is_solvable());
}

TEST(Is_Valid_Move_True) {
    Game g;
    CHECK(g.is_valid_move(2, 3)); 
    CHECK(g.is_valid_move(3, 2)); 
}

TEST(Is_Valid_Move_False) {
    Game g;
    CHECK(!g.is_valid_move(0, 0)); 
    CHECK(!g.is_valid_move(3, 3)); 
    CHECK(!g.is_valid_move(-1, 0));
    CHECK(!g.is_valid_move(4, 0)); 
}

TEST(Move_Valid) {
    Game g;
    CHECK(g.move(15)); 
    
    CHECK_EQUAL(3, g.get_empty_x());
    CHECK_EQUAL(2, g.get_empty_y());
    CHECK_EQUAL(15, g.get_board()[3][3]);
    CHECK_EQUAL(0, g.get_board()[3][2]);
}

TEST(Move_Invalid_Tile_Value) {
    Game g;
    CHECK_THROW(g.move(0), std::invalid_argument);
    CHECK_THROW(g.move(16), std::invalid_argument);
    CHECK_THROW(g.move(-5), std::invalid_argument);
}

TEST(Move_Not_Ad_jacent) {
    Game g;
    CHECK_THROW(g.move(1), std::invalid_argument); 
}

TEST(Subscript_Operator) {
    Game g;
    CHECK_EQUAL(1, g[1]);
    CHECK_EQUAL(2, g[2]);
    CHECK_EQUAL(15, g[15]);
    CHECK_EQUAL(0, g[16]);

    CHECK_THROW(g[0], std::out_of_range);
    CHECK_THROW(g[17], std::out_of_range);
}

TEST(Getters) {
    Game g;
    auto board = g.get_board();
    CHECK_EQUAL(4, board.size());
    CHECK_EQUAL(4, board[0].size());
    CHECK_EQUAL(3, g.get_empty_x());
    CHECK_EQUAL(3, g.get_empty_y());
}

TEST(Get_Size) {
    Game g;
    CHECK_EQUAL(4, g.get_size());
}

TEST(Create_RandomBoard_Solvable) {
    Game g;
    g.create_random_board();
    CHECK(g.is_solvable());
    
    int zeros = 0;
    for (int i = 1; i <= 16; i++) {
        if (g[i] == 0) zeros++;
    }
    CHECK_EQUAL(1, zeros);
    
    std::set<int> values;
    for (int i = 1; i <= 16; i++) {
        values.insert(g[i]);
    }
    CHECK_EQUAL(16, values.size());
    CHECK(values.find(0) != values.end());
    CHECK(values.find(15) != values.end());
}

TEST(Move_Edge_Cases) {
    std::vector<std::vector<int>> board = {
        {0, 2, 3, 4},
        {1, 6, 7, 8},
        {5,10,11,12},
        {9,13,14,15}
    };
    Game g(board);
    CHECK_EQUAL(0, g.get_empty_x());
    CHECK_EQUAL(0, g.get_empty_y());
    CHECK(g.is_valid_move(0,1)); 
    CHECK(g.is_valid_move(1,0)); 
    CHECK(g.move(2));
    CHECK_EQUAL(0, g.get_empty_x());
    CHECK_EQUAL(1, g.get_empty_y());
}

TEST(Move_Updates_State_Correctly) {
    Game g;
    CHECK(g.is_solved());
    
    g.move(15);
    CHECK(!g.is_solved());
    CHECK_EQUAL(0, g[15]); 
    CHECK_EQUAL(15, g[16]);
    
    g.move(15);
    CHECK(g.is_solved());
    CHECK_EQUAL(15, g[15]);
    CHECK_EQUAL(0, g[16]);
}

TEST(Display_Called) {
    Game g;
    std::string out = capture_print(g);
    std::string solved_board = "\n=========================\n|  1  |  2  |  3  |  4  |\n|=====|=====|=====|=====|\n|  5  |  6  |  7  |  8  |\n|=====|=====|=====|=====|\n|  9  | 10  | 11  | 12  |\n|=====|=====|=====|=====|\n| 13  | 14  | 15  |     |\n=========================\n\n";
    
    CHECK_EQUAL(solved_board, out);
}

int main() {
    return UnitTest::RunAllTests();
}