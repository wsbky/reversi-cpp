#pragma once

#include "../board.hh"

namespace reversi::evaluator01 {

using namespace BitOperation;

const board positions1 = 0x8100000000000081;
const board positions2 = 0x3c0081818181003c;
const board positions3 = 0x00003c3c3c3c0000;
const board positions4 = 0x0042000000004200;

int evaluate(const Board& current, bool turn) {
    int a = popcount(current.legalBoard(turn)) -
            popcount(current.legalBoard(!turn));

    int b1 = popcount(current(turn) & positions1);
    int b2 = popcount(current(turn) & positions2);
    int b3 = popcount(current(turn) & positions3);
    int b4 = popcount(current(turn) & positions4);

    int b = b1 * 20 + b2 * 6 + b3 * 3 - b4 * 100;
    return a * 100 + b * 20;
}
}  // namespace reversi::evaluator01
