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

    explicit ai(bool isO) : isO{isO} {}

    pair<short, short> get_best_move(const board &my_board, bool with_pruning);

private:
    bool isO;

    short min_value(board &cur_board);

    short max_value(board &cur_board);

    short min_value(board &cur_board, short alpha, short beta);

    short max_value(board &cur_board, short alpha, short beta);

    short utility(short terminal_status) {
        short end;
        if (terminal_status == 3) end = 0;
        else if (isO) end = terminal_status == 1 ? (short) 1 : (short) -1;
        else end = terminal_status == 2 ? (short) 1 : (short) -1;
        return end;
    }
};


#endif //TTT_AI_HPP
