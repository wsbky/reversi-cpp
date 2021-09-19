#include "reversi.hh"

#include <fstream>
#include <iostream>

int main() {
    // reversi::Board a(0x0010240720260000, 0x000858f81c181400);
    // std::cout << a.toString(true);

    // a.put(reversi::BitOperation::toBit(3, 7), true);
    // std::cout << a.toString(true, false);

    std::ofstream ofs;
    ofs.open("record.txt", std::ios::out);

    reversi::playHvC(reversi::com1::search, std::cin, std::cout, ofs);

    return 0;
}
