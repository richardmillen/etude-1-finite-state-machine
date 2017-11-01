////////////////////
// state_test.cpp //
////////////////////

#include "state.hpp"

#include <gtest/gtest.h>

TEST(StateTest, GetName) {
	state_t state("test");
	ASSERT_EQ("test", state.name());
}


/*

+ name() readonly string
+ 




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



*/


