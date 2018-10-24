#include "pch.h"
#include "../Poker/assets/Hand.h"

#include "gtest/gtest.h"


double square(int n) { return n * n; }

TEST(SquareRootTest, PositiveNos) {
	EXPECT_EQ(324, square(18));
	EXPECT_EQ(625, square(25));
	EXPECT_EQ(2500, square(50));
}

TEST(SquareRootTest, ZeroAndNegativeNos) {
	ASSERT_EQ(0, square(0));
	ASSERT_EQ(1, square(-1));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}