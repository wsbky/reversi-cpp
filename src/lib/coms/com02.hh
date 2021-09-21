#pragma once

#include <algorithm>
#include <functional>
#include <vector>

#include "../board.hh"

namespace reversi {

using namespace BitOperation;

class com2 {
    Evaluator ev_early;
    Evaluator ev_middle;
    Evaluator ev_final;
    int depth_early;
    int depth_middle;
    int depth_final;
    int switch_first;
    int switch_second;
    int max_score = 10000;
    int min_score = -10000;

    int alphabeta(Evaluator ev, const Board& node, bool turn, int depth, int a,
                  int b) {
        if (node.isFinish() || depth == 0) {
            return ev(node, turn);
        }

        if (node.isPass(turn))
            return -alphabeta(ev, node, !turn, depth - 1, -b, -a);

        const std::vector<board> legalPuts = node.legalPuts(turn);

        for (const auto& e : legalPuts) {
            Board child = Board(node).put(e, turn);
            a = std::max(a, -alphabeta(ev, child, !turn, depth - 1, -b, -a));
            if (a >= b) return a;
        }
        return a;
    }

  public:
    com2(Evaluator early, Evaluator middle, Evaluator final, int d_early,
         int d_middle, int d_final, int switch1 = 12, int switch2 = 52,
         int maxscore = 10000, int minscore = -10000)
        : ev_early(early),
          ev_middle(middle),
          ev_final(final),
          depth_early(d_early),
          depth_middle(d_middle),
          depth_final(d_final),
          switch_first(switch1),
          switch_second(switch2),
          max_score(maxscore),
          min_score(minscore) {}

    board search(const Board& current, bool turn) {
        const std::vector<board> legalPuts = current.legalPuts(turn);
        std::vector<int> scores;
        scores.reserve(legalPuts.size());

        Evaluator ev;
        int depth;
        int count = popcount(current(turn) | current(!turn));
        std::cout << count << std::endl;
        if (count < switch_first) {
            ev = ev_early;
            depth = depth_early;
        } else if (count < switch_second) {
            ev = ev_middle;
            depth = depth_middle;
        } else {
            ev = ev_final;
            depth = depth_final;
        }

        for (const auto& e : legalPuts) {
            int score = -alphabeta(ev, Board(current).put(e, turn), !turn,
                                   depth, -max_score, -min_score);
            scores.push_back(score);
        }

        std::vector<int>::iterator it_max =
            std::max_element(scores.begin(), scores.end());
        return legalPuts.at(std::distance(scores.begin(), it_max));
    }
};

}  // namespace reversi
