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

initial_state(state_t s)
initial_state(state_t[] s)
bool is_current(state_t s)
send(string s) OR handle(string s)
reset() <-- ??
	
event_context_t
---------------

stream()
string()
next_stream()

start_timer()

*/






