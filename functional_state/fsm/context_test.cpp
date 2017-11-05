//////////////////////
// context_test.cpp //
//////////////////////

#include "context.hpp"
#include "state.hpp"
#include "stream.hpp"

#include <gtest/gtest.h>

#include <iostream>
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

TEST_F(ContextTest, StateHandlesMultipleEvents) {
	auto counter = 0;
	
	stream_t inc("increment counter", "i");
	stream_t dec("decrement counter", "d");
	
	state1.on_event(inc, [&](context_t& c) {
		++counter;
	});
	
	state1.on_event(dec, [&](context_t& c) {
		--counter;
	});
	
	context.start(state1);
	
	context.execute("i");
	context.execute("i");
	context.execute("i");
	context.execute("d");
	context.execute("d");
	
	ASSERT_EQ(1, counter);
}

TEST_F(ContextTest, EventReadsFromStream) {
	string str;
	
	stream_t any("all events");
	state1.on_event(any, [&](context_t& c) {
		str.append(c.input());
	});
	
	context.start(state1);
	
	context.execute("a");
	context.execute("b");
	context.execute("c");
	
	EXPECT_EQ("abc", str);
}

TEST_F(ContextTest, StateTransitions) {
	ostringstream oss;
	
	stream_t next("go to next", "next");
	stream_t prev("go to previous", "prev");
	
	state1.on_event(next, [&](context_t& c) {
		oss << c.input();
	}).next_state(state2);

	state2.on_event(prev, [&](context_t& c) {
		oss << "," << c.input();
	}).next_state(state1);
	
	context.start(state1);
	
	context.execute("next");
	context.execute("prev");
	
	ASSERT_EQ("next,prev", oss.str());
}

TEST_F(ContextTest, StreamSharedByStates) {
	ostringstream oss;
	
	stream_t shared("shared stream", "[abc]");
	
	state1.on_event(shared, [&](context_t& c) {
		oss << "1" << c.input();
	}).next_state(state2);
	
	state2.on_event(shared, [&](context_t& c) {
		oss << "2" << c.input();
	});
	
	context.start(state1);
	
	context.execute("a");
	context.execute("b");
	context.execute("c");
	
	ASSERT_EQ("1a2b2c", oss.str());
}







/*


TEST_F(ContextTest, StateExecutesNextState) {
	ostringstream oss;
	
	state_t end("end");
	
	stream_t move("move to next state", R"(\d)");
	stream_t skip("skip to end", "SKIP");
	stream_t last("last event", {R"(state\d)", R"(\d)"});
	
	state1.on_event(move, [&](context_t& c) {
		oss << "1:" << c.input() << " ";
	}).next_state(state2);
	
	state1.on_event(skip, [&](context_t& c) {
		oss << "1:" << c.input() << " ";
		c.next_execute("state1");
	}).next_state(end);
	
	state2.on_event(move, [&](context_t& c) {
		oss << "2:" << c.input() << " ";
	}).next_state(state1);
	
	end.on_event(last, [&](context_t& c) {
		oss << "E:" << c.input(1) << " [from: " << c.input(0) << "]";
	});
	
	context.start(state1);
	
	context.execute("a");
	context.execute("b");
	context.execute("c");
	context.execute("d");
	context.execute("SKIP");
	context.execute("e");
	
	ASSERT_EQ("1:a 2:b 1:c 2:d 1:SKIP E:e [from: state1]", oss.str());
}




*/


/*
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

initial_state(state_t[] s)
reset() <-- ??

stream()
string()
next_stream()

start_timer()


*/






