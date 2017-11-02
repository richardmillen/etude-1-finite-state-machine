////////////////////
// state_test.cpp //
////////////////////

#include "state.hpp"

#include <gtest/gtest.h>

TEST(StateTest, GetName) {
	state_t state("test");
	ASSERT_EQ("test", state.name());
}


