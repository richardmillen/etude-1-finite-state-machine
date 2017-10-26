////////////////////////
// timer_test.cpp //
////////////////////////

#include "timer.hpp"

#include <gtest/gtest.h>

class TimerTest : public testing::Test
{
public:
	timer_t timer;
};

TEST_F(TimerTest, Foo) {

}




/*
timer_t
-----------

timer_t(std::string name)

tick_t on_tick(stream_t, std::function<void(context_t)> fn)
*/






