#pragma once

#include "../board.hh"

namespace reversi::com::evaluatorMAX {

using namespace BitOperation;

int evaluate(const Board& current, bool turn) {
    return popcount(current(turn)) - popcount(current(!turn));
}
}  // namespace reversi::com::evaluatorMAX
