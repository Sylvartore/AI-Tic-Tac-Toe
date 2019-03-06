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

    board() {
        for (auto &row : state) {
            for (char &cell : row) {
                cell = '+';
            }
        }
    }

    void print() const {
        cout << endl << "  ";
        for (short i = 0; i < rows; i++) cout << " " << (char) ('1' + i);
        cout << endl;

        for (short row = 0; row < rows; row++) {
            cout << " " << (char) ('a' + row) << " ";
            for (short col = 0; col < rows; col++) {
                cout << state[row][col] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    bool isValidMove(short row, short col) const {
        return state[row][col] == '+';
    }

    void move(short row, short col, bool isO) {
        if (isO) state[row][col] = 'O';
        else state[row][col] = 'X';
    }

    vector<pair<short, short>> get_all_moves() const {
        vector<pair<short, short>> all_moves;
        for (short row = 0; row < board::rows; row++) {
            for (short col = 0; col < board::rows; col++) {
                if (isValidMove(row, col)) all_moves.emplace_back(row, col);
            }
        }
        return all_moves;
    }

    short terminal_test() const {
        bool draw = true;
        for (short row = 0; row < rows; row++) {
            for (short col = 0; col < rows; col++) {
                if (state[row][col] != '+') {
                    if (check_col(row, col, state[row][col], 0) || check_row(row, col, state[row][col], 0) ||
                        check_dia_r(row, col, state[row][col], 0) || check_dia_l(row, col, state[row][col], 0)) {
                        return state[row][col] == 'O' ? (short) 1 : (short) 2;
                    }
                } else if (draw) draw = false;
            }
        }
        return draw ? (short) 3 : (short) 0;
    }

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
