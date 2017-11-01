//////////////////////
// context_test.cpp //
//////////////////////

#include "context.hpp"
#include "state.hpp"

#include <gtest/gtest.h>

class ContextTest : public testing::Test
{
public:
	ContextTest() : state1("state1"), state2("state2"), counter(0) {}
private:
	context_t context;
	state_t state1;
	state_t state2;
	int counter;
};

TEST_F(ContextTest, NoCurrentState) {
	ASSERT_FALSE(context.is_current(state1));
}

TEST_F(ContextTest, StartStateIsCurrent) {
	context.start(state1);
	
	ASSERT_TRUE(context.is_current(state1));
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






