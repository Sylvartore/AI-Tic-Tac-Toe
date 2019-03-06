//
// Created by Sylvartore on 3/4/2019.
//

#ifndef TTT_GAME_HPP
#define TTT_GAME_HPP

#include <limits>
#include <chrono>
#include "board.hpp"
#include "ai.hpp"

class game {
public:
    game() {
        my_board = board{};
        isPvP = getMode();
        isTurnO = true;
        if (!isPvP) {
            isPlayO = getSide();
            my_ai = ai{!isPlayO};
        }
    }

    void start() {
        cout << "Game began!" << endl << endl;
        short winStatus = 0;
        while (winStatus == 0) {
            take_turns();
            winStatus = my_board.terminal_test();
        }
        game_over(winStatus);
    }

private:
    board my_board;
    bool isTurnO;
    bool isPvP;
    bool isPlayO;
    ai my_ai{};

    void take_turns() {
        if (isPvP || (isPlayO && isTurnO) || (!isPlayO && !isTurnO)) {
            cout << "Now is " << (isTurnO ? "O" : "X") << " turn" << endl;
            my_board.print();
            pair<short, short> move = prompt_move();
            my_board.move(move.first, move.second, isTurnO);
        } else {
            auto start = chrono::high_resolution_clock::now();
            pair<short, short> move = my_ai.get_best_move_with_pruning(my_board);
            auto finish = std::chrono::high_resolution_clock::now();
            double time1 = (double) ((chrono::duration_cast<chrono::nanoseconds>(finish - start)).count()) / 1000000;

            start = chrono::high_resolution_clock::now();
            my_ai.get_best_move_without_pruning(my_board);
            finish = std::chrono::high_resolution_clock::now();
            double time2 = (double) ((chrono::duration_cast<chrono::nanoseconds>(finish - start)).count()) / 1000000;

            cout << "AI moved at " << (char) (move.first + 'a') << (char) (move.second + '1') << ", took "
                << time1 << "ms search with pruning, " << time2 << "ms search without pruning" << endl;
            my_board.move(move.first, move.second, isTurnO);
        }
        isTurnO = !isTurnO;
    }

    pair<short, short> prompt_move() const {
        cout << "Please make selection: (a1/b2/c3/etc.)" << endl;
        string selection;
        cin >> selection;
        bool valid = selection.size() == 2 && selection[0] >= 'a' && selection[0] <= 'c' &&
                     selection[1] >= '1' && selection[1] <= '3' &&
                     my_board.isValidMove(selection[0] - 'a', selection[1] - '1');
        while (!valid) {
            cout << "Invalid input" << endl;
            cin >> selection;
            valid = selection.size() == 2 && selection[0] >= 'a' && selection[0] <= 'c' &&
                    selection[1] >= '1' && selection[1] <= '3' &&
                    my_board.isValidMove(selection[0] - 'a', selection[1] - '1');
        }
        return make_pair(selection[0] - 'a', selection[1] - '1');
    }

    void game_over(short winner) const {
        my_board.print();
        cout << "Game Over, ";
        if (winner == 1) cout << "O won!" << endl;
        else if (winner == 2) cout << "X won!" << endl;
        else cout << "it's a draw!" << endl;
    }

    bool getMode() const {
        int mode = 0;
        while (mode != 1 && mode != 2) {
            cout << "Please select mode: " << endl;
            cout << "1. Player vs Player" << endl;
            cout << "2. Player vs AI" << endl;
            if (!(cin >> mode)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! " << endl << endl;
            }
        }
        return mode == 1;
    }

    bool getSide() const {
        int mode = 0;
        while (mode != 1 && mode != 2) {
            cout << "Would you like to play O or X: " << endl;
            cout << "1. O" << endl;
            cout << "2. X" << endl;
            if (!(cin >> mode)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! " << endl << endl;
            }
        }
        return mode == 1;
    }

};


#endif //TTT_GAME_HPP
