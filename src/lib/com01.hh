#pragma once

#include <algorithm>
#include <functional>
#include <vector>

#include "board.hh"
#include "evaluators/01.hh"

namespace reversi::com1 {

using Evaluator = std::function<int(const Board&, bool)>;
Evaluator evaluate = evaluator01::evaluate;
int max_score = 10000;
int min_score = -10000;

void set(Evaluator& eval, int score_max = 10000, int score_min = -10000) {
    evaluate = eval;
    max_score = score_max;
    min_score = score_min;
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

}  // namespace reversi::com1
