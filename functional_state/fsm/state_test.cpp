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
	add_substate(state_t state)
	add_condition(condition_t condition)
	on_event(stream_t input, std::function handler) -> event_t
	on_error(std::function handler) -> error_t
	on_enter(std::function handler)
	on_exit(std::function handler)
	
event_t:
	next_state(state_t conditional_state)
	next_state(condition_t condition, std::initialization_list<state_t> conditional_states);
	next_state(std:initialization_list...)
	must_next(state_t conditional_state)
	must_next(condition_t condition, std::initialization_list<state_t> conditional_states);
	must_next(std::initialization_list...)
	
*/


