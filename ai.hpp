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

    pair<short, short> get_best_move_without_pruning(const board &my_board) {
        short max = -2;
        pair<short, short> best;
        for (pair<short, short> &each : my_board.get_all_moves()) {
            board copy = my_board;
            copy.move(each.first, each.second, isO);
            short utility = min_value(copy);
            if (max == -2 || utility > max) {
                max = utility;
                best = each;
            }
        }
        return best;
    };

    pair<short, short> get_best_move_with_pruning(const board &my_board) {
        short max = -2;
        pair<short, short> best;
        for (pair<short, short> &each : my_board.get_all_moves()) {
            board copy = my_board;
            copy.move(each.first, each.second, isO);
            short utility = min_value(copy, -2, 2);
            if (max == -2 || utility > max) {
                max = utility;
                best = each;
            }
        }
        return best;
    };
private:
    bool isO;

    short min_value(board &cur_board) {
        short terminal_status = cur_board.terminal_test();
        if (terminal_status != 0) return utility(terminal_status);
        short v = 2;
        pair<short, short> action;
        for (pair<short, short> &each :cur_board.get_all_moves()) {
            board copy = cur_board;
            copy.move(each.first, each.second, !isO);
            short utility = max_value(copy);
            if (utility < v) {
                v = utility;
                action = each;
            }
        }
        return v;
    }

    short max_value(board &cur_board) {
        short terminal_status = cur_board.terminal_test();
        if (terminal_status != 0) return utility(terminal_status);
        short v = -2;
        pair<short, short> action;
        for (pair<short, short> &each :cur_board.get_all_moves()) {
            board copy = cur_board;
            copy.move(each.first, each.second, isO);
            short utility = min_value(copy);
            if (utility > v) {
                v = utility;
                action = each;
            }
        }
        return v;
    }

    short min_value(board &cur_board, short alpha, short beta) {
        short terminal_status = cur_board.terminal_test();
        if (terminal_status != 0) return utility(terminal_status);
        short v = 2;
        pair<short, short> action;
        for (pair<short, short> &each :cur_board.get_all_moves()) {
            board copy = cur_board;
            copy.move(each.first, each.second, !isO);
            short utility = max_value(copy, alpha, beta);
            if (utility < v) {
                v = utility;
                action = each;
            }
            if (utility <= alpha) {
                return utility;
            }
            beta = min(beta, utility);
        }
        return v;
    }

    short max_value(board &cur_board, short alpha, short beta) {
        short terminal_status = cur_board.terminal_test();
        if (terminal_status != 0) return utility(terminal_status);
        short v = -2;
        pair<short, short> action;
        for (pair<short, short> &each :cur_board.get_all_moves()) {
            board copy = cur_board;
            copy.move(each.first, each.second, isO);
            short utility = min_value(copy, alpha, beta);
            if (utility > v) {
                v = utility;
                action = each;
            }
            if (utility >= beta) {
                return utility;
            }
            alpha = max(alpha, utility);
        }
        return v;
    }

    short utility(short terminal_status) {
        short end;
        if (terminal_status == 3) end = 0;
        else if (isO) end = terminal_status == 1 ? (short) 1 : (short) -1;
        else end = terminal_status == 2 ? (short) 1 : (short) -1;
        return end;
    }
};


#endif //TTT_AI_HPP
