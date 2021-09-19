#pragma once

#include <cctype>
#include <functional>
#include <iostream>
#include <sstream>

#include "lib/board.hh"
#include "lib/com01.hh"
#include "lib/evaluators/01.hh"
#include "lib/players.hh"

namespace reversi {

namespace PlayLoops {
// human vs human
void hvh(Board& current, std::istream& is, std::ostream& os,
         std::ostream& ros) {
    bool turn = true;
    while (!current.isFinish()) {
        if (current.isPass(turn)) {
            os << (turn ? "●" : "○") << " passed.\n;";
            turn = !turn;
            continue;
        }
        os << "\n" << current.toString(true, turn);
        player::human(current, turn, is, os, ros);
        turn = !turn;
    }
}

void hvc(Board& current, Search white, std::istream& is, std::ostream& os,
         std::ostream& ros) {
    bool turn = true;
    while (!current.isFinish()) {
        if (current.isPass(turn)) {
            os << (turn ? "●" : "○") << " passed.\n";
            turn = !turn;
            continue;
        }
        os << "\n" << current.toString(true, turn);
        if (turn) player::human(current, turn, is, os, ros);
        else
            player::com(white, current, turn, os, ros);
        turn = !turn;
    }
}
}  // namespace PlayLoops

void playHvH(std::istream& is = std::cin, std::ostream& os = std::cout,
             std::ostream& ros = std::cout) {
    Board current;

    PlayLoops::hvh(current, is, os, ros);

    if (current.judge() == 1) os << "● wins: ";
    else if (current.judge() == -1)
        os << "○ wins: ";
    else
        os << "Draw: ";
}
void playHvC(Search white, std::istream& is = std::cin,
             std::ostream& os = std::cout, std::ostream& ros = std::cout) {
    Board current;

    PlayLoops::hvc(current, white, is, os, ros);

    if (current.judge() == 1) os << "● wins: ";
    else if (current.judge() == -1)
        os << "○ wins: ";
    else
        os << "Draw: ";
}

}  // namespace reversi
