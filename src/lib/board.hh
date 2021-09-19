#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace reversi {
using board = std::uint64_t;

namespace BitOperation {
int popcount(board x) {
    x = x - ((x >> 1) & 0x5555555555555555);

    x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);

    x = (x + (x >> 4)) & 0x0f0f0f0f0f0f0f0f;
    x = x + (x >> 8);
    x = x + (x >> 16);
    x = x + (x >> 32);

    return x & 0x0000007f;
}

board toBit(unsigned int x, unsigned int y) {
    if (x > 8 || y > 8) return 0;
    return 0x8000000000000000 >> (x + y * 8);
}

board transfer(board put, int k) {
    switch (k) {
        case 0: return (put << 8) & 0xffffffffffffff00;
        case 1: return (put << 7) & 0x7f7f7f7f7f7f7f00;
        case 2: return (put >> 1) & 0x7f7f7f7f7f7f7f7f;
        case 3: return (put >> 9) & 0x007f7f7f7f7f7f7f;
        case 4: return (put >> 8) & 0x00ffffffffffffff;
        case 5: return (put >> 7) & 0x00fefefefefefefe;
        case 6: return (put << 1) & 0xfefefefefefefefe;
        case 7: return (put << 9) & 0xfefefefefefefe00;
        default: return 0;
    }
}
}  // namespace BitOperation

class Board {
  private:
    board black;
    board white;

  public:
    Board(board black = 0x0000000810000000, board white = 0x0000001008000000)
        : black(black),
          white(white) {}
    Board(const Board& other) : black(other.black), white(other.white) {}

    Board& operator=(const Board& rhs) {
        black = rhs.black;
        white = rhs.white;
        return *this;
    }

    board operator()(bool turn) const { return turn ? black : white; }

    board legalBoard(bool turn) const {
        const board my_board = turn ? black : white;
        const board op_board = turn ? white : black;
        const board blank_board = ~(black | white);

        const board hor_watch_op_board = op_board & 0x7e7e7e7e7e7e7e7e;
        const board ver_watch_op_board = op_board & 0x00ffffffffffff00;
        const board all_watch_op_board = op_board & 0x007e7e7e7e7e7e00;

        board temp;
        board legal_board = 0;

        // left
        temp = hor_watch_op_board & (my_board >> 1);
        for (int i = 0; i < 5; ++i) temp |= hor_watch_op_board & (temp >> 1);
        legal_board |= blank_board & (temp >> 1);

        // right
        temp = hor_watch_op_board & (my_board << 1);
        for (int i = 0; i < 5; ++i) temp |= hor_watch_op_board & (temp << 1);
        legal_board |= blank_board & (temp << 1);

        // upper
        temp = ver_watch_op_board & (my_board >> 8);
        for (int i = 0; i < 5; ++i) temp |= ver_watch_op_board & (temp >> 8);
        legal_board |= blank_board & (temp >> 8);

        // lower
        temp = ver_watch_op_board & (my_board << 8);
        for (int i = 0; i < 5; ++i) temp |= ver_watch_op_board & (temp << 8);
        legal_board |= blank_board & (temp << 8);

        // upper left
        temp = all_watch_op_board & (my_board >> 9);
        for (int i = 0; i < 5; ++i) temp |= all_watch_op_board & (temp >> 9);
        legal_board |= blank_board & (temp >> 9);

        // upper right
        temp = all_watch_op_board & (my_board >> 7);
        for (int i = 0; i < 5; ++i) temp |= all_watch_op_board & (temp >> 7);
        legal_board |= blank_board & (temp >> 7);

        // lower left
        temp = all_watch_op_board & (my_board << 7);
        for (int i = 0; i < 5; ++i) temp |= all_watch_op_board & (temp << 7);
        legal_board |= blank_board & (temp << 7);

        // lower right
        temp = all_watch_op_board & (my_board << 9);
        for (int i = 0; i < 5; ++i) temp |= all_watch_op_board & (temp << 9);
        legal_board |= blank_board & (temp << 9);

        return legal_board;
    }
    std::vector<board> legalPuts(bool turn) const {
        std::vector<board> ret;
        ret.reserve(BitOperation::popcount(legalBoard(turn)));

        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j)
                if (canPut(BitOperation::toBit(i, j), turn))
                    ret.push_back(BitOperation::toBit(i, j));

        return ret;
    }
    bool canPut(board put, bool turn) const {
        return (put & legalBoard(turn)) == put;
    }

    Board& put(board put, bool turn) {
        board my_board = turn ? black : white;
        board op_board = turn ? white : black;

        board rev = 0;

        for (int i = 0; i < 8; ++i) {
            board temp = 0;
            board mask = BitOperation::transfer(put, i);
            while ((mask != 0) && ((mask & op_board) != 0)) {
                temp |= mask;
                mask = BitOperation::transfer(mask, i);
            }
            if ((mask & my_board) != 0) rev |= temp;
        }

        my_board ^= put | rev;
        op_board ^= rev;

        black = turn ? my_board : op_board;
        white = turn ? op_board : my_board;

        return *this;
    }

    bool isPass(bool turn) const {
        return legalBoard(turn) == 0 && legalBoard(!turn) != 0;
    }
    bool isFinish() const {
        return legalBoard(true) == 0 && legalBoard(false) == 0;
    }
    int judge() const {
        int black_count = BitOperation::popcount(black);
        int white_count = BitOperation::popcount(white);

        if (black_count > white_count) return 1;
        if (white_count > black_count) return -1;
        return 0;
    }

    std::string toString(bool show_legal = false, bool turn = true) const {
        std::string ret;
        ret += "   1 2 3 4 5 6 7 8  \n";
        ret += "  ----------------- \n";

        for (int i = 0; i < 8; ++i) {
            ret += std::to_string(i + 1) + "| ";

            for (int j = 0; j < 8; ++j) {
                if (black & BitOperation::toBit(j, i)) ret += "●";
                else if (white & BitOperation::toBit(j, i))
                    ret += "○";
                else if (show_legal &&
                         legalBoard(turn) & BitOperation::toBit(j, i))
                    ret += "+";
                else
                    ret += "∙";

                if (j != 7) ret += " ";
            }

            ret += " |\n";
        }

        ret += "  ----------------- \n";
        return ret;
    }
};
}  // namespace reversi
