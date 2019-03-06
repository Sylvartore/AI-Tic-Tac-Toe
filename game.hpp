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
    game();

    void start();

private:
    board my_board;
    bool isTurnO;
    bool isPvP;
    bool isPlayO;
    ai my_ai{};

    void take_turns();

    pair<short, short> prompt_move() const;

    void game_over(short winner) const;

    bool select_mode() const;

    bool select_side() const;
};


#endif //TTT_GAME_HPP
