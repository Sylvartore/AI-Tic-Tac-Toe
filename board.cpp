//
// Created by Sylvartore on 3/4/2019.
//

#include "board.hpp"

board::board() {
    for (auto &row : state) {
        for (char &cell : row) {
            cell = '+';
        }
    }
}

void board::print() const {
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

short board::terminal_test() const {
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

vector<pair<short, short>> board::get_all_moves() const {
    vector<pair<short, short>> all_moves;
    for (short row = 0; row < board::rows; row++) {
        for (short col = 0; col < board::rows; col++) {
            if (isValidMove(row, col)) all_moves.emplace_back(row, col);
        }
    }
    return all_moves;
}
