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
state_t
-------

void add_substate(state_t state)
void add_condition(condition_t condition)
event_t on_event(stream_t input, std::function handler)
error_t on_error(std::function handler) 
void on_enter(std::function handler)
void on_exit(std::function handler)
	
	
*/


