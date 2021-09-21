#pragma once

#include "board.hh"

namespace reversi {

namespace player {

void human(Board&, bool, std::istream&, std::ostream&, std::ostream&);
void com(Board&, bool, std::ostream&, std::ostream&);

void human(Board& current, bool turn, std::istream& is, std::ostream& os,
           std::ostream& ros) {
    char s1, s2;
    int x = -1, y = -1;

    for (;;) {
        os << (turn ? "●" : "○") << " (x y): ";
        is >> s1;
        if (s1 == 'p') {
            ros << (turn ? "Black" : "White") << ": passed\n";
            return;
        }
        is >> s2;
        if (std::isdigit(s1) && std::isdigit(s2)) {
            x = s1 - '0';
            y = s2 - '0';
        }

        if (current.canPut(BitOperation::toBit(x - 1, y - 1), turn)) break;
    }
    ros << (turn ? "Black" : "White") << ": " << x << " " << y << "\n";
    current.put(BitOperation::toBit(x - 1, y - 1), turn);
}

void com(Search search, Board& current, bool turn, std::ostream& os,
         std::ostream& ros) {
    board put = search(current, turn);
    int x = -1, y = -1;
    for (int i = 0; i < 64; ++i)
        if (put >> i) {
            x = 8 - i % 8;
            y = 8 - i / 8;
        }

    os << (turn ? "●" : "○") << " (x y): " << x << " " << y << "\n";
    ros << (turn ? "Black" : "White") << ": " << x << " " << y << "\n";
    current.put(put, turn);
}

}  // namespace player
}  // namespace reversi
