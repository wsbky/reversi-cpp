#pragma once

#include <algorithm>
#include <vector>

#include "../board.hh"

namespace reversi {
namespace com {

const board positions1 = 0x8100000000000081;
const board positions2 = 0x3c0081818181003c;
const board positions3 = 0x00003c3c3c3c0000;
const board positions4 = 0x0042000000004200;

const int max_score = 10000;
const int min_score = -10000;

board search(const Board&, bool, int);
int alphabeta(const Board&, bool, int, int, int);
int evaluate(const Board&, bool);

board search(const Board& current, bool turn, int depth) {
    const std::vector<board> legalPuts = current.legalPuts(turn);
    std::vector<int> scores;
    scores.reserve(legalPuts.size());

    for (const auto& e : legalPuts) {
        int score = -alphabeta(Board(current).put(e, turn), !turn, depth,
                               -max_score, -min_score);
        scores.push_back(score);
    }

    std::vector<int>::iterator it_max =
        std::max_element(scores.begin(), scores.end());
    return legalPuts.at(std::distance(scores.begin(), it_max));
}

int alphabeta(const Board& node, bool turn, int depth, int a, int b) {
    if (node.isFinish() || depth == 0) {
        return evaluate(node, turn);
    }

    if (node.isPass(turn)) return -alphabeta(node, !turn, depth - 1, -b, -a);

    const std::vector<board> legalPuts = node.legalPuts(turn);

    for (const auto& e : legalPuts) {
        Board child = Board(node).put(e, turn);
        a = std::max(a, -alphabeta(child, !turn, depth - 1, -b, -a));
        if (a >= b) return a;
    }
    return a;
}

int evaluate(const Board& board, bool turn) {
    int a = BitOperation::popcount(board.legalBoard(turn)) -
            BitOperation::popcount(board.legalBoard(!turn));

    int b1 = BitOperation::popcount(board(turn) & positions1);
    int b2 = BitOperation::popcount(board(turn) & positions2);
    int b3 = BitOperation::popcount(board(turn) & positions3);
    int b4 = BitOperation::popcount(board(turn) & positions4);

    int b = b1 * 20 + b2 * 6 + b3 * 3 - b4 * 100;
    return a * 100 + b * 20;
}

}  // namespace com

namespace player {
Board com1(Board current, bool turn, std::ostream& os, std::ostream& ros) {
    board put = com::search(current, turn, 6);
    int x = -1, y = -1;
    for (int i = 0; i < 64; ++i)
        if (put >> i) {
            x = 8 - i % 8;
            y = 8 - i / 8;
        }

    os << (turn ? "●" : "○") << " (x y): " << x << " " << y << "\n";
    ros << (turn ? "Black" : "White") << ": " << x << " " << y << "\n";
    return current.put(put, turn);
}
}  // namespace player

}  // namespace reversi
