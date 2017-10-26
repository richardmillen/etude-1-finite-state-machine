/////////////////////
// stream_test.cpp //
/////////////////////

#include "stream.hpp"

#include <gtest/gtest.h>

class StreamTest : public testing::Test
{
public:
	stream_t stream;
};

TEST_F(StreamTest, Foo) {
}

/*
stream_t<T>
-----------

stream_t
--------

stream_t(string name, string match)
stream_t(string name, string introducer, string match)
std::string value()
value(std::string s)

operator<<()
operator=()


*/




