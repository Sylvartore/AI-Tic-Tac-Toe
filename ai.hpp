//
// Created by Sylvartore on 3/4/2019.
//

#ifndef TTT_AI_HPP
#define TTT_AI_HPP

#include <iostream>
#include "board.hpp"

using namespace std;

class ai {
public:
    ai() = default;

    pair<short, short> get_best_move(const board &my_board) {
        for (short row = 0; row < board::rows; row++) {
            for (short col = 0; col < board::rows; col++) {
                if (my_board.isValidMove(row, col)) return make_pair(row, col);
            }
        }
    };
private:
};


#endif //TTT_AI_HPP
