////////////////////
// state_test.cpp //
////////////////////

#include "state.hpp"

#include <gtest/gtest.h>

class StateTest : public testing::Test
{
public:
	state_t state;
};

TEST_F(StateTest, Foo) {
}

/*
state_t:
	add_substate(string name)
	next_state(string name)
	add_event(stream_t input, function handler)

*/

