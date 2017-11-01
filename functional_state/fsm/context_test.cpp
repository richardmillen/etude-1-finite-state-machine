//////////////////////
// context_test.cpp //
//////////////////////

#include "context.hpp"
#include "state.hpp"

#include <gtest/gtest.h>

class ContextTest : public testing::Test
{
public:
	context_t ctx;
};

TEST_F(ContextTest, NoCurrentState) {
	state_t s("foo");
	
	ASSERT_FALSE(ctx.is_current(s));
}

TEST_F(ContextTest, StartStateIsCurrent) {
	state_t s("foo");
	ctx.start(s);
	
	ASSERT_TRUE(ctx.is_current(s));
}

/*

recv() ignored
recv() handled


recv()  /  send()  /  handle()  /  process()  /  input()  /  execute()

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






