#pragma once

#include <fstream>
#include <map>
#include <vector>

#include "../board.hh"

namespace reversi::evaluator02 {

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

std::map<std::vector<bool>, int> scores = {
    {std::vector<bool>{true, true, true}, 100},
    {std::vector<bool>{true, false, true}, 100},
    {std::vector<bool>{true, true, false}, 100},
    {std::vector<bool>{true, false, false}, 100},
    {std::vector<bool>{false, true, false}, -50},
    {std::vector<bool>{false, true, true}, -50},
    {std::vector<bool>{false, false, true}, 10},
    {std::vector<bool>{false, false, false}, 0},
};

int cornerEval(const Board& current, bool turn) {
    std::vector<bool> my_temp(3, false);
    std::vector<bool> op_temp(3, false);
    int score_temp = 0;

    for (const auto& m : moves) {
        for (int i = 0; i < 3; ++i) {
            my_temp.at(i) =
                toBit(m.sx + m.dx * i, m.sy + m.dy * i) & current(turn);
            op_temp.at(i) =
                toBit(m.sx + m.dx * i, m.sy + m.dy * i) & current(!turn);
        }
        score_temp += scores[my_temp] - scores[op_temp];
    }

    return score_temp;
}

int evaluate(const Board& current, bool turn) {
    std::ofstream ofs;
    ofs.open("eval_log.txt", std::ios::app);

    int a = popcount(current.legalBoard(turn)) -
            popcount(current.legalBoard(!turn));

    int b = cornerEval(current, turn);

    ofs << current.toString(true, turn);
    ofs << "score: " << a << " " << b << std::endl;

    return a + 3 * b;
}
}  // namespace reversi::evaluator02
