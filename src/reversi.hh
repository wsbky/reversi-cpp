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

void cvh(Board& current, Search black, std::istream& is, std::ostream& os,
         std::ostream& ros) {
    bool turn = true;
    while (!current.isFinish()) {
        if (current.isPass(turn)) {
            os << (turn ? "●" : "○") << " passed.\n";
            turn = !turn;
            continue;
        }
        os << "\n" << current.toString(true, turn);
        if (turn) player::com(black, current, turn, os, ros);
        else
            player::human(current, turn, is, os, ros);

        turn = !turn;
    }
}
void cvc(Board& current, Search black, Search white, std::ostream& os,
         std::ostream& ros) {
    bool turn = true;
    while (!current.isFinish()) {
        if (current.isPass(turn)) {
            os << (turn ? "●" : "○") << " passed.\n";
            turn = !turn;
            continue;
        }
        os << "\n" << current.toString(true, turn);
        if (turn) player::com(black, current, turn, os, ros);
        else
            player::com(white, current, turn, os, ros);

        turn = !turn;
    }
}
}  // namespace PlayLoops

class Reversi {
    Search cbs;
    Search cws;

    std::istream& is = std::cin;
    std::ostream& os = std::cout;
    std::ostream& ros = std::cout;

  public:
    Reversi(Search com_black_search, Search com_white_search)
        : cbs(com_black_search),
          cws(com_white_search) {}
    Reversi(Search com_black_search, Search com_white_search,
            std::istream& is_a, std::ostream& os_a, std::ostream& ros_a)
        : cbs(com_black_search),
          cws(com_white_search),
          is(is_a),
          os(os_a),
          ros(ros_a) {}

    void playHvH() {
        Board current;

        PlayLoops::hvh(current, is, os, ros);

        os << "\n---------------------\n";
        if (current.judge() == 1) os << "● wins: ";
        else if (current.judge() == -1)
            os << "○ wins: ";
        else
            os << "Draw: ";
        os << "● " << BitOperation::popcount(current(true)) << " : "
           << BitOperation::popcount(current(false)) << " ○\n\n";
        os << current.toString();
        os << "---------------------\n";
    }
    void playHvC() {
        Board current;

        PlayLoops::hvc(current, cws, is, os, ros);

        os << "\n---------------------\n";
        if (current.judge() == 1) os << "● wins: ";
        else if (current.judge() == -1)
            os << "○ wins: ";
        else
            os << "Draw: ";
        os << "● " << BitOperation::popcount(current(true)) << " : "
           << BitOperation::popcount(current(false)) << " ○\n\n";
        os << current.toString();
        os << "---------------------\n";
    }
    void playCvH() {
        Board current;

        PlayLoops::cvh(current, cbs, is, os, ros);

        os << "\n---------------------\n";
        if (current.judge() == 1) os << "● wins: ";
        else if (current.judge() == -1)
            os << "○ wins: ";
        else
            os << "Draw: ";
        os << "● " << BitOperation::popcount(current(true)) << " : "
           << BitOperation::popcount(current(false)) << " ○\n\n";
        os << current.toString();
        os << "---------------------\n";
    }
    void playCvC() {
        Board current;

        PlayLoops::cvc(current, cbs, cws, os, ros);

        os << "\n---------------------\n";
        if (current.judge() == 1) os << "● wins: ";
        else if (current.judge() == -1)
            os << "○ wins: ";
        else
            os << "Draw: ";
        os << "● " << BitOperation::popcount(current(true)) << " : "
           << BitOperation::popcount(current(false)) << " ○\n\n";
        os << current.toString();
        os << "---------------------\n";
    }
};

}  // namespace reversi
