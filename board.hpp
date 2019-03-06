//
// Created by Sylvartore on 3/4/2019.
//

#ifndef TTT_BOARD_HPP
#define TTT_BOARD_HPP

#include <iostream>
#include <vector>

using namespace std;

class board {
public:
    static constexpr short rows = 3;

    board();

    void print() const;

    bool isValidMove(short row, short col) const {
        return state[row][col] == '+';
    }

    void move(short row, short col, bool isO) {
        if (isO) state[row][col] = 'O';
        else state[row][col] = 'X';
    }

    vector<pair<short, short>> get_all_moves() const;

    short terminal_test() const;

    bool check_col(short row, short col, char possible_winner, short array_number) const {
        if (array_number == 3) return true;
        if (row > rows - 1 || col > rows - 1 || row < 0 || col < 0) return false;
        return state[row][col] == possible_winner && check_col(row + (short) 1, col, state[row][col], ++array_number);
    }

    bool check_row(short row, short col, char possible_winner, short array_number) const {
        if (array_number == 3) return true;
        if (row > rows - 1 || col > rows - 1 || row < 0 || col < 0) return false;
        return state[row][col] == possible_winner && check_row(row, col + (short) 1, state[row][col], ++array_number);
    }

    bool check_dia_r(short row, short col, char possible_winner, short array_number) const {
        if (array_number == 3) return true;
        if (row > rows - 1 || col > rows - 1 || row < 0 || col < 0) return false;
        return state[row][col] == possible_winner &&
               check_dia_r(row + (short) 1, col + (short) 1, state[row][col], ++array_number);
    }

    bool check_dia_l(short row, short col, char possible_winner, short array_number) const {
        if (array_number == 3) return true;
        if (row > rows - 1 || col > rows - 1 || row < 0 || col < 0) return false;
        return state[row][col] == possible_winner &&
               check_dia_l(row + (short) 1, col - (short) 1, state[row][col], ++array_number);
    }

private:
    char state[rows][rows]{};
};


#endif //TTT_BOARD_HPP
