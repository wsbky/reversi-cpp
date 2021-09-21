#include "reversi.hh"

#include <fstream>
#include <iostream>

int main() {
    std::ofstream record;
    record.open("record.txt", std::ios::out);
    std::ofstream log;
    log.open("playlog.txt", std::ios::out);

    reversi::com1 black(reversi::evaluator02::evaluate);
    reversi::com1 white(reversi::evaluator03::evaluate);

    reversi::Search bs = [&](const reversi::Board& a, bool b, int c) {
        return black.search(a, b, c);
    };
    reversi::Search ws = [&](const reversi::Board& a, bool b, int c) {
        return white.search(a, b, c);
    };

    reversi::Reversi play(bs, ws, std::cin, std::cout, record);
    play.playCvC();
    // play.playHvC();
    // play.playCvH();
    // play.playHvH();

    return 0;
}
