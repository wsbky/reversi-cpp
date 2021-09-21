#pragma once

#include <vector>

#include "../board.hh"

namespace reversi::evaluator03 {

using namespace BitOperation;

struct searchMove {
    int sx;  // start point x
    int sy;  // start point y
    int dx;  // move direction x
    int dy;  // move direvtion y

    searchMove(int ssx, int ssy, int ddx, int ddy)
        : sx(ssx),
          sy(ssy),
          dx(ddx),
          dy(ddy) {}
};

std::vector<searchMove> moves = {
    searchMove(0, 0, 1, 0),  searchMove(0, 0, 0, 1),  searchMove(0, 7, 1, 0),
    searchMove(0, 7, 0, -1), searchMove(7, 0, -1, 0), searchMove(7, 0, 0, 1),
    searchMove(7, 7, -1, 0), searchMove(7, 7, 0, -1),
};

std::vector<board> mountains = {
    0x7e00000000000000,
    0x000000000000007e,
    0x0080808080808000,
    0x0001010101010100,
};

int firmPoint(const Board& current, bool turn) {
    board res = 0;
    board my_board = current(turn);

    for (const auto& m : moves) {
        for (int i = 0; i < 8; ++i) {
            int x = m.sx + m.dx * i;
            int y = m.sy + m.dy * i;
            board b = toBit(x, y);
            if (b & my_board) res |= b;
            else
                break;
        }
    }

    return popcount(res);
}

int cornerPoint(const Board& current, bool turn) {
    board my_board = current(turn);
    board op_board = current(!turn);

    return popcount(my_board & 0x8100000000000081) -
           popcount(op_board & 0x8100000000000081);
}

int sidePoint(const Board& current, bool turn) {
    board my_board = current(turn);
    board op_board = current(!turn);

    return popcount(my_board & 0x7e8181818181817e) -
           popcount(op_board & 0x7e8181818181817e);
}

int patternPoint(const Board& current, bool turn) {
    int score_tmp = 0;
    board my_board = current(turn);
    board op_board = current(!turn);

    for (const auto& m : mountains) {
        if ((my_board & m) == m) score_tmp += 1;
        if ((op_board & m) == m) score_tmp -= 1;
    }

    return score_tmp;
}

int evaluate(const Board& current, bool turn) {
    int a = firmPoint(current, turn);
    int b = patternPoint(current, turn);
    int c = popcount(current.legalBoard(turn)) -
            popcount(current.legalBoard(!turn));
    int d = cornerPoint(current, turn);
    int e = sidePoint(current, turn);

    return 10 * a + 10 * b + c + 70 * d + 10 * e;
}

}  // namespace reversi::evaluator03
