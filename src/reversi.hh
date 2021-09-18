#pragma once

#include <cctype>
#include <iostream>
#include <sstream>

#include "board.hh"
#include "com/01.hh"

namespace reversi {

namespace player {
Board humam(Board current, bool turn, std::istream& is, std::ostream& os,
            std::ostream& ros) {
    char s1, s2;
    int x = -1, y = -1;

    for (;;) {
        os << (turn ? "●" : "○") << " (x y): ";
        is >> s1;
        if (s1 == 'p') {
            ros << (turn ? "Black" : "White") << ": passed\n";
            return current;
        }
        is >> s2;
        if (std::isdigit(s1) && std::isdigit(s2)) {
            x = s1 - '0';
            y = s2 - '0';
        }

        if (current.canPut(BitOperation::toBit(x - 1, y - 1), turn)) break;
    }
    ros << (turn ? "Black" : "White") << ": " << x << " " << y << "\n";
    return current.put(BitOperation::toBit(x - 1, y - 1), turn);
}
}  // namespace player

void play(std::istream& is = std::cin, std::ostream& os = std::cout,
          std::ostream& ros = std::cout) {
    Board current;
    bool turn = true;

    while (!current.isFinish()) {
        if (current.isPass(turn)) {
            os << (turn ? "●" : "○") << " passed.\n";
            turn = !turn;
            continue;
        }
        os << "\n" << current.toString(true, turn);
        current = player::humam(current, turn, is, os, ros);
        turn = !turn;
    }
    if (current.judge() == 1) os << "● wins\n";
    else if (current.judge() == -1)
        os << "○ wins\n";
    else
        os << "Draw\n";
}

void play_com(std::istream& is = std::cin, std::ostream& os = std::cout,
              std::ostream& ros = std::cout) {
    Board current;
    bool turn = true;

    while (!current.isFinish()) {
        if (current.isPass(turn)) {
            os << (turn ? "●" : "○") << " passed.\n";
            turn = !turn;
            continue;
        }
        os << "\n" << current.toString(true, turn);
        if (turn) current = player::humam(current, turn, is, os, ros);
        else
            current = player::com1(current, turn, os, ros);
        turn = !turn;
    }
}

}  // namespace reversi
