//////////////////////
// context_test.cpp //
//////////////////////

#include "context.hpp"
#include "state.hpp"
#include "stream.hpp"

#include <gtest/gtest.h>

#include <string>
#include <sstream>
#include <functional>

using namespace std;

class ContextTest : public testing::Test
{
public:
	ContextTest() : state1("state1"), state2("state2") {}
public:
	context_t context;
	state_t state1;
	state_t state2;
};

TEST_F(ContextTest, NoCurrentState) {
	ASSERT_FALSE(context.is_current(state1));
}

TEST_F(ContextTest, StartStateIsCurrent) {
	context.start(state1);
	
	ASSERT_TRUE(context.is_current(state1));
}

TEST_F(ContextTest, StateHandlesSingleEvent) {
	auto counter = 0;
	
	stream_t plus("plus (increment counter)", R"(\+)");
	state1.on_event(plus, [&](context_t& c) {
		++counter;
	});
	
	context.start(state1);
	
	EXPECT_FALSE(context.execute("abc"));
	EXPECT_FALSE(context.execute("123"));
	EXPECT_FALSE(context.execute("-"));
	EXPECT_FALSE(context.execute("/"));
	EXPECT_FALSE(context.execute(""));
	
	EXPECT_TRUE(context.execute("+"));
	
	EXPECT_EQ(1, counter);
}

TEST_F(ContextTest, EventReadsFromStream) {
	ostringstream oss;
	
	stream_t any("all events");
	state1.on_event(any, [&](context_t& c) {
		oss << c.input().accepted();
	});
	
	context.start(state1);
	
	context.execute("a");
	context.execute("b");
	context.execute("c");
	
	EXPECT_EQ("abc", oss.str());
}

/*
state moves to next (single handler)
state moves to next (multiple handlers)
handler writes to next stream
state on enter
state on exit
state on error ?
state doesn't move to conditional next
state moves to conditional next
state moves to one of many conditional next/s
substate handles event
timer
timer changes
timer changes state

no state >> assertion error

event_t
-------

next_state(state_t s)
next_state(condition_t c, state_t[] s)
next_state(state_t[] s)

must_next(state_t s)
must_next(condition_t c, state_t[] s);
must_next(state_t[] s)

state_t
-------

state_t(std::string name)
state_t(std::string name, timer_t timer)

std::string name()
add_substate(state_t s)
add_condition(condition_t c)
add_conditions(condition_t[], binary_function<>, condition_t[])



on_enter(std::function<void(context_t)> fn)

on_exit(std::function<void(context_t)> fn)

error_t on_error(std::function<void(context_t)> fn) 


condition_t
-----------

condition_t()
condition_t(std::function<bool(state_t)> fn)

expr() -> std::string&		<-- ??

eval(std::function<bool(state_t)> fn)



context_t:

nitial_state(state_t[] s)
reset() <-- ??

stream()
string()
next_stream()

start_timer()


*/






