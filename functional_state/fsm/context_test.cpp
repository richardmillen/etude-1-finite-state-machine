//////////////////////
// context_test.cpp //
//////////////////////

#include "context.hpp"
#include "state.hpp"
#include "stream.hpp"

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

TEST_F(ContextTest, StateHandlesAllEvents) {
	stream_t any("any");
	state1.on_event(any, [&](ctx) {
		++counter;
	});
	context.start(state1);
	
	context.execute("foo");
	EXPECT_EQ(1, counter);

	context.execute("bar");
	EXPECT_EQ(2, counter);
}





/*
no state >> error ?
event not handled
state handles event
state moves to next (single handler)
state moves to next (multiple handlers)
state on enter
state on exit
state on error ?
state doesn't move to conditional next
state moves to conditional next
substate handles event


state_t
-------

state_t(std::string name)
state_t(std::string name, timer_t timer)

std::string name()
add_substate(state_t s)
add_condition(condition_t c)
add_conditions(condition_t[], binary_function<>, condition_t[])

event_t on_event(stream_t input, std::function<void(context_t)> fn)

on_enter(std::function<void(context_t)> fn)

on_exit(std::function<void(context_t)> fn)

error_t on_error(std::function<void(context_t)> fn) 


context_t:

nitial_state(state_t[] s)
reset() <-- ??

stream()
string()
next_stream()

start_timer()


*/






