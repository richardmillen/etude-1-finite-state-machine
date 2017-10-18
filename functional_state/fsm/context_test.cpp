//////////////////////
// context_test.cpp //
//////////////////////

#include "context.hpp"

#include <gtest/gtest.h>

class ContextTest : public testing::Test
{
public:
	context_t ctx;
};

TEST_F(ContextTest, Foo) {
}


/*
context_t:
	initial_state(state_t state)
	send(string s)
	reset() <-- ??
	
event_context_t:
	stream()
	next_stream()
*/






