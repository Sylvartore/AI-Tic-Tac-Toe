//
// Created by Sylvartore on 3/4/2019.
//

#include "ai.hpp"

pair<short, short> ai::get_best_move(const board &my_board, bool with_pruning) {
    short max = -2;
    pair<short, short> best;
    for (pair<short, short> &each : my_board.get_all_moves()) {
        board copy = my_board;
        copy.move(each.first, each.second, isO);
        short utility = with_pruning ? min_value(copy, -2, 2) : min_value(copy);
        if (max == -2 || utility > max) {
            max = utility;
            best = each;
        }
    }
    return best;
}

short ai::min_value(board &cur_board) {
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

short ai::max_value(board &cur_board) {
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

short ai::min_value(board &cur_board, short alpha, short beta) {
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

short ai::max_value(board &cur_board, short alpha, short beta) {
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
