//////////////////
// fsm_test.cpp //
//////////////////

#include "context.hpp"
#include "state.hpp"
#include "stream.hpp"

#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <stdexcept>

using namespace std;

class FsmTest : public testing::Test
{
public:
	FsmTest() : state1("state1"), state2("state2"), state3("state3") {}
public:
	context_t context;
	state_t state1;
	state_t state2;
	state_t state3;
};

TEST_F(FsmTest, NoCurrentState) {
	ASSERT_FALSE(context.is_current(state1));
}

TEST_F(FsmTest, StartStateIsCurrent) {
	context.start(state1);
	
	ASSERT_TRUE(context.is_current(state1));
}

TEST_F(FsmTest, StateHandlesSingleEvent) {
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

TEST_F(FsmTest, StateHandlesMultipleEvents) {
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

TEST_F(FsmTest, EventReadsFromStream) {
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

TEST_F(FsmTest, StateTransitions) {
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

TEST_F(FsmTest, StreamSharedByStates) {
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

TEST_F(FsmTest, StateExecutesNextState) {
	ostringstream oss;
	
	state_t end("end");
	
	stream_t move("move to next state", "[a-z]{1}");
	stream_t skip("skip to end", "END");
	stream_t last("last event (format: from,message)", {R"(state\d)", ",", ".+"});
	
	state1.on_event(move, [&](context_t& c) {
		oss << "1:" << c.input() << " ";
	}).next_state(state2);
	
	state1.on_event(skip, [&](context_t& c) {
		oss << "1:" << c.input() << " ";
		c.next_execute("state1,hi!");
	}).next_state(end);
	
	state2.on_event(move, [&](context_t& c) {
		oss << "2:" << c.input() << " ";
	}).next_state(state1);
	
	end.on_event(last, [&](context_t& c) {
		oss << "E:[" << c.input(0) << " says " << c.input(2) << "]";
	});
	
	context.start(state1);
	
	context.execute("a");
	context.execute("b");
	context.execute("c");
	context.execute("d");
	context.execute("END");
	
	ASSERT_EQ("1:a 2:b 1:c 2:d 1:END E:[state1 says hi!]", oss.str());
}

TEST_F(FsmTest, StateEnteredEvent) {
	bool entered = false;
	bool exited = false;
	
	stream_t next("go to next", "next");
	
	state1.on_event(next, [](context_t& c) {}).next_state(state2);
	
	state1.on_exit([&](context_t& c) {
		exited = true;
	});
	
	state2.on_enter([&](context_t& c) {
		entered = true;
	});
	
	context.start(state1);
	
	context.execute("next");
	
	EXPECT_TRUE(exited);
	EXPECT_TRUE(entered);
}

TEST_F(FsmTest, FalseConditionPreventsTransition) {
	stream_t next("go to next", "next");
	
	state1.on_event(next, [](context_t& c) {}).next_state(state2);
	
	state2.add_condition(condition_t([](state_t& s) {
		return false;
	}));
	
	context.start(state1);
	
	context.execute("next");
	
	ASSERT_TRUE(context.is_current(state1));
}

TEST_F(FsmTest, TransitionToOneOfMany) {
	auto which = 0;
	
	stream_t opt("go to state 2 or 3", "[23]");
	
	state1.on_event(opt, [&](context_t& c) {
		which = stoi(c.input());
	}).next_state({state2, state3});
	
	state2.add_condition(condition_t([&](state_t& s) {
		return which == 2;
	}));
	state2.add_condition(condition_t([&](state_t& s) {
		return which == 3;
	}));

	context.start(state1);
	
	context.execute("3");
	
	ASSERT_TRUE(context.is_current(state3));
}

TEST_F(FsmTest, AncestorOfStateHandlesEvent) {
	auto handled_by_ancestor = false;
	
	state_t grand_parent("grand parent");
	state_t parent("parent");
	state_t child("child");
	
	stream_t any("handle any input");
	
	grand_parent.on_event(any, [&](context_t& c) {
		handled_by_ancestor = true;
	});
	
	grand_parent.add_substate(parent).add_substate(child);
	
	context.start(child);
	
	EXPECT_TRUE(context.is_current(child));
	EXPECT_FALSE(context.is_current(parent));
	EXPECT_FALSE(context.is_current(grand_parent));
	
	context.execute("hello");
	
	EXPECT_TRUE(handled_by_ancestor);
}

TEST_F(FsmTest, MustTransitionToNextStateFails) {
	stream_t any("accept any input");
	
	state1.on_event(any, [](context_t& c) {
		// MUST move from state1 to state2
	}).must_next(state2);
	
	state2.add_condition(condition_t([&](state_t& s) {
		return false;
	}));
	
	context.start(state1);
	
	ASSERT_THROW(context.execute("foo"), std::logic_error);
}








