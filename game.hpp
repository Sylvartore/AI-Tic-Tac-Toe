//
// Created by Sylvartore on 3/4/2019.
//

#ifndef TTT_GAME_HPP
#define TTT_GAME_HPP

#include "board.hpp"

class game {
public:
    game() {
        my_board = board{};
        isO = true;
    }

    void start() {
        cout << "Game began!" << endl << endl;
        short winStatus = 0;
        while (winStatus == 0) {
            take_turns();
            winStatus = my_board.hasWinner();
        }
        game_over(winStatus);
    }

private:
    board my_board;
    bool isO;

    void take_turns() {
        cout << "Now is " << (isO ? "O" : "X") << " turn" << endl;
        my_board.print();
        prompt_move();
        isO = !isO;
    }

    void prompt_move() {
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
        my_board.move(selection[0] - 'a', selection[1] - '1', isO);
    }

    void game_over(short winner) {
        my_board.print();
        cout << "Game Over, ";
        if (winner == 1) cout << "O won!" << endl;
        else if (winner == 2) cout << "X won!" << endl;
        else cout << "it's a draw!" << endl;
    }
};


#endif //TTT_GAME_HPP
