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

state_t(std::string name)
void add_substate(state_t state)
void add_condition(condition_t condition)
event_t on_event(stream_t input, std::function<void(context_t)> fn)
error_t on_error(std::function fn) 
void on_enter(std::function fn)
void on_exit(std::function fn)



*/


