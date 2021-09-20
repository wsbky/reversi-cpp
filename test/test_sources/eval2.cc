#include <gtest/gtest.h>

#include "lib/evaluators/02.hh"

using namespace reversi;
using namespace reversi::evaluator02;

TEST(corner_test1, 1) {
    Board a(0x8000000000000000, 0);
    EXPECT_EQ(evaluate(a, true), 100);
}
