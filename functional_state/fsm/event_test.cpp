////////////////////
// event_test.cpp //
////////////////////

#include "event.hpp"

#include <gtest/gtest.h>

class EventTest : public testing::Test
{
public:
	event_t event;
};

TEST_F(EventTest, Foo) {
}




/*
event_t
-------

next_state(state_t s)
next_state(condition_t c, state_t[] s)
next_state(state_t[] s)

must_next(state_t s)
must_next(condition_t c, state_t[] s);
must_next(state_t[] s)




*/





