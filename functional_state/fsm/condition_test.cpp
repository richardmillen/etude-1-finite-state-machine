////////////////////////
// condition_test.cpp //
////////////////////////

#include "condition.hpp"

#include <gtest/gtest.h>

class ConditionTest : public testing::Test
{
public:
	condition_t condition;
};

TEST_F(ConditionTest, Foo) {
}




/*
condition_t
-----------

condition_t()
condition_t(std::function<bool(state_t)> fn)

expr() -> std::string&		<-- ??

eval(std::function<bool(state_t)> fn)


*/






