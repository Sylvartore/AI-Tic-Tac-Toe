//
// Created by Sylvartore on 3/4/2019.
//

#include "game.hpp"

game::game() {
    my_board = board{};
    isPvP = select_mode();
    isTurnO = true;
    if (!isPvP) {
        isPlayO = select_side();
        my_ai = ai{!isPlayO};
    }
}

void game::start() {
    cout << "Game began!" << endl << endl;
    short winStatus = 0;
    while (winStatus == 0) {
        take_turns();
        winStatus = my_board.terminal_test();
    }
    game_over(winStatus);
}

void game::take_turns() {
    if (isPvP || (isPlayO && isTurnO) || (!isPlayO && !isTurnO)) {
        cout << "Now is " << (isTurnO ? "O" : "X") << " turn" << endl;
        my_board.print();
        pair<short, short> move = prompt_move();
        my_board.move(move.first, move.second, isTurnO);
    } else {
        auto start = chrono::high_resolution_clock::now();
        pair<short, short> move = my_ai.get_best_move(my_board, true);
        auto finish = std::chrono::high_resolution_clock::now();
        double time = (double) ((chrono::duration_cast<chrono::nanoseconds>(finish - start)).count()) / 1000000;
        cout << "AI moved at " << (char) (move.first + 'a') << (char) (move.second + '1') << ", took "
             << time << "ms search with pruning ";


        start = chrono::high_resolution_clock::now();
        my_ai.get_best_move(my_board, false);
        finish = std::chrono::high_resolution_clock::now();
        time = (double) ((chrono::duration_cast<chrono::nanoseconds>(finish - start)).count()) / 1000000;
        cout << time << "ms search without pruning";
        
        cout << endl;
        my_board.move(move.first, move.second, isTurnO);
    }
    isTurnO = !isTurnO;
}

pair<short, short> game::prompt_move() const {
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

void game::game_over(short winner) const {
    my_board.print();
    cout << "Game Over, ";
    if (winner == 1) cout << "O won!" << endl;
    else if (winner == 2) cout << "X won!" << endl;
    else cout << "it's a draw!" << endl;
}

bool game::select_mode() const {
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

bool game::select_side() const {
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
