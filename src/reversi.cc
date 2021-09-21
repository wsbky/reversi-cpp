#include "reversi.hh"

#include <fstream>
#include <iostream>

using namespace reversi;

int main() {
    std::ofstream record;
    record.open("record.txt", std::ios::out);
    std::ofstream log;
    log.open("playlog.txt", std::ios::out);

    com1 black(evaluator02::evaluate, 5);
    com2 white(evaluator02::evaluate, evaluator03::evaluate,
               evaluatorMAX::evaluate, 5, 7, 12, 25);

    Search bs = [&](const Board& a, bool b) { return black.search(a, b); };
    Search ws = [&](const Board& a, bool b) { return white.search(a, b); };

    Reversi play(bs, ws, std::cin, std::cout, record);
    // play.playCvC();
    play.playHvC();
    // play.playCvH();
    // play.playHvH();

    return 0;
}
